from sys import argv

# Words in dictionary
words = set()

def check(word):
    # if the word (case insensetive) is in the set, return true
    if word.lower():
        return True
    else:
        return False
    

def load(dictionary):
    # load dictionary into memory and return true if successful
    file = open(dictionary)
    for line in file:
        word = line.rstrip()
        words.add(word)
    file.close()
    return True


def size():
    return len(words)


