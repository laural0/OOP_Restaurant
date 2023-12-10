//
// Created by Laura on 12/5/2023.
//

#include "Preparate.h"
#include "../Helper/Helper.h"
#include <sstream>
#include <vector>
#include <fstream>

float Preparat::adaosComercial = 400;

Preparat::Preparat() {}

Preparat::Preparat(char *numePreparat) {
    if (numePreparat != nullptr) {
        this->denumire = new char[strlen(numePreparat) + 1];
        strcpy(this->denumire, numePreparat);

        convertLowercase(this->denumire);
    } else {
        throw ExceptionInput("Numele preparatului nu poate fi null.");
    }
}

Preparat::Preparat(char *numePreparat, std::vector<Ingredient> &reteta, bool dePost) {
    if (numePreparat != nullptr) {
        this->denumire = new char[strlen(numePreparat) + 1];
        strcpy(this->denumire, numePreparat);

        convertLowercase(this->denumire);
    } else {
        throw ExceptionInput("Numele preparatului nu poate fi null.");
    }

    this->reteta = reteta;

    this->esteAlergen = dePost;
}

Preparat::Preparat(Preparat &preparat) {
    this->denumire = preparat.denumire;
    this->reteta = preparat.reteta;
    this->esteAlergen = preparat.esteAlergen;

}

Preparat::~Preparat() {
    delete[]this->denumire;
    this->denumire = nullptr;
}

void Preparat::set_denumire(const char *denumire) {
    if (denumire != nullptr) {
        this->denumire = new char[strlen(denumire) + 1];
        strcpy(this->denumire, denumire);

        convertLowercase(this->denumire);
    } else {
        throw ExceptionInput("Numele preparatului nu poate fi null.");
    }
}


void Preparat::set_reteta(const std::vector<Ingredient> &reteta) {
    this->reteta = reteta;
}

void Preparat::set_adaosComercial(const float adaosComercial) {
    Preparat::adaosComercial = adaosComercial;
}

void Preparat::set_dePost(const bool dePost) {
    this->esteAlergen = dePost;
}

char *Preparat::get_denumire() const {
    return this->denumire;
}


std::vector<Ingredient> Preparat::get_reteta() const {
    return this->reteta;
}

float Preparat::get_adaosComercial() {
    return Preparat::adaosComercial;
}

bool Preparat::get_dePost() const {
    return this->esteAlergen;
}

std::ostream &operator<<(std::ostream &out, const Preparat &preparat) {
    out << "\nNume preparat: ";
    if (preparat.denumire != nullptr) {
        out << preparat.denumire;
    } else {
        throw ExceptionInput("Numele preparatului nu poate fi null");
    }

    out << "\nReteta: ";
    for(auto it : preparat.reteta)
        out<<"      "<<it<<"\n";
    out << "\nDe post: ";
    if (preparat.esteAlergen) { out << "Da"; }
    else { out << "Nu"; }

    return out;
}

std::istream &operator>>(std::istream &in, Preparat &preparat) {
    if (preparat.denumire != nullptr) {
        delete[] preparat.denumire;
        preparat.denumire = nullptr;
    }

    std::cout << "\nIntroduceti denumirea preparatului: ";
    std::string buffer;
    in >> buffer;

    preparat.denumire = new char[buffer.size() + 1];
    strcpy(preparat.denumire, buffer.data());

    convertLowercase(preparat.denumire);

    std::cout << "\nSi acum ingredientele......";
    std::vector<Ingredient> lista = Ingredient::getListaIngrediente();
    for (int i = 0; i < lista.size(); i++)
        std::cout << i + 1 << ". " << lista[i] << "\n";

    std::cout << "Doriti sa adaugati un ingredient? Y/N\n";
    char response;
    std::cin >> response;
    response == 'Y' || response == 'y' ? response = true : response = false;
    if (response) {
        while (response) {


            Ingredient ingredientNou;
            std::cin >> ingredientNou;

            ingredientNou.adaugaIngredient();

            std::cout << "Doriti sa mai adaugati?\n";
            std::cin >> response;

        }
        std::cout << "Aceasta este lista actualizata: \n";
        lista = Ingredient::getListaIngrediente();
        for (int i = 0; i < lista.size(); i++)
            std::cout << "      " << i + 1 << ". " << lista[i] << "\n";
    }


    std::cout << "Ce ingrediente doriti sa includeti in noul preparat? Scrieti "
                 "numerele ingredientelor urmate de o virgula.\n";
    std::vector<int> answer;
    int index;
    while (std::cin >> index)
        answer.push_back(index);

    float cant;
    std::cout << "Introduceti cantitatile pentru fiecare ingredient! \n";
    for (int i = 0; i < answer.size(); i++) {
        std::cout << "  Pentru " << lista[answer[i] - 1].get_numeIngredient() << ": \n";
        in >> cant;
        lista[answer[i]-1].set_stoc(cant);
        preparat.reteta.push_back(lista[answer[i]-1]);

    }

    std::cout << "Este de post?  Y/N";
    char reponse;
    std::cin >> response;
    reponse == 'Y' || response == 'y' ? preparat.esteAlergen = true : preparat.esteAlergen = false;

    return in;
}

std::vector<Preparat> Preparat::getListaPreparate() {
    std::fstream fisier;

    fisier.open("Preparat.csv", std::ios::in);
    if(fisier.is_open())
        throw ExceptionInput("Fisierul nu a putut fi deschis");
    std::string line;
    int flag;
    std::vector<std::string> lineParsat;
    std::vector<Preparat> result;
    while (std::getline(fisier, line)) {

        Preparat p;

        lineParsat = stringParse(line, ';');
        for (int i = 0; i < lineParsat.size(); i++) //3k+1
        {
            Ingredient ingredient;
            if (i == 0)
                p.set_denumire(lineParsat[i].c_str());
            else {
                std::vector<std::string> ingredientNecesar;
                bool alergen;
                ingredientNecesar = stringParse(lineParsat[i], ',');
                ingredient.set_denumire(ingredientNecesar[0].c_str());
                ingredient.set_stoc(stof(ingredientNecesar[1]));
                if (ingredientNecesar[2] == "false")
                    alergen = false;
                else
                    alergen = true;

                ingredient.set_alergen(alergen);
            }
            p.reteta.push_back(ingredient);
        }
        for (int i = 0; i < p.reteta.size(); i++) {
            if (p.reteta[i].get_alergen() == true)
                p.esteAlergen = true;
            else
                p.esteAlergen = false;
        }
        //todo: result.push_back(p);
    }
    return result;

}

void Preparat::adaugaPreparat() {

}


