//
// Created by Laura on 1/5/2024.
//

#ifndef PROIECT_OOP_MENIU_H
#define PROIECT_OOP_MENIU_H

#include<iostream>
#include <vector>
#include "../Preparate/Preparate.h"

class Meniu{

public:
    static void afiseazaMeniu();
    static std::vector<Preparat>getListaMancare();
    static std::vector<Preparat>getListaBauturi();
    static void genereazaRaportProfit();
};



#endif //PROIECT_OOP_MENIU_H
