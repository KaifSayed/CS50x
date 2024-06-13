from cs50 import get_int


def main():
    # Get user input for blocks height
    height = 0
    while height < 1 or height > 8:
        height = get_int("Height: ")

    for i in range(1, height + 1):
        # Print spaces
        for j in range(height - i):
            print(" ", end="")

        # Print left blocks
        for j in range(i):
            print("#", end="")

        # Print spaces
        print("  ", end="")

        # Print right blocks
        for j in range(i):
            print("#", end="")

        print()


if __name__ == "__main__":
    main()
