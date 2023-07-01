import sys

names = ['ali', 'hassan', 'hussain', 'yusuf', 'sayed']

name = input("Name: ")

if name in names:
    print(f"{name} was found in the list!")
    sys.exit(0)

print(f"{name} was not found")
sys.exit(1)