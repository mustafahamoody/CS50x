"""
References
Vijetha. (2023, February 9). How to Start Python For Loop at 1. Spark By {Examples}. Retrieved August 4, 2023, from https://sparkbyexamples.com/python/how-to-start-python-for-loop-at-1/
"""

from cs50 import get_int

# TODO
height = -1

while height < 1 or height > 8:
    height = get_int("Height: ")

space = height - 1

for i in range(1, height + 1):
    print(" " * space, end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i)
    space -= 1
