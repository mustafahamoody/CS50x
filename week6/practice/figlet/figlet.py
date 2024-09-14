from pyfiglet import Figlet
from sys import argv, exit
import random

figlet = Figlet()

fonts = figlet.getFonts()

f = random.choice(fonts)

if len(argv) != 0 and len(argv) != 3:
    print("Invalid usage")
    exit(1)

if len(argv) == 3:
    if argv[1] != "-f" and argv[1] != "--font":
        print("Invalid usage")
        exit(1)

    elif argv[2] not in fonts:
        print("Invalid usage")
        exit(1)

    else:
        f = argv[2]

figlet.setFont(font=f)

word = input("Input: ")

print(figlet.renderText(word))
