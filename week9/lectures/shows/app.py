from cs50 import SQL
from flask import Flask, render_template, request, jsonify


app = Flask(__name__)
db = SQL("sqlite:///shows.db")


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/search")
def search():
    # q will come from the input value of the search form.
    # The letter 'q' is hardcoded in the 'fetch' command in the javascript section.
    query_string = request.args.get("q")
    if query_string:
        shows = db.execute("SELECT * FROM shows WHERE title LIKE ? LIMIT 20", "%" + query_string + "%")
    else:
        shows = []
    return jsonify(shows)