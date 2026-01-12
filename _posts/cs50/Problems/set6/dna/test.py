import csv

str_names = []
people = []

with open("databases/small.csv") as file:
    reader = csv.DictReader(file)
    str_names = reader.fieldnames[1:]
    # print("STR names: ")
    # print(str_names)
    # print("row are:")
    for row in reader:
        # print(row)
        person = {'name': row['name']}
        for str_name in str_names:
            person[str_name] = int(row[str_name])
            people.append(person)


print("str_names are:")
print(str_names)
print("people are:")
print(people)

print("#" * 100)
with open("sequences/1.txt", "r") as file:
    sequence = file.read().strip()
    print("sequence example")
    print(sequence)


str_counts = {}
for str_name in str_names:
    str_counts[str_name] = longest_match(sequence, str_name)

for person in people:
    match = True
    for str_name in str_names:
        if int(person[str_name]) != str_counts[str_name]:
            match = False
            break
    if match:
        print(person['name'])
