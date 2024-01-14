//
// Created by Laura on 12/5/2023.
//

#include "Ingrediente.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "../Helper/Helper.h"
#include <iomanip>


void Ingredient::convertLowercase(std::string &sir) {
    for (int i = 0; i < sir.size(); i++)
        tolower(sir[i]);
}

Ingredient::Ingredient() {

}

Ingredient::Ingredient(const std::string denumire) {
    this->denumire = denumire;
}

Ingredient::Ingredient(const std::string numeIngredient, float calorii, float pret, float stoc, bool alergen) {
    this->denumire = numeIngredient;
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

    this->denumire = ingredient.denumire;
    this->kcalorii = ingredient.kcalorii;
    this->pret = ingredient.pret;
    this->stoc = ingredient.stoc;
    this->alergen = ingredient.alergen;

}

Ingredient::~Ingredient() {

}

void Ingredient::set_denumire(const std::string numeIngredient) {

    this->denumire = numeIngredient;
    convertLowercase(this->denumire);

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

std::string Ingredient::get_numeIngredient() const {
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

bool Ingredient::operator!=(const Ingredient &ingredient) {
    if (denumire == ingredient.denumire || kcalorii == ingredient.kcalorii ||
        stoc == ingredient.stoc || pret == ingredient.pret || alergen == ingredient.alergen)
        return false;
    return true;
}

std::istream &operator>>(std::istream &in, Ingredient &ingredient) {

    std::cout << "\nDenumire: ";
    std::getline(in, ingredient.denumire);
    ingredient.convertLowercase(ingredient.denumire);

    std::cout << "Calorii: ";
    in >> ingredient.kcalorii;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignoră restul liniei, inclusiv newline


    if (ingredient.kcalorii <= 0) {
        throw ExceptionInput("Caloriile trebuie sa fie mai mari decat 0.");
    }
    std::cout << "Pret: ";
    in >> ingredient.pret;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignoră restul liniei, inclusiv newline


    if (ingredient.pret <= 0) {
        throw ExceptionInput("Pretul trebuie sa fie mai mare decat 0.");
    }

    std::cout << "Stoc: ";
    in >> ingredient.stoc;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignoră restul liniei, inclusiv newline


    if (ingredient.stoc <= 0) {
        throw ExceptionInput("Stocul trebuie sa fie mai mare decat 0.");
    }

    char response;

    std::cout << "Este alergen? y/n";
    in >> response;
    if (response == 'y') {
        ingredient.alergen = true;
    } else {
        ingredient.alergen = false;
    }
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignoră restul liniei, inclusiv newline

    return in;
}



//float Ingredient::CalculeazaCalorii() const {
//    return this->stoc / this->kcalorii;
//}
//
//float Ingredient::CalculeazaPret() const {
//    return float(this->stoc / 100) * this->pret;
//}


int Ingredient::cautaLinieIngredient(std::string denumire) {

    std::fstream fisier;
    fisier.open("..//Ingredient//Ingredient.csv", std::ios::in);

    std::string line;

    if (!fisier.is_open()) { throw ExceptionInput("Nu s-a putut deschide fisierul."); }

    int numarLinie = 0;

    while (std::getline(fisier, line)) {
        std::stringstream lineS(line);
        std::string cell;
        numarLinie++;
        int column = 0;
        while (std::getline(lineS, cell, ',') && column <= 1) {
            column++;
            if (cell == denumire)
                return numarLinie;
        }
    }

    fisier.close();
    return -1;
}

void Ingredient::adaugaIngredient() {
    int linie = Ingredient::cautaLinieIngredient(this->denumire);
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

    fisier.open("..//Ingredient//Ingredient.csv", std::ios::app);

    fisier << this->denumire << ","
           << this->kcalorii << ","
           << this->pret << ","
           << this->stoc << ","
           << this->alergen
           << "\n";

    fisier.close();

}

void Ingredient::actualizeazaIngredient(int linie) {
    std::fstream fisier, fisierUpdate;

    fisier.open("..//Ingredient//Ingredient.csv", std::ios::in);
    fisierUpdate.open("..//Ingredient//IngredientNou.csv", std::ios::out);

    std::string line;
    std::vector<std::string> lines;

    while (getline(fisier, line)) {
        lines.push_back(line);
    }

    for (int i = 0; i < linie - 1; i++)
        fisierUpdate << lines[i] << "\n";

    std::string alergen;
    if (this->alergen == 1)
        alergen = "true";
    else
        alergen = "false";
    fisierUpdate << this->denumire << ","
                 << this->kcalorii << ","
                 << this->pret << ","
                 << this->stoc << ","
                 << alergen
                 << "\n";

    for (int i = linie + 1; i < lines.size(); i++)
        fisierUpdate << lines[i] << "\n";

    fisier.close();
    fisierUpdate.close();

    remove("..//Ingredient//Ingredient.csv");
    rename("..//Ingredient//IngredientNou.csv", "..//Ingredient//Ingredient.csv");

}

bool Ingredient::operator<(const Ingredient &ingredient) const {
    return this->pret < ingredient.pret;
}

Ingredient &Ingredient::operator=(const Ingredient &ingredient) {
    if (this != &ingredient) {
        this->denumire = ingredient.denumire;
        this->kcalorii = ingredient.kcalorii;
        this->pret = ingredient.pret;
        this->stoc = ingredient.stoc;
        this->alergen = ingredient.alergen;
    }

    return *this;
}

std::vector<Ingredient> Ingredient::getListaIngrediente() {
    std::fstream fisier;

    fisier.open("..//Ingredient//Ingredient.csv", std::ios::in);

    std::string line;
    std::vector<std::string> lista;
    std::vector<Ingredient> listaIngrediente;
    while (getline(fisier, line)) {
        lista = stringParse(line, ','); //aici am fiecare element din ingredient sub format string
        bool alergen;
        if (lista.size() >= 5) {
            bool dePost = (lista[4] == "false") ? false : true;
            Ingredient ingredient(lista[0], stof(lista[1]), stof(lista[2]), stof(lista[3]), alergen);
            listaIngrediente.push_back(ingredient);

        } else {
            throw ExceptionInput("Vectorul nu are dimensiunea potrivita.");
        }
    }

    fisier.close();
    return listaIngrediente;

}

//functie destinata clasei comanda
bool Ingredient::verificaInStoc(const Ingredient &ingredient) {

    std::fstream fisier;
    fisier.open("..//Ingredient//Ingredient.csv", std::ios::in);
    if(!fisier.is_open()){throw ExceptionInput("Fisierul Ingredient.csv nu a putut fi deschis.");}

    std::string line;
    std::vector<std::string> lista;

    while (getline(fisier, line)) {
        lista = stringParse(line, ','); //aici am fiecare element din ingredient sub format string
        if (!lista.empty() && lista.size()==5) {
            if (stof(lista[3]) < ingredient.stoc) return false;
        }
    }

    fisier.close();
    return true;
}

//doar daca exista in lista
Ingredient Ingredient::getIngredientDinLista(int linieDinFisier) {
    std::fstream fisier;
    fisier.open("..//Ingredient//Ingredient.csv", std::ios::in);

    std::string line;
    std::vector<std::string> lista;

    Ingredient ingredient;
    int index = 0;

    while (getline(fisier, line)) {
        index++;
        if (index == linieDinFisier) {
            lista = stringParse(line, ','); //aici am fiecare element din ingredient sub format string
            ingredient.set_denumire(lista[0]);
            ingredient.set_kcalorii(stof(lista[1]));
            ingredient.set_pret(stof(lista[2]));
            ingredient.set_stoc(stof(lista[3]));
            ingredient.set_alergen(lista[4] == "true");
            break;
        }
    }

    fisier.close();
    return ingredient;
}

void Ingredient::modificaStoc(const Ingredient &ingredient, const std::string &flag) {

    std::fstream fisier;
    std::fstream fisierUpdate;
    std::fstream raportStoc;


    raportStoc.open("..//Rapoarte//ModificareStoc.txt", std::ios::app);
    fisier.open("..//Ingredient//Ingredient.csv", std::ios::in);
    fisierUpdate.open("..//Ingredient//IngredientNou.csv", std::ios::out);

    raportStoc << std::setw(21) << ingredient.denumire;
    raportStoc << std::setw(15) << (flag == "minus" ? "scadere" : "adaugare");
    raportStoc << std::setw(10) << ingredient.stoc;
    raportStoc << std::setw(30) << dataCurenta() << '\n';


    std::string line;
    std::vector<std::string> lines;

    while (getline(fisier, line)) {
        if(!line.empty())
            lines.push_back(line);
    }

    for (int i = 0; i < lines.size(); i++) {
        std::vector<std::string> parsedLine;
        parsedLine = stringParse(lines[i], ','); //aici am fiecare element din ingredient sub format string
        if (parsedLine[0] == ingredient.denumire) {
            float stocNou;
            if (flag == "minus") {
                stocNou = stof(parsedLine[3]) - ingredient.stoc;
            } else {
                stocNou = stof(parsedLine[3]) + ingredient.stoc;
            }
            std::string alergen;
            if (ingredient.alergen == 1)
                alergen = "true";
            else
                alergen = "false";


            fisierUpdate << ingredient.denumire << ","
                         << parsedLine[1] << ","
                         << parsedLine[2] << ","
                         << stocNou << ","
                         << alergen
                         << "\n";
        } else { fisierUpdate << lines[i] << "\n"; }
    }
    fisier.close();
    fisierUpdate.close();
    raportStoc.close();

    remove("..//Ingredient//Ingredient.csv");
    rename("..//Ingredient//IngredientNou.csv", "..//Ingredient//Ingredient.csv");

}




