#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {

        int k = atoi(argv[1]); //zamiana stringa na inta - mimo, że wpisujemy liczę początkowo z argv mamy string
        int w = k % 26; //dzielenie przez modulo, dzięki, któremu może max przesunąc litery o 25 miejsc
        if (argc == 2)
        {
            string p = get_string("Plaintext: ");

            printf("ciphertext: ");

            for (int i = 0, n = strlen(p); i < n; i++)

                if (islower(p[i]) && p[i] + w > 122) //dla małych liter, nie przeskakujemy poza nie
                {
                    printf("%c", p[i] + w - 26);
                }



                else if (isupper(p[i]) && p[i] + w > 90) //dla dużych liter, nie przeskakujemy poza nie
                {
                    printf("%c", p[i] + w - 26);
                }


                else if (!(isalpha(p[i]))) //dla znaków, zostawiamy je bez zmian
                {
                    printf("%c", p[i]);
                }

                else // dla liter, które mieszczą się bez przeskakiwania
                {
                    printf("%c", p[i] + w);
                }
            printf("\n");

        }
    }
    else
    {
        printf("błąd\n");
        return 1;
    }
}