from cs50 import SQL
from flask import Flask, render_template, request
from helpers import random_string
import random

app = Flask(__name__)
app.config["TEMPLATES_AUTO_RELOAD"] = True

db = SQL("sqlite:///history.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # Get page number
        page = request.form.get("page") # put the actual name, not 'name'!

    if request.method == "GET":
        page = request.args.get("page")

     # Validate input
    try:
        page = int(page)
    except ValueError:
        return render_template("index.html", string="Enter a number")

    if page < 0:
        return render_template("index.html", string="Enter a positive number")

    # Update history.db
    if not db.execute("SELECT page FROM history WHERE page=?", page):
        db.execute("INSERT INTO history (page) VALUES (?)", page)

    # Create random page seed
    random.seed(page)

    string = random_string(page)
    history = db.execute("SELECT * FROM history")
    return render_template("index.html", string=string, history=history)