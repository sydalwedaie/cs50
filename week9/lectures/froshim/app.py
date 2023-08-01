from cs50 import SQL
from flask import Flask, render_template, request, redirect

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee"
]

app = Flask(__name__)

db = SQL("sqlite:///froshim.db")


@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)


@app.route("/register", methods=["POST"])
def register():
    # Validate submission
    name = request.form.get("name")
    sport = request.form.get("sport")
    if not name:
        return render_template("error.html", message="Missing name")
    if not sport:
        return render_template("error.html", message="Missing sport")
    if sport not in SPORTS:
        return render_template("error.html", message="Invalid sport")

    # Remember registrants
    db.execute("INSERT INTO registrants (name, sport) VALUES(?, ?)", name, sport)

    # Confrim registration
    return redirect("/registrants")


@app.route("/registrants") # "POST" is not allowed here
def registrants():
    registrants = db.execute("SELECT * FROM registrants")
    return render_template("registrants.html", registrants=registrants)


@app.route("/deregister", methods=["POST"])
def deregister():
    id = request.form.get("id")

    # Forget Registrant
    if id:
        db.execute("DELETE FROM registrants WHERE registrants.id=?", id)
    return redirect("/registrants")