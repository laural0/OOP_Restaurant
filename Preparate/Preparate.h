//
// Created by Laura on 12/5/2023.
//

#ifndef PROIECT_OOP_PREPARATE_H
#define PROIECT_OOP_PREPARATE_H

#include<iostream>
#include <map>
#include <sstream>
#include "../Ingredient/Ingrediente.h"

class Preparat {
    char *denumire = nullptr;
    std::map<Ingredient, float> reteta;
    static float adaosComercial;        //in procent
    bool dePost = false;

public:

    Preparat();

    Preparat(char *numePreparat);

    Preparat(char *numePreparat, std::map<Ingredient, float> &reteta, bool dePost);

    Preparat(Preparat &preparat);

    ~Preparat();

    void set_denumire(const char *denumire);


    void set_reteta(const std::map<Ingredient, float> &reteta);

    static void set_adaosComercial(const float adaosComercial);

    void set_dePost(const bool dePost);

    char *get_denumire() const;

    std::map<Ingredient, float> get_reteta() const;

    static float get_adaosComercial();

    bool get_dePost() const;

    friend std::ostream &operator<<(std::ostream &out, const Preparat &preparat);

    friend std::istream &operator>>(std::istream &in, Preparat &preparat);

    void getListaPreparate();

    void adaugaPreparat();
};


#endif //PROIECT_OOP_PREPARATE_H
