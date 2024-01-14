//
// Created by Laura on 12/5/2023.
//

#ifndef PROIECT_OOP_PREPARATE_H
#define PROIECT_OOP_PREPARATE_H

#include<iostream>
#include <map>
#include <sstream>
#include <memory>
#include "../Ingredient/Ingrediente.h"

typedef std::string string;

class Preparat {
    string denumire = "";
    std::vector<Ingredient> reteta;
    static float adaosComercial;        //in procent
    bool esteAlergen = false;

public:

    Preparat();

    Preparat(const std::string &numePreparat);

    Preparat(const std::string &numePreparat, const std::vector<Ingredient> &reteta, bool alergen);

    Preparat(const Preparat &preparat);

    Preparat(Preparat &&sursa);

    ~Preparat();

    void set_denumire(const string &denumire);

    void set_reteta(const std::vector<Ingredient> &reteta);

    static void set_adaosComercial(const float adaosComercial);

    void set_Alergen(const bool alergen);

    string get_denumire() const;

    std::vector<Ingredient> get_reteta() const;

    static float get_adaosComercial();

    bool get_Alergen() const;

    friend std::ostream &operator<<(std::ostream &out, const Preparat &preparat);

    friend std::istream &operator>>(std::istream &in, Preparat &preparat);

    //static std::vector<Preparat> getListaPreparate();
    //a fost mutata in meniu

    Preparat &getPreparat(std::string denumire);

    Preparat &operator=(const Preparat &preparat);

    float calculeazaPret();

    float calculeazaCalorii();

    bool operator==(const Preparat &preparat);

    static void adaugaPreparat(Preparat preparat);

    static bool verificaStocIngrediente(const Preparat &preparat);

    static void modificaStocIngrediente(const Preparat &preparat, const std::string &flag);
};


#endif //PROIECT_OOP_PREPARATE_H
