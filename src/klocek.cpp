#include "klocek.h"
#include <cstdlib>
#include <bits/stdc++.h>

std::vector<std::vector<std::vector<bool>>> klocki =
    {
        {// I
         {0, 0, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 1, 0}},
        {// J
         {1, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {// L
         {0, 0, 1, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {// O
         {1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {// S
         {0, 1, 1, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {// Z
         {1, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {// T
         {0, 1, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}

};

int wielkosci[7] = {4, 3, 3, 2, 3, 3, 3};

Klocek::Klocek(TypKlocka _typ = I)
{
    typ = _typ;
    wielkosc = wielkosci[typ];
    tablica = klocki[typ];
}
TypKlocka Klocek::dajTyp()
{
    return typ;
}
std::vector<std::vector<bool>> Klocek::dajTablice()
{
    return tablica;
}
void Klocek::obroc(KierunekObrotu kierunekObrotu = PRAWO)
{

    std::vector<std::vector<bool>> nowa_tablica = tablica;

    for(int i = 0; i < wielkosc; i++){
        for(int j = 0 ; j < wielkosc; j++){
            if(kierunekObrotu == PRAWO){
                nowa_tablica[j][wielkosc - i - 1] = tablica[i][j];
            } else {
                nowa_tablica[wielkosc - j - 1][i] = tablica[i][j];
            }
        }
    }

    tablica = nowa_tablica;
}
