//
// Created by Laura on 12/5/2023.
//

#ifndef PROIECT_OOP_INGREDIENTE_H
#define PROIECT_OOP_INGREDIENTE_H

#include<cstring>
#include "../ExceptionInput/ExceptionInput.h"
#include<iostream>
#include <vector>


class Ingredient {
    char *denumire = nullptr;
    float kcalorii = 0;              //per 100g
    float pret = 0;                 //per 100g
    float stoc = 0;
    bool alergen = false;

    void convertLowercase(char *sir);

    void inregistreazaIngredient();

    void actualizeazaIngredient(int linie);

public:

    int cautaLinieIngredient();

    Ingredient();

    explicit Ingredient(const char *denumire);

    Ingredient(char const *numeIngredient, float calorii, float pret, float stoc, bool alergen);

    Ingredient(Ingredient const &ingredient);

    ~Ingredient();

    void set_denumire(const char *numeIngredient);

    void set_kcalorii(const float kcalorii);

    void set_pret(const float pret);

    void set_stoc(const float stoc);

    void set_alergen(const bool alergen);

    char *get_numeIngredient() const;

    float get_kcalorii() const;

    float get_pret() const;

    float get_stoc() const;

    bool get_alergen() const;

    bool operator<(const Ingredient &ingredient) const;

    friend std::ostream &operator<<(std::ostream &out, const Ingredient &a);

    friend std::istream &operator>>(std::istream &in, Ingredient &a);

    Ingredient &operator=(const Ingredient &ingredient);


    void adaugaIngredient();

    static std::vector<Ingredient> getListaIngrediente();

};


#endif //PROIECT_OOP_INGREDIENTE_H
