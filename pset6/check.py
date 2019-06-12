import cs50

def company():
    lista = [] # tworzymy listy do przechowywania elementów numeru karty i działań na nich
    lista1 = [] #lista z elementami mnozonymi
    lista2 = [] #lista z elementami do zsumowania
    for  i in range(len(n)):
        lista.append(int(n[i])) #dodajemy elementy do naszej głownej listy i zamieniamy je na liczby



    for  i, e in reversed(list(enumerate(lista))):  #pętla for, gdzie odwracamy kolejność w liście i jednocześnie mamy dostęp do indeksu

        if len(n) == 16: #uwzględniamy przypadek gdy liczba cyfr w numerze jest parzysta i wynosi 16

            if i % 2 == 0 and e < 5: #standardowe mnożenie
                w = e * 2
                lista2.append(int(w))
            elif i % 2 == 0 and e > 4: #mnożenie, gdzie wynik wyszedł 10 lub więcej, odejmujemy 9 by zsumować elementy liczby
                w = (e * 2) - 9
                lista2.append(int(w))
            else:
                lista1.append(int(e)) #elementy, które należy zsumować, czyli od ostatniego co dwa

        else:                         #to samo, tylko w przypadku dla nieparzystych numerów kart
            if i % 2 == 1 and e < 5:
                w = e * 2
                lista2.append(int(w))
            elif i % 2 == 1 and e > 4:
                w = (e * 2) - 9
                lista2.append(int(w))
            else:
                lista1.append(int(e))


    result = (sum(lista2) + sum(lista1)) % 10


    if result == 0 and len(n) == 15 and int(n[0]) == 3 and (int(n[1]) == 4 or int(n[1]) == 7):
        print("AMEX") #szalone warunki, które karta musi spełnić, by była z AMEX, 2 pozostałe to samo tylko dla VISY i MC

    elif result == 0 and len(n) == 16 and int(n[0]) == 5 and (int(n[1]) == 1 or int(n[1]) == 2 or int(n[1]) == 3 or int(n[1]) == 4 or int(n[1]) == 5):
        print("MASTERCARD")

    elif result == 0 and (len(n) == 13 or len(n) == 16) and int(n[0]) == 4:
        print("VISA")

    else:
        print("INVALID") #zły numer karty


n = cs50.get_string("YOUR CREDIT CARD NUMBER: ")
company()