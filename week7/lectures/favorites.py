import csv

with open("favorites.csv") as file:
    reader = csv.DictReader(file)
    counts = dict()

    for row in reader:
        favorite = row["problem"]
        # if favorite == "Scratch":
        #     counts["scratch"] += 1 if "scratch" in counts else 1
        #     # if "scratch" in counts:
        #     #     counts["scratch"] +=1
        #     # else:
        #     #     counts["scratch"] = 1
        # elif favorite == "C":
        #     counts["c"] += 1 if "c" in counts else 1
        #     # if "c" in counts:
        #     #     counts["c"] +=1
        #     # else:
        #     #     counts["c"] = 1
        # elif favorite == "Python":
        #     counts["python"] += 1 if "python" in counts else 1
        #     # if "python" in counts:
        #     #     counts["python"] +=1
        #     # else:
        #     #     counts["python"] = 1

        # if favorite in counts:
        #     counts[favorite] += 1
        # else:
        #     counts[favorite] = 1

        counts[favorite] = counts.get(favorite, 0) + 1

for favorite in sorted(counts, key=lambda favorite: counts[favorite], reverse=True):
    print(f"{favorite}: {counts[favorite]}")