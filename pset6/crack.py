import cs50
from crypt import crypt
from itertools import product
from string import ascii_letters, digits

def decrypt(crypted, charset=ascii_letters):
    # find hash for all 4-char strings from the charset
    # and compare with the given hash
    for candidate in map(''.join, product(charset, repeat=5)):
        if crypted == crypt(candidate, crypted):
            return candidate

salt, hashed = '50', 'YHuxoCN9Jkc'
print(decrypt(salt + hashed))
# -> e2e4
#assert crypt('e2e4', 'qb') == (salt + hashed)



