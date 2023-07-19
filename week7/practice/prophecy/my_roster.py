from cs50 import SQL
import csv

db = SQL('sqlite:///my_roster.db')

with open('students.csv') as file:
    file_reader = csv.DictReader(file)

    for row in file_reader:
        db.execute("INSERT INTO students (student_name) VALUES (?)", row['student_name'])

        if not db.execute("SELECT house FROM houses WHERE house = ?", row['house']):
            db.execute("INSERT INTO houses (house, head) VALUES (?, ?)", row['house'], row['head'])

        student_id = db.execute("SELECT id FROM students WHERE student_name = ?", row['student_name'])[0]['id']
        house_id = db.execute("SELECT id FROM houses WHERE house = ?", row['house'])[0]['id']

        db.execute("INSERT INTO assignments (student_id, house_id) VALUES (?, ?)", student_id, house_id)
