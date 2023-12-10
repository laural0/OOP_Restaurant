//
// Created by Laura on 12/5/2023.
//

#include "Ingrediente.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "../Helper/Helper.h"

void Ingredient::convertLowercase(char *sir) {
    char *p = sir;
    for (; *p; ++p) *p = tolower(*p);
}

Ingredient::Ingredient() {
    std::cout << "constructor fara parametri";
}

Ingredient::Ingredient(const char *denumire) {
    if (denumire == nullptr) {
        throw ExceptionInput("Denumirea ingredientului nu poate fi nula.");

    } else {
        this->denumire = new char[strlen(denumire) + 1];
        strcpy(this->denumire, denumire);

        convertLowercase(this->denumire);
    }
}

Ingredient::Ingredient(char const *numeIngredient, float calorii, float pret, float stoc, bool alergen) {
    if (numeIngredient == nullptr) {
        throw ExceptionInput("Atributul este null.");
    } else {
        this->denumire = new char[strlen(numeIngredient) + 1];
        strcpy(this->denumire, numeIngredient);

        convertLowercase(this->denumire);
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
    if (stoc < 0) {
        throw ExceptionInput("Stocul ingredientului trebuie sa fie mai mare decat 0.");
    } else {
        this->stoc = stoc;
    }
    this->alergen = alergen;
}

Ingredient::Ingredient(Ingredient const &ingredient) {


    if (this->denumire != nullptr) {
        delete[] this->denumire;
        this->denumire = nullptr;
    }
    if (ingredient.denumire == nullptr) {
        throw ExceptionInput("Denumirea este nula.");
    } else {
        this->denumire = new char[strlen(ingredient.denumire) + 1];
        strcpy(this->denumire, ingredient.denumire);
    }

    this->kcalorii = ingredient.kcalorii;
    this->pret = ingredient.pret;
    this->stoc = ingredient.stoc;
    this->alergen = ingredient.alergen;

}

Ingredient::~Ingredient() {
    delete[] denumire;
    denumire = nullptr;
}

void Ingredient::set_denumire(const char *numeIngredient) {
    if (this->denumire != nullptr) {
        delete[] this->denumire;
        this->denumire = nullptr;
    }
    if (numeIngredient == nullptr) {
        throw ExceptionInput("Atributul este null.");
    } else {
        this->denumire = new char[strlen(numeIngredient) + 1];
        strcpy(this->denumire, numeIngredient);

        convertLowercase(this->denumire);
    }
}

void Ingredient::set_kcalorii(const float kcalorii) {
    if (kcalorii <= 0) {
        throw ExceptionInput("Caloriile trebuie sa fie mai mari decat 0.");

    } else {
        this->kcalorii = kcalorii;
    }
}

void Ingredient::set_pret(const float pret) {
    if (pret <= 0) {
        throw ExceptionInput("Pretul trebuie sa fie mai mare decat 0.");
    } else {
        this->pret = pret;
    }
}

void Ingredient::set_stoc(const float stoc) {
    if (stoc < 0) {
        throw ExceptionInput("Stocul ingredientului trebuie sa fie mai mare decat 0.");
    } else {
        this->stoc = stoc;
    }
}

void Ingredient::set_alergen(const bool alergen) {
    this->alergen = alergen;
}

char *Ingredient::get_numeIngredient() const {
    return this->denumire;
}

float Ingredient::get_kcalorii() const {
    return this->kcalorii;
}

float Ingredient::get_pret() const {
    return this->pret;
}

float Ingredient::get_stoc() const {
    return this->stoc;
}

bool Ingredient::get_alergen() const {
    return this->alergen;
}


std::ostream &operator<<(std::ostream &out, const Ingredient &a) {
    out << "\nNume ingredient: " << a.denumire;
    out << "\nStoc: " << a.stoc;
    out << "\nCalorii: " << a.kcalorii;
    out << "\nPret: " << a.pret;
    out << "\nAlergen: ";
    if (a.alergen) {
        out << "Da";
    } else {
        out << "Nu";
    }

    return out;
}

std::istream &operator>>(std::istream &in, Ingredient &ingredient) {
    if (ingredient.denumire != nullptr) {
        delete[] ingredient.denumire;
        ingredient.denumire = nullptr;
    }

    std::cout << "\nDenumire: ";
    std::string buffer;
    in >> buffer;

    ingredient.denumire = new char[buffer.size() + 1];
    strcpy(ingredient.denumire, buffer.data());

    ingredient.convertLowercase(ingredient.denumire);

    std::cout << "\nCalorii: ";
    in >> ingredient.kcalorii;

    if (ingredient.kcalorii <= 0) {
        throw ExceptionInput("Caloriile trebuie sa fie mai mari decat 0.");
    }

    std::cout << "\nPret: ";
    in >> ingredient.pret;

    if (ingredient.pret <= 0) {
        throw ExceptionInput("Pretul trebuie sa fie mai mare decat 0.");
    }
    std::cout << "\nStoc: 1000";
    ingredient.stoc = 1000;

    char response;

    std::cout << "\nEste alergen? y/n  ";
    in >> response;
    if (response == 'y') {
        ingredient.alergen = true;
    } else {
        ingredient.alergen = false;
    }

    return in;
}



//float Ingredient::CalculeazaCalorii() const {
//    return this->stoc / this->kcalorii;
//}
//
//float Ingredient::CalculeazaPret() const {
//    return float(this->stoc / 100) * this->pret;
//}


int Ingredient::cautaLinieIngredient() {

    std::fstream fisier;
    fisier.open("C:\\Users\\alex\\CLionProjects\\OOP_Restaurant\\Ingredient\\Ingredient.csv", std::ios::in);

    std::string line;

    if (!fisier.is_open()) { throw ExceptionInput("Nu s-a putut deschide fisierul."); }
    if (this->denumire == nullptr) { throw ExceptionInput("Denumirea este nula."); }

    std::getline(fisier, line);
    std::stringstream lineS(line);
    std::string cell;

    int numarLinie = 1;
    while (std::getline(fisier, line)) {
        std::stringstream lineS(line);
        numarLinie++;
        int column = 0;
        while (std::getline(lineS, cell, ',') && column <= 1) {
            column++;
            if (cell == this->denumire)
                return numarLinie;
        }
    }

    fisier.close();
    return -1;
}

void Ingredient::adaugaIngredient() {
    int linie = this->cautaLinieIngredient();
    if (linie != -1) {
        std::cout << "Ingredientul " << this->denumire
                  << " a fost deja inregistrat in stoc! Doresti sa il actualizezi ? Y/N ";
        char response;
        std::cin >> response;
        if (response == 'Y') {
            this->actualizeazaIngredient(linie);
            std::cout << "Ingredient actualizat cu succes!";
        }

    } else {
        this->inregistreazaIngredient();
        std::cout << "Ingredient inregistrat cu succes!";
    }

}

void Ingredient::inregistreazaIngredient() {
    std::fstream fisier;

    fisier.open("Ingredient.csv", std::ios::app);

    fisier << this->denumire << ", "
           << this->kcalorii << ", "
           << this->pret << ", "
           << this->stoc << ", "
           << this->alergen
           << "\n";

    fisier.close();

}

void Ingredient::actualizeazaIngredient(int linie) {
    std::fstream fisier, fisierUpdate;

    fisier.open("Ingredient.csv", std::ios::in);
    fisierUpdate.open("IngredientNou.csv", std::ios::out);

    std::string line;
    std::vector<std::string> lines;

    while (getline(fisier, line)) {
        lines.push_back(line);
    }

    for (int i = 0; i < linie - 1; i++)
        fisierUpdate << lines[i] << "\n";

    fisierUpdate << this->denumire << ", "
                 << this->kcalorii << ", "
                 << this->pret << ", "
                 << this->stoc << ", "
                 << this->alergen
                 << "\n";

    for (int i = linie + 1; i < lines.size(); i++)
        fisierUpdate << lines[i] << "\n";

    fisier.close();
    fisierUpdate.close();

    remove("Ingredient.csv");
    rename("IngredientNou.csv", "Ingredient.csv");

}

bool Ingredient::operator<(const Ingredient &ingredient) const {
    return this->pret < ingredient.pret;
}

Ingredient &Ingredient::operator=(const Ingredient &ingredient) {
    delete[] this->denumire;
    this->denumire = nullptr;

    this->denumire = ingredient.denumire;
    this->kcalorii = ingredient.kcalorii;
    this->pret = ingredient.pret;
    this->stoc = ingredient.stoc;
    this->alergen = ingredient.alergen;

    return *this;
}

std::vector<Ingredient> Ingredient::getListaIngrediente() {
    std::fstream fisier;

    fisier.open("C:\\Users\\alex\\CLionProjects\\OOP_Restaurant\\Ingredient\\Ingredient.csv", std::ios::in);

    std::string line;
    std::vector<std::string> lista;
    std::vector<Ingredient> listaIngrediente;
    while (getline(fisier, line)) {
        lista = stringParse(line, ','); //aici am fiecare element din ingredient sub format string
        bool dePost;
        if (lista.size() >= 5) {
            bool dePost = (lista[4] == "false") ? false : true;
            Ingredient ingredient(lista[0].c_str(), stof(lista[1]), stof(lista[2]), stof(lista[3]), dePost);
            listaIngrediente.push_back(ingredient);

        } else {
            throw ExceptionInput("Vectorul nu are dimensiunea potrivita.");
        }
    }

    fisier.close();
    return listaIngrediente;

}



