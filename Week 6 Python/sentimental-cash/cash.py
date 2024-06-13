from cs50 import get_float


def get_cents():
    cents = -1
    while cents < 0:
        try:
            dollars = get_float("Change owed: ")
            cents = round(dollars * 100)
        except ValueError:
            print("Please enter a valid number.")
    return cents


def calculate_coins(cents, denomination):
    # Calculate the number of coins for the given denomination
    return cents // denomination


def main():
    # Ask how much change the customer is owed
    cents = get_cents()

    # Calculate the number of quarters to give the customer
    quarters = calculate_coins(cents, 25)
    cents -= quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_coins(cents, 10)
    cents -= dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = calculate_coins(cents, 5)
    cents -= nickels * 5

    # Calculate the number of pennies to give the customer
    pennies = cents

    # Sum coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coins to give the customer
    print(coins)


if __name__ == "__main__":
    main()
