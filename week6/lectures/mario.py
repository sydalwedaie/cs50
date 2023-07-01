from cs50 import get_int

def main():
    height = get_height()
    width = get_width()
    for i in range(height):
        print('#' * width)

def get_height():
    while True:
        n = get_int("Enter height: ")
        if n > 0:
            return n

def get_width():
    while True:
        n = get_int("Enter width: ")
        if n > 0:
            return n

main()