from cs50 import get_int

# Keep prompting for height until correct value is entered.
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# Each line consists of leading spaces which shrink, and blocks that grow.
# Use `height` and `i` to get this shrinking and growing in an iteration.
# the extra `-1` and `+1` are to account for the fact that `i` starts at 0.
for i in range(height):
    leading_spaces = " " * (height - i - 1)
    blocks = "#" * (i + 1)
    print(f"{leading_spaces}{blocks}  {blocks}")

