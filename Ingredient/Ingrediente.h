//
// Created by Laura on 12/5/2023.
//

#ifndef PROIECT_OOP_INGREDIENTE_H
#define PROIECT_OOP_INGREDIENTE_H

#include<cstring>
#include "../ExceptionInput/ExceptionInput.h"
#include<iostream>


class Ingrediente { //todo: poate sparta in 2 clase IngredientVrac si ingredientLabucata ? sau sa aiba un flag boolean daca e la bucata sau nu
    const int cod;  //todo: clasa denumita la singular
    char *numeIngredient = nullptr;
    float kcalorii = 0;              //per 100g
    float pret = 0;                 //per 100g
    float cantitate = 0;
    bool alergen = false;

public:
    Ingrediente(const int cod) : cod(cod) {}

    Ingrediente(const int cod, char const *numeIngredient, float calorii, float pret, float cantitate, bool alergen)
            : cod(cod) {
        if (numeIngredient != nullptr) {
            this->numeIngredient = new char[strlen(numeIngredient) + 1];
            strcpy(this->numeIngredient, numeIngredient);
        } else {
            throw ExceptionInput("Atributul este null.");
        }
        if (calorii <= 0) {
            throw ExceptionInput("Caloriile ingredientului trebuie sa fie mai mari decat 0.");
        } else {
            this->kcalorii = calorii;
        }
        if (pret <= 0) {
            throw ExceptionInput("Pretul ingredientului trebuie sa fie mai mare decat 0.");
        } else {
            this->pret = pret;
        }
        if (cantitate < 0) {
            throw ExceptionInput("Cantitatea ingredientului trebuie sa fie mai mare decat 0.");
        } else {
            this->cantitate = cantitate;
        }
        this->alergen = alergen;
    }

    Ingrediente(Ingrediente const &a, const int cod) : cod(cod) {
        delete[] this->numeIngredient;
        this->numeIngredient = nullptr;

        this->numeIngredient = new char[strlen(a.numeIngredient) + 1];
        strcpy(this->numeIngredient, a.numeIngredient);

        this->kcalorii = a.kcalorii;
        this->pret = a.pret;
        this->cantitate = a.cantitate;
        this->alergen = a.alergen;

    }
    ~Ingrediente() {
        delete[] numeIngredient;
        numeIngredient = nullptr;
    }

    void set_numeIngredient(const char *numeIngredient);

    void set_kcalorii(const float kcalorii);

    void set_pret(const float pret);

    void set_cantitate(const float cantitate);

    void set_alergen(const bool alergen);

    char *get_numeIngredient() const;

    float get_kcalorii() const;

    float get_pret() const;

    float get_cantitate() const;

    bool get_alergen() const;

    friend std::ostream &operator<<(std::ostream &out, const Ingrediente &a);

    friend std::istream &operator>>(std::istream &in, Ingrediente &a);


    float CalculeazaCalorii() const;

    float CalculeazaPret() const;

};


#endif //PROIECT_OOP_INGREDIENTE_H
