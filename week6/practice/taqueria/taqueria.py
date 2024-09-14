def main():
    total = 0.00

    try:
        while True:
            item = input("Item: ")
            if len(item) < 1:
                break
            item = item.title()
            if item in menu:
                total += menu[item]
                print("Total: ${:.2f}".format(total))

    except EOFError:
        print()


menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00,
}

main()
