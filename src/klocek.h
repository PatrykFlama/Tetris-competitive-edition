#include "enums.h"
#include <cstdlib>
#include <bits/stdc++.h>

class Klocek
{
    TypKlocka typ;
    int wielkosc;
    std::vector<std::vector<bool>> tablica;

public:
    Klocek(TypKlocka _typ);
    TypKlocka dajTyp();
    std::vector<std::vector<bool>> dajTablice();
    void obroc(KierunekObrotu kierunekObrotu);
};
