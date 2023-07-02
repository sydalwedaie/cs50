books = []

for i in range(3):
    book = dict()
    book["title"] = input("Title: ")
    book["author"] = input("Author: ")
    books.append(book)

for book in books:
    print("The book {} is written by {}".format(book["title"], book["author"]))

print()

print(books)