import csv

books = []

with open("books-utf8.csv") as file:
    file_reader = csv.DictReader(file)

    for book in file_reader:
        books.append(book)

for book in books:
    print(book)