from cs50 import SQL
from flask import Flask, redirect, render_template, request, session
from flask_session import Session

app = Flask(__name__)
db = SQL("sqlite:///store.db")

# Configure Session
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = 'filesystem'
Session(app)

@app.route("/")
def index():
    books = db.execute("SELECT * FROM books")
    return render_template("books.html", books=books)

@app.route("/cart", methods=["GET", "POST"])
def cart():
    if "cart" not in session:
        session["cart"] = []

    if request.method == "POST":
        session["cart"].append(request.form.get("id"))

    cart = db.execute("SELECT * FROM books WHERE id IN (?)", session["cart"])
    return render_template("cart.html", cart=cart)