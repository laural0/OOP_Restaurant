//
// Created by Laura on 12/5/2023.
//

#ifndef PROIECT_OOP_PREPARATE_H
#define PROIECT_OOP_PREPARATE_H

#include<iostream>
#include <map>
#include "../Ingredient/Ingrediente.h"

class Preparate {  //todo: clasa denumita la singular : Preparat
    char *numePreparat;
    float cantitateaNecesara;
    map<Ingrediente, float>reteta;
    static float adaosManopera;
    bool dePost;

public:
    Preparate()
};


#endif //PROIECT_OOP_PREPARATE_H
