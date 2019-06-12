#include <cs50.h>
#include <stdio.h>

int main(void)
{
int i;
    do
    {
    i = get_int("height: ");
    }
    while(i >=23);

    for (int n = 0; n < i; n++)
    {

         for (int m = n+1; m < i; m++)

        {
            printf(" ");
        }

        for (int m = 0; m < n+1; m++)

        {
            printf("#");
        }

        for (int m = 0; m < 3; m++)

        {
            printf(" ");
        }

        for (int m = 0; m < n+1; m++)

        {
            printf("#");
        }

       printf("\n");
    }
}