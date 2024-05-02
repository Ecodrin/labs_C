import random
import names
import os
import string

def randomword(length):
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(length))


def main():
    numbers_students = random.randint(1, 100)
    for i in range(1, numbers_students):
        print(randomword(15), random.randint(1, 2 ** 16), randomword(49))


if __name__ == "__main__":
    main()