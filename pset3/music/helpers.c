// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int cyf1 = fraction[0] - '0';
    int cyf2 = fraction[2] - '0';

    switch(cyf2)
    {
        case 1:
        cyf1 = cyf1 * 8;
        return cyf1;
        break;

        case 2:
        cyf1 = cyf1 * 4;
        return cyf1;
        break;

        case 4:
        cyf1 = cyf1 * 2;
        return cyf1;
        break;

        case 8:
        return cyf1;
        break;

    }
 return cyf1;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    string podstawa ="A4";
    int a = 1;
    float A4 = 440;

    switch(note[0])
{
    case 'A':
    break;
    case 'B':
   A4 = A4*pow(2.0, 2.0/12.0);
    break;
    case 'C':
   A4 = A4/pow(2.0, 9.0/12.0);
    break;
    case 'D':
    A4 = A4/pow(2.0, 7.0/12.0);
    break;
    case 'E':
   A4 = A4/pow(2.0, 5.0/12.0);
    break;
    case 'F':
   A4 = A4/pow(2.0, 4.0/12.0);
    break;
    case 'G':
   A4 = A4/pow(2.0, 2.0/12.0);
    break;
}


if(strcmp(note, podstawa) == 0)
        return A4;


if(note[1] == '#') //|| note[1] == 'b')
    {
        a++;
        A4 = A4*pow(2.0, 1.0/12.0); //inkrementacja note by przeszedl do nastepnej literki
    }

if(note[1] == 'b')
    {
        a++; //inkrementacja note by przeszedl do nastepnej literki(znaku)
        A4 = A4/pow(2.0, 1.0/12.0);
    }

int ZamNaCyf = note[a] - '0';
int wynik = ZamNaCyf - 4;
int potega = pow(2, abs(wynik));


if(wynik > 0)
    {
        float mnozenie = A4*potega;
        return round(mnozenie);
    }

if(wynik < 0)
    {
        float dzielenie = A4/potega;
        return round(fabs(dzielenie));
    }

if(wynik == 0) //wyjatek dla 4 oktawy, gdzie "wynik" = 0, potrzebne do poprawnego dziala '#' i 'b'
    {
        return round(A4);
    }


    else
    return 0;

    return 0;

}


// Determines whether a string represents a rest
bool is_rest(string s)
{
    if(strcmp(s, "") == 0)
    return true;

    else
    return false;
}
