from cs50 import SQL

favorite = input("Favorite: ")
db = SQL("sqlite:///favorites.db")

rows = db.execute(f"SELECT * AS FROM favorites WHERE problem = '{favorite}'" )

print(rows[0])