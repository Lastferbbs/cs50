import cs50

def space():
    for a in range(n-i-1):
        print(" ", end="")

def space2():
    print(" ", end="")
    print(" ", end="")


def block():
    for a in range(i+2):
        print("#", end="")


n = cs50.get_int("Number beetween 1 and 22: ")
if n > 0 and n < 23:
    for i in range(n):
        space()
        block()
        space2()
        block()
        print()
