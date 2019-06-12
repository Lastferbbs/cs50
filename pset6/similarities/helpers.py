from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    a = a.splitlines()
    b = b.splitlines() #zamienia string na string zlozony z linijek
    c = set(a).intersection(b) #część wspólna z a i b
    return c


def sentences(a, b):
    """Return sentences in both a and b"""
    a = sent_tokenize(a) #znajduje znaki konczace zdanie i oddziela je
    b = sent_tokenize(b)
    c = set(a).intersection(b)
    return c


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    i = 0
    listA = []
    listB = []
    m = n

    for x in range(0, len(a)):
        if m > len(a): #przerywa gdy, albo n jest od początku większe od len(a) albo gdy zakończy się iteracja
            m = n
            i = 0
            break
        listA.append(a[i:m]) # dodaje do listy substring o zadanej długości
        i += 1
        m += 1

    for x in range(0, len(b)):
        if m > len(b):
            break
        listB.append(b[i:m])
        i += 1
        m += 1

    print(listA)
    c = set(listA).intersection(listB)
    return c
