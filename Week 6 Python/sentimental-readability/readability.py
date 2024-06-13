from cs50 import get_string


def count_letters(text):
    count = 0
    for char in text:
        if char.isalpha():
            count += 1
    return count


def count_words(text):
    count = 1  # Assuming at least one word in the text
    for char in text:
        if char.isspace():
            count += 1
    return count


def count_sentences(text):
    count = 0
    for char in text:
        if char in [".", "!", "?"]:
            count += 1
    return count


def main():
    # Get input text from the user
    text = get_string("Text: ")

    # Count letters, words, and sentences
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Calculate the Coleman-Liau index
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Output the reading level
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
