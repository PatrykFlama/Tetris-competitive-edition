#include "enums.h"
#include <cstdlib>
#include <bits/stdc++.h>

class Klocek
{
    TypKlocka typ;
    int wielkosc;
    std::vector<std::vector<bool>> tablica;

public:
    Klocek(TypKlocka typ_temp);
    TypKlocka dajTyp();
    std::vector<std::vector<bool>> dajTablice();
    std::vector<std::vector<bool>> obroc(KierunekObrotu kierunekObrotu);
};
