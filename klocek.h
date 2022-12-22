#include "types.h"
#include <cstdlib>
#include <bits/stdc++.h>

std::vector<std::vector<std::vector<bool>>> klocki =
{
    {//I
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {//J
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0 ,0},
        {0, 0, 0, 0}       
    },
    {//L
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0 ,0},
        {0, 0, 0, 0}   
    },
    {//O
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0 ,0},
        {0, 0, 0, 0}
    },
    {//S
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0 ,0},
        {0, 0, 0, 0}       
    },
    {//Z
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0 ,0},
        {0, 0, 0, 0}       
    },
    {//T
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0 ,0},
        {0, 0, 0, 0}       
    }

};

int wielkosci[7] = {4, 3, 3, 2, 3, 3, 3};


class Klocek{
    type typ;
    int wielkosc;
    int nr_obrotu;
    std::string kolor;
    std::vector<std::vector<bool>> matrix;

    public:
        Klocek(){//tu moze w konstruktor wlozyc wielkosc planszy zeby moc wylosowac x i y na podstawie tego
            typ = static_cast<type>(rand() % end);
            std::cout << "typ to: " << typ << "\n";
            int do_obrocenia = rand() % 4;
            matrix = klocki[typ];
            wielkosc = wielkosci[typ];
            std::cout << "wielkosc to: " << wielkosc << "\n";
            for(int i=0; i<do_obrocenia; i++){
                Obroc();
            }
            //kolor = losuj_kolor();
        }
        Klocek(type typ_temp){ 
            //TODO
        }
        type Typ(){
            return typ;
        }
        std::vector<std::vector<bool>> Matrix(){
            return matrix;
        }
        std::vector<std::vector<bool>> Obroc(bool kierunek = true){
            //true - w prawo, false - w lewo

            //TODO
        }

};