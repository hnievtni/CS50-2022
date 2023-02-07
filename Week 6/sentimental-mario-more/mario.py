from cs50 import get_int


def main():
    print("Please enter a positive integer for Height.\n", end="")
    height = getPositiveInt()
    # for each row
    for rowCounter in range(1, height + 1):
        # blank spaces before first column
        i = rowCounter
        while height - i != 0:
            print(" ", end="")
            i += 1
        # for each column
        print("#" * rowCounter, end="")

        # blank space between sections
        print("  ", end="")
        # second section
        print("#" * rowCounter, end="")

        print()


def getPositiveInt():
    # to check if the integer we got is positive or not
    height = 0
    while height < 1 or height > 8:
        height = get_int("Height: ")

    return height


main()
