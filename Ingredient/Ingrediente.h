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
    std::string denumire = "";
    float kcalorii = 0;              //per 100g
    float pret = 0;                 //per 100g
    float stoc = 0;
    bool alergen = false;

    void convertLowercase(std::string &sir);

    void inregistreazaIngredient();

    void actualizeazaIngredient(int linie);

public:

    static int cautaLinieIngredient(std::string denumire);

    Ingredient();

    explicit Ingredient(const std::string denumire);

    Ingredient(const std::string numeIngredient, float calorii, float pret, float stoc, bool alergen);

    Ingredient(Ingredient const &ingredient);

    ~Ingredient();

    void set_denumire(const std::string numeIngredient);

    void set_kcalorii(const float kcalorii);

    void set_pret(const float pret);

    void set_stoc(const float stoc);

    void set_alergen(const bool alergen);

    std::string get_numeIngredient() const;

    float get_kcalorii() const;

    float get_pret() const;

    float get_stoc() const;

    bool get_alergen() const;

    bool operator<(const Ingredient &ingredient) const;

    friend std::ostream &operator<<(std::ostream &out, const Ingredient &a);

    friend std::istream &operator>>(std::istream &in, Ingredient &a);

    Ingredient &operator=(const Ingredient &ingredient);

    bool operator!=(const Ingredient &ingredient);

    static Ingredient getIngredientDinLista(int linieDinFisier);

    void adaugaIngredient();


    static std::vector<Ingredient> getListaIngrediente();

    static bool verificaInStoc(const Ingredient &ingredient);

    static void modificaStoc(const Ingredient &ingredient, const std::string &flag);
};


#endif //PROIECT_OOP_INGREDIENTE_H
