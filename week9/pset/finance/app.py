import time

from cs50 import SQL
from flask import Flask, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

################
# Configurations
################
# Configure Application
app = Flask(__name__)

# Configure database
db = SQL("sqlite:///finance.db")

# Configure Session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Give templates access to functions on every page
@app.context_processor
def utilities():
    def username(user_id):
        user_entry = db.execute(
            "SELECT username FROM users WHERE id=?",
            session.get("user_id")
        )
        return user_entry[0]["username"]

    return dict({
        "username": username,
        "usd": usd,
        "format_time": time.ctime,
        "lookup": lookup
    })

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response
    
################
# Routes
################
@app.route("/")
@login_required
def index():
    user_id = session.get("user_id")
    portfolio = db.execute(
        "SELECT symbol, SUM(shares) AS shares, price FROM transactions \
        WHERE user_id=? GROUP BY symbol",
        user_id)
    cash = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]["cash"]

    # Calculate total portfolio value
    total = cash
    for stock in portfolio:
        total = total + (stock["price"] * stock["shares"])

    return render_template("index.html", portfolio=portfolio, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # Access via Buy link
    if request.method == "GET":
        return render_template("buy.html")

    # Access via form submit
    user_id = session.get("user_id")
    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    # Validate inputs
    if not symbol:
        return apology("Must provide a symbol", 400)

    if not shares:
        return apology("Must provide number of shares", 400)

    try:
        shares = int(shares)
    except ValueError:
        return apology("Must enter a number", 400)

    if shares < 0:
        return apology("Must provide a positive number of shres", 400)

    # Get and validate stock info
    stock = lookup(symbol)
    if not stock:
        return apology("Symbol not valid", 400)

    # Ensure enough cash available
    available_cash = db.execute(
        "SELECT cash FROM users WHERE id=?",
        user_id
    )[0]["cash"]
    transaction_cost = shares * float(stock["price"])

    if transaction_cost > available_cash:
        return apology("You don't have enough cash to perform this transaction")

    # Add transaction to database
    db.execute(
        "INSERT INTO transactions (user_id, symbol, shares, price, time) \
        VALUES (?, ?, ?, ?, ?)",
        user_id, stock["symbol"], shares, stock["price"], time.time()
    )

    # Update available cash
    remaining_cash = available_cash - transaction_cost
    db.execute("UPDATE users SET cash=? WHERE id=?", remaining_cash, user_id)

    # Redirect to home after purchase
    return redirect("/")


@app.route("/history")
@login_required
def history():
    user_id = session.get("user_id")
    transactions = db.execute("SELECT * FROM transactions WHERE user_id=?", user_id)
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    # User reached route via login URL
    if request.method == "GET":
        return render_template("login.html")

    # User reached route via login form
    username = request.form.get("username")
    password = request.form.get("password")

    # Check username and passwrod are supplied
    if not username:
        return apology("must provide username", 400)
    elif not password:
        return apology("must provide password", 400)

    # Query database for username
    user_entry = db.execute("SELECT * FROM users WHERE username=?", username)

    # Ensure username exists and password is correct
    if len(user_entry) != 1 or not check_password_hash(user_entry[0]["hash"], password):
        return apology("Invalid username and/or passport.")

    # Remember which user has logged in
    session["user_id"] = user_entry[0]["id"]

    return redirect("/")


@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    # access via Quote link
    if request.method == "GET":
        return render_template("quote.html")

    # Access via form
    # Get and validate symbol
    symbol = request.form.get("symbol")
    if not symbol:
        return apology("Symbol field cannot be blank", 400)

    # GEt and validate stock info
    stock = lookup(symbol)
    if not stock:
        return apology("Symbol not valid", 400)

    return render_template("quoted.html", stock=stock)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")

    # Access via POST
    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    # Validate username
    if not username:
        return apology("Must supply a username.", 400)
    elif db.execute("SELECT username FROM users WHERE username=?", username):
        return apology("Username already exists. Choose another username.", 400)

    # Validate password
    if not password:
        return apology("Must supply a password.", 400)

    # Validate confirmation
    if not confirmation:
        return apology("Must supply a confirmation.", 400)
    elif password != confirmation:
        return apology("Password and Confirmation do not match.", 400)

    # Add user to database
    db.execute(
        "INSERT INTO users (username, hash) VALUES (?, ?)",
        username, generate_password_hash(password)
    )

    # Log the user in
    user_entry = db.execute("SELECT * FROM users WHERE username=?", username)
    session["user_id"] = user_entry[0]["id"]

    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_id = session.get("user_id")

    # Access via GET
    if request.method == "GET":
        stocks = db.execute(
            "SELECT DISTINCT(symbol) FROM transactions WHERE user_id=?",
            user_id
        )
        return render_template("sell.html", stocks=stocks)

    # Access via POST
    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    # Validate inputs
    if not symbol:
        return apology("Must provide a symbol", 400)
    elif not shares:
        return apology("Must provide number of shares", 400)
    elif float(shares) < 0:
        return apology("Must provide a positive integer", 400)

    # Get and validate stock info
    stock = lookup(symbol)
    if not stock:
        return apology("Symbol not valid", 400)

    # Ensure enough shares available
    available_shares = db.execute(
        "SELECT SUM(shares) As shares FROM transactions WHERE user_id=? GROUP BY symbol",
        user_id
    )[0]["shares"]

    if float(shares) > float(available_shares):
        return apology("You don't have enough shares to perform this transaction")

    # Add transaction to database
    db.execute(
        "INSERT INTO transactions (user_id, symbol, shares, price, time) \
        VALUES (?, ?, ?, ?, ?)",
        user_id, symbol,
        -(float(shares)),
        float(stock["price"]),
        time.time())

    # Update available cash
    available_cash = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]["cash"]
    transaction_cost = float(shares) * float(stock["price"])
    remaining_cash = available_cash + transaction_cost
    db.execute("UPDATE users SET cash=? WHERE id=?", remaining_cash, user_id)

    # Redirect to home after sale
    return redirect("/")