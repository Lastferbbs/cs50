// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc !=4)
    {
        fprintf(stderr, "Usage: resize ntimes(1-100) infile outfile\n");
        return 1;
    }


    // remember filenames and new size
    char *m = argv[1];
    int n = atoi(m);
    char *infile = argv[2];
    char *outfile = argv[3];

    // ensure max size
    if (n > 100 || n < 1)
    {
        fprintf(stderr, "n must be between 1 and 100.\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    int oldpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; //space for old padding


    bi.biWidth *= n; // n times width
    bi.biHeight *= n; //n times height


    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; //new padding

    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight); //new biSizeImage

    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); //new bfSize


    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines

    int j;
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight)/n; i < biHeight; i++) //przez n, bo chcemy operować na liczbę, która była przed
    {                                                                 //pomnożeniem(czyli stary Height)
        for (int o = 0; o < n - 1; o++) //pętla, która wywoła się o jeden raz mniej niż n
        {
        // iterate over pixels in scanline
            for (j = 0; j < bi.biWidth/n; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }



            }

            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }

            fseek(inptr, -(j*sizeof(RGBTRIPLE)), SEEK_CUR);
            printf("width: %i\n", bi.biWidth);
            offset = ftell(inptr);
            printf("Pozycja w pliku: %ld\n", offset);
        }

        for (j = 0; j < bi.biWidth/n; j++) //ostatnie wykonanie pętli kopiującej, które nie cofa wskaźnika, przez co jest w
        {                                  //w dobtym miejscu po zakończeniu ostatniego przejścia pętli
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);



            // write RGB triple to outfile
            for (int l = 0; l < n; l++)
            {
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }


        }

        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }

        // skip over padding, if any
        fseek(inptr, oldpadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
