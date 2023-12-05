//
// Created by Laura on 12/5/2023.
//

#include "Ingrediente.h"


void Ingrediente::set_numeIngredient(const char *numeIngredient) {
    if (this->numeIngredient != nullptr) {
        delete[] this->numeIngredient;
        this->numeIngredient = nullptr;
    }
    if (numeIngredient != nullptr) {
        this->numeIngredient = new char[strlen(numeIngredient) + 1];
        strcpy(this->numeIngredient, numeIngredient);
    } else {
        throw ExceptionInput("Atributul este null.");
    }
}

void Ingrediente::set_kcalorii(const float kcalorii) {
    if (kcalorii <= 0) {
        throw ExceptionInput("Caloriile trebuie sa fie mai mari decat 0.");

    } else {
        this->kcalorii = kcalorii;
    }
}

void Ingrediente::set_pret(const float pret) {
    if (pret <= 0) {
        throw ExceptionInput("Pretul trebuie sa fie mai mare decat 0.");
    } else {
        this->pret = pret;
    }
}

void Ingrediente::set_cantitate(const float cantitate) {
    if (cantitate < 0) {
        throw ExceptionInput("Cantitatea ingredientului trebuie sa fie mai mare decat 0.");
    } else {
        this->cantitate = cantitate;
    }
}

void Ingrediente::set_alergen(const bool alergen) {
    this->alergen = alergen;
}

char *Ingrediente::get_numeIngredient() const {
    return this->numeIngredient;
}

float Ingrediente::get_kcalorii() const {
    return this->kcalorii;
}

float Ingrediente::get_pret() const {
    return this->pret;
}

float Ingrediente::get_cantitate() const {
    return this->cantitate;
}

bool Ingrediente::get_alergen() const {
    return this->alergen;
}


ostream &operator<<(ostream &out, const Ingrediente &a) {
    out << "\nNume ingredient: ";
    if(a.numeIngredient!= nullptr)
    {
        out<<a.numeIngredient;
    }
    else
    {
        throw ExceptionInput("Ingredientul nu are nume.");
    }
    out << "\nCantitate: " << a.cantitate;
    out << "\nCalorii: " << a.CalculeazaCalorii();
    out << "\nPret: " << a.CalculeazaPret();
    out << "\nAlergen: ";
    if (a.alergen) {
        out << "Da";
    } else {
        out << "Nu";
    }

    return out;
}


float Ingrediente::CalculeazaCalorii() const {
    return this->cantitate / this->kcalorii;
}

float Ingrediente::CalculeazaPret() const {
    return float(this->cantitate / 100) * this->pret;
}
