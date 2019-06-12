# Questions

## What's `stdint.h`?

C library, which let you define size of data types

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

This way we can save memory and we define size of these ints

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

424D

## What's the difference between `bfSize` and `biSize`?

biSize is the size of the BITMAPINFOHEADER only.
bfSize = biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Because of not enough memory

## Why is the third argument to `fread` always `1` in our code?

Bo odczytujemy tylko jeden element

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

It sets the file position of the stream to the given offset.

## What is `SEEK_CUR`?

arguemnt whence, SEEK_CUR moves file pointer position to given location

## Whodunit?

Prof Plum with the candlestick in the library
