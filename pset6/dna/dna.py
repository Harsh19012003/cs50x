import sys
import csv

if len(sys.argv) == 3:
    pass
else:
    print("Usage: name arg1 arg2")
    exit()


# Function taking dna and all STR sequence as input
# and returning list of STR sequence present in dna i.e (text file)
def str_list(strs, dna):

    # Initializing empty list
    str_present = []

    # Iterate through each strand
    for j in range(len(strs)):
        cur_str_seq = strs[j]
        final_max = 0
        p = 0
        cur_max = 0
        # Iterate through dna sample text in window equal to length of current STR strand
        while p in range(len(dna)):
            window = dna[p:p+len(cur_str_seq)]

            # If window is exactly current STR
            if window == cur_str_seq:
                cur_max += 1
                final_max = max(cur_max, final_max)
                # Move to string index just after STR
                p = p + len(cur_str_seq)
            else:
                cur_max = 0
                # Move to next string index
                p += 1

        # Add new list element
        str_present.append(final_max)
    return str_present


# STR text file is opened and stored in "dna"
with open(sys.argv[2], "r") as text_file:
    dna = text_file.read()


# CSV file is opened and stored in output as list of dictionaries
with open(sys.argv[1], "r") as csv_file:
    reader = csv.DictReader(csv_file)

    # Here "output" is a list of dictionaries
    output = list(reader)

    # First row extracted as list of 1 dictionary
    first_row = output[0:1]

# Strands(strs) is list of strands present in csv
strs = list(first_row[0].keys())[1:]


str_output = str_list(strs, dna)


# Empty initialized list
row = []

# Iterate thorough all rows in csv file i.e all elements of output
for i in range(len(output)):
    # Convert each row (values-only of dict) list-dict to list-list
    row.append(list(output[i].values()))


# Converting string characters to integers
for i in range(len(row)):
    for j in range(1, len(str_output)+1):
        row[i][j] = int(row[i][j])


# Compare the obtained row and match it to person and print person
for person in range(len(row)):
    if set(row[person][1:]) == set(str_output):
        true_person = row[person][0]
        break
    else:
        true_person = "No match"

print(true_person)
