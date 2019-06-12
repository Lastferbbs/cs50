# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

Synonym for the disease known as silicosis.

## According to its man page, what does `getrusage` do?

returns resource usage measures for who(in this case, for SELF) - Return resource usage statistics for the calling process,
              which is the sum of resources used by all threads in the
              process(self is a speller).

## Per that same man page, how many members are in a variable of type `struct rusage`?

16 - here is a list http://man7.org/linux/man-pages/man2/getrusage.2.html

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

It uses less memory than passing by value

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

1.Sama pętla for pobiera jeden znak z pliku, po czym sprawdza czy nie jesteśmy na końcu tego pliku, przejściu pętli, wczytuje ona kolejny znak
2. Pierwszy if sprawdza czy nasze słowo zawiera tylko litery lub apostrof('\'' - w ten sposób, podejrzewam, że dlatego, by 3 ' nie stały obok się i kompilator się nie gubił),
następnie upewnia się, że nie przekracza max długości, jeśli przekracza przelatuje przez reszte liter i zeruje indeks dla nowego słowa.
3. Następnie program eliminuje słowa, które zawierają cyfry, tak samo przechodząc przez wszystkie cyfry i przygotowuje się na następne słowo.
4. W tym miejscu mam pewną zagwozdkę, prawdpodobnie program znajduje spację i w ten sposób wykrywa pełne słowo. Zakańcza je w standardowy sposób - '\0',
i zwiększa licznik znalezionych słów. Następnie jest fragment, który mierzy czas potrzebny na sprawdzenie czy słowo jest napisane poprawnie.
A w nim funkcja, która sprawdza czy słowo jest zapisane poprawnie.
5.Później jest fragment zapisujący dane z benchmarka.
6. Później if, który wyświetla słowo z literówką i zwiększa licznik literówek
7. Na samym końcu funkcja ustawia index na 0, by móc obrobić następne słowo.




## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

Prawdopodbnie wczytywal by też słowa z cyframi i innymi znakami. Trzeba by je osobno odfiltrowywać. Możliwe, też, że trudniej byłoby kontrolować index i mieć pewność, że słowo, zostało poprawnie zapisane.
Również trudniej byłoby ograniczyć max długość słowa

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

By zapobiec ich nadpisywaniu, przypuszczam również, że ma to zapobiec oszukiwaniu.
