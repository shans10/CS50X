def main():
    s = input("Text: ")
    n = len(s)
    L = count_letters(s, n) / count_words(s, n) * 100
    S = count_sentences(s, n) / count_words(s, n) * 100
    index = 0.0588 * L - 0.296 * S - 15.8

    if index > 1 and index <= 16:
        print(f"Grade {round(index)}")

    elif index > 16:
        print("Grade 16+")

    else:
        print("Before Grade 1")


def count_letters(s, n):
    letters = 0
    for i in range(n):
        if (ord(s[i]) > 64 and ord(s[i]) < 91) or (ord(s[i]) > 96 and ord(s[i]) < 123):
            letters += 1
    return letters


def count_words(s, n):
    words = len(s.split())
    return words


def count_sentences(s, n):
    sentences = 0
    for i in range(n):
        if s[i] == '.' or s[i] == '?' or s[i] == '!':
            sentences += 1
    return sentences


main()
