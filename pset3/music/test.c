#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "helpers.h"

    int main(void)
    {
        string fraction = get_string("");
        int cyf1 = fraction[0] - '0';
        int cyf2 = fraction[2] - '0';

        switch(cyf2)
        {
            case 1:
            printf("%d\n", cyf1 * 8);
            break;

            case 2:
            printf("%d\n", cyf1 * 4);
            break;

            case 4:
            printf("%d\n", cyf1 * 2);
            break;

            case 8:
            printf("%d\n", cyf1);
            break;


        }
    }



//int frequency(string note)
//{
    // TODO
//}