import cs50

def caesar():
    print("Ciphertext: ", end="")
    for char in zdanie:

        if char.isupper():
            ascii = ord(char) + przesun
            if ascii > 90:
                ascii = ascii - 26

            char = chr(ascii)


        elif char.isalpha():
            ascii = ord(char) + przesun
            if ascii > 122:
                ascii = ascii - 26

            char = chr(ascii)


        print(char, end="")

    print()





przesun = cs50.get_int("Przesuniecie: ")
przesun = przesun % 26
zdanie = cs50.get_string("Plaintext: ")
caesar()