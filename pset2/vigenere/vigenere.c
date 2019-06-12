#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string k = argv[1];
    if (argc == 2) //sprawdzenie czy warunek 2 arg w argc jest spełniony
    {


        for (int i = 0, n = strlen(k); i < n; i++) //sprawdzenie czy wszystkie znaki to litery, inaczej dostajemy błąd
        {
            if (isalpha(k[i]))
            {
                continue;
            }

            else
            {
                printf("Błąd!!!\n");
                return (1);
            }
        }

    }

    else
    {
        printf("Błąd!!!\n");
        return (1);
    }

    string p = get_string("Plaintext: ");
    int n = strlen(p);
    int m = strlen(k);
    int b = 0;
    int c;

    printf("ciphertext: ");

    for (int i = 0; i < n; i++)

        if (islower(p[i])) //szyfrowanie dla małych liter
        {

            c = b % strlen(k); //grupowanie liter, ze wzgłedu na dowolną długość słowa szyfrującego

            char d = tolower(k[c]); //wielkość litery w słowie szyfrującym ma nie mieć w wpływu na wynik, dlatego zawsze będzie mała

            for (int j = 0; j < m; j++) // pętla która dobiera nam odpowiednią literę w kolejności ze słowa szyfrującego
            {
                if (c == j) //pętla która przypisuje odpowiednią literę ze słowa szyfrującego do litery z tekstu do zaszyfrowania
                {
                    //warunki potrzebne by nie wychodzić poza alfabet
                    if (p[i] + d - 97 > 122)
                    {
                        printf("%c", p[i] + d - 97 - 26);
                    }



                    else
                    {
                        printf("%c", p[i] + d - 97);
                    }

                    break; //wychodzi z pętli i lekko przyśpiesza program, który od teraz sprawdza warunek aż co znajdzie i nie dłużej
                }



            }

            b++;
            //inkrementacja b, potrzebna by zliczane były tylko litery, a nie również znaki, dzięki czemu
            //zachowana jest odpowiednia kolejność w szyfsze
        }

        else if (isupper(p[i]))
        {
            //wszystko tutaj działa tak samo jak dla małych liter, z tą różnicą, że nie ma znaczenia wielkość litery w szyfsze
            c = b % strlen(k);

            char e = toupper(k[c]);

            for (int j = 0; j < m; j++)
            {
                if (c == j)
                {
                    if (p[i] + e - 65 > 90)
                    {
                        printf("%c", p[i] + e - 65 - 26);
                    }

                    else
                    {
                        printf("%c", p[i] + e - 65);
                    }

                    break;
                }
            }

            b++;

        }


        else if (!(isalpha(p[i]))) //dla znaków, zostawiamy je bez zmian
        {
            printf("%c", p[i]);
        }

    printf("\n");

}