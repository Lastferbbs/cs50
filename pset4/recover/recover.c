// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: name of image to recover\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    int a = 0;
    int b = 1;
    int f = 0;
    int c = 0;
    uint8_t buffer[512];

    char filename[8];
    sprintf(filename, "%03i.jpg", f);
    FILE *img = fopen(filename, "wb");



    while (fread(buffer, 1, 512, inptr) == 512)
    {
        if  (
            buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            ((buffer[3] & 0xf0) == 0xe0)
            )
        {
            c = 0;
            f++;
            a++;
            if(a == b)
            {
                fwrite(buffer, 1, 512, img);
                f--;
                c++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", f);
                fopen(filename, "wb");
                fwrite(buffer, 1, 512, img);
                c++;
            }


        }

        else if(c == b)
        {
            fwrite(buffer, 1, 512, img);
        }










    }

fclose(img);
}
