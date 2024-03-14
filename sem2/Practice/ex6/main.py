import random
import names
import os


def main():
    numbers_students = random.randint(1, 1000)
    for i in range(1, numbers_students):
        print(i, names.get_full_name(), 'man' if random.randint(0, 1) == 1 else 'woman', random.randint(1, 16),
              random.randint(1, 5),
              random.randint(1, 5), random.randint(1, 5), random.randint(1, 5), random.randint(1, 5),
              random.randint(1, 5), random.randint(1, 5))


if __name__ == "__main__":
    main()