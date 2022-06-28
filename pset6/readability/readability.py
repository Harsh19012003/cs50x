from cs50 import get_string

# Input from user
text = get_string("Text: ")
length = (len(text))

# Variables declaration
sentences = 0
words = 0
letters = 0

# Sentences counter
for i in range(length):
    if text[i] == '.' or text[i] == '?' or text[i] == '!':
        sentences += 1

# Words counter
for i in range(length-1):
    if text[i] == ' ' or text[i] == '!' or text[i] == '?' or (text[i] == '.' and text[i + 1] != ' '):
        words += 1
words += 1

# Letter counter
for i in range(length):
    if str.isalpha(text[i]):
        letters += 1

# Variables declaration
L = (letters * 100) / words
S = (sentences * 100) / words

# Grade calculated using Coleman-Liau index formula
grade = round(0.0588 * L - 0.296 * S - 15.8)

# Proper grade display inbetween 1 to 16
if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
