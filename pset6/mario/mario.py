from cs50 import get_int

# Valid input acception
while True:
    h = get_int("Height? ")
    if h >= 1 and h <= 8:
        break

# Rows
for i in range(h):
    # Column blank
    for j in range(2, h-i+1):
        print(" ", end="")

    # Column first half
    for j in range(h-i, h+1):
        print("#", end="")

    # Column void in middle
    print("  ", end="")

    # Column secind half
    for j in range(h+2, h+2+i+1):
        print("#", end="")

    # Print new line
    print()