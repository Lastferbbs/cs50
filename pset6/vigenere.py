import cs50


def caesar():
    print("Ciphertext: ", end="")
    a = 0
    przesun.lower()
    for char in zdanie:

        if char.isupper():
            ascii = ord(char) + (ord(przesun[a]) - ord("a")) #zamienia literę w kodzie na przesuniecie o
                                                             #odpowiadające jej miejsce w alfabecie - 1
            if ascii > 90:
                ascii = ascii - 26 #zapętla alfabet

            char = chr(ascii) #zamienia na znak

            #/\ zamiana litery na odpowiadającą jej liczbę

            a += 1

            if a == len(przesun): # wraca na poczatek kodu, po przejsciu calego
                a = 0

        elif char.isalpha():
            ascii = ord(char) + (ord(przesun[a]) - ord("a"))
            if ascii > 122:
                ascii = ascii - 26

            char = chr(ascii)

            a += 1

            if a == len(przesun):
                a = 0

        print(char, end="")

    print()


przesun = cs50.get_string("Kod: ")
zdanie = cs50.get_string("Plaintext: ")
caesar()