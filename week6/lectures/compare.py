from cs50 import get_string

x = get_string("x: ")
y = get_string("y: ")

if x < y:
    print("x less than y")
elif x > y:
    print("x more than y")
else:
    print("x equal y")