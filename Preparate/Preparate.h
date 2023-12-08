//
// Created by Laura on 12/5/2023.
//

#ifndef PROIECT_OOP_PREPARATE_H
#define PROIECT_OOP_PREPARATE_H

#include<iostream>
#include <map>
#include "../Ingredient/Ingrediente.h"

class Preparat {
    char *denumire;
    float numarIngrediente;
    std::map<Ingredient, float> reteta;
    static float adaosComercial;        //in procent
    bool dePost;

public:
    Preparat(char *numePreparat);

    Preparat(char *numePreparat, float numarIngrediente, std::map<Ingredient, float> &reteta, bool dePost);

    Preparat(Preparat &a);

    ~Preparat();

    void set_denumire(const char *denumire);

    void set_numarIngrediente(const float numarIngrediente);

    void set_reteta(const std::map<Ingredient, float> &reteta);

    static void set_adaosComercial(const float adaosComercial);

    void set_dePost(const bool dePost);

    char* get_denumire() const;

    float get_numarIngrediente() const;

    std::map<Ingredient, float> get_reteta() const;

    static float get_adaosComercial();

    bool get_dePost() const;

    friend std::ostream &operator<<(std::ostream &out, const Preparat &a);

    friend std::istream &operator>>(std::istream &in, Preparat &a);
};


#endif //PROIECT_OOP_PREPARATE_H
