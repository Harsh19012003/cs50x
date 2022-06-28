from cs50 import get_string
import re

# Getiing user input credit card number
number = get_string("Enter credit card number ")
n = int(number)

# Basic variables
length = len(number)
add = 0

# Luhn's algorithm for validity
for index in range(length - 1, -1, -2):
    add += int(number[index])

for index in range(length - 1, -1, -2):
    add += int(number[index]*2)

if add % 10 == 0:
    v1 = False
else:
    v1 = True

# Starting of number validity
amex = "^34|^37"
mastercard = "^51|^52|^53|^54|^55"
visa = "^4"

# Checking for required conditions and outputting
# If is valid acc. to luhn's algorithm
if v1 == True:
    if length == 15:
        # if digits 34 or 37:
        if (re.search(amex, number)):
            print("AMEX")
        else:
            print("INVALID")

    elif length == 13:
        # if digits 4
        if(re.search(visa, number)):
            print("VISA")
        else:
            print("INVALID")

    elif length == 16:
        # if digits 51 or 52 or 53 or 54 or 55
        if(re.search(mastercard, number)):
            print("MASTERCARD")
        elif(re.search(visa, number)):   # else if digits 4
            print("VISA")
        else:
            print("INVALID")

    else:
        print("INVALID")

else:
    print("INVALID")
