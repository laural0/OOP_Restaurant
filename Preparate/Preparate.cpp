//
// Created by Laura on 12/5/2023.
//

#include "Preparate.h"
#include "../Helper/Helper.h"
#include <sstream>
#include <vector>
#include <fstream>
#include <memory>
#include <limits>

float Preparat::adaosComercial = 400;

Preparat::Preparat() = default;

Preparat::Preparat(const std::string &numePreparat) : denumire(numePreparat) {

}

Preparat::Preparat(const std::string &numePreparat, const std::vector<Ingredient> &reteta, bool alergen) : reteta(
        reteta), esteAlergen(alergen) {

    this->denumire = numePreparat;
}

Preparat::Preparat(const Preparat &preparat) {
    this->denumire = preparat.denumire;
    this->reteta = preparat.reteta;
    this->esteAlergen = preparat.esteAlergen;

}

Preparat::Preparat(Preparat &&sursa)
        : denumire(std::move(sursa.denumire)),
          reteta(std::move(sursa.reteta)),
          esteAlergen(sursa.esteAlergen) {

}

Preparat &Preparat::operator=(const Preparat &preparat){
    if(this!=&preparat){
        this->denumire=preparat.denumire;
        this->reteta=preparat.reteta;
        this->esteAlergen=preparat.esteAlergen;
    }
    return *this;
}

Preparat::~Preparat() = default;

void Preparat::set_denumire(const string &denumire) {
    this->denumire = denumire;
}


void Preparat::set_reteta(const std::vector<Ingredient> &reteta) {
    this->reteta = reteta;
}

void Preparat::set_adaosComercial(const float adaosComercial) {
    Preparat::adaosComercial = adaosComercial;
}

void Preparat::set_Alergen(const bool alergen) {
    this->esteAlergen = alergen;
}

string Preparat::get_denumire() const {
    return this->denumire;
}


std::vector<Ingredient> Preparat::get_reteta() const {
    return this->reteta;
}

float Preparat::get_adaosComercial() {
    return Preparat::adaosComercial;
}

bool Preparat::get_Alergen() const {
    return this->esteAlergen;
}

//Preparat &Preparat::getPreparat(std::string denumire) {
//
//}

bool Preparat::operator==(const Preparat &preparat) {
    if(denumire!=preparat.denumire)
        return false;
    else
    {
        for(int i=0;i<reteta.size();i++)
            if(this->reteta[i]!=preparat.reteta[i])
                return false;

    }
    return true;
}

//rezolvat
std::ostream &operator<<(std::ostream &out, const Preparat &preparat) {
    out << "\nNume preparat: ";
    out << preparat.denumire;

    out << "\nReteta: \n";
    for (auto const &it: preparat.reteta)
        out << "      -" << it.get_numeIngredient() << "(" << it.get_stoc() << ")" << "\n";
    out << "\nAlergen: ";
    if (preparat.esteAlergen) { out << "Da"; }
    else { out << "Nu"; }

    return out;
}

//rezolvat
std::istream &operator>>(std::istream &in, Preparat &preparat) {

    std::cout << "\nIntroduceti denumirea preparatului: ";

    std::getline(in, preparat.denumire);


    std::cout << "Lista ingrediente disponibile: \n";
    std::vector<Ingredient> lista = Ingredient::getListaIngrediente();

    for (int i = 0; i < lista.size(); i++) {
        if ((i + 1) % 3) {
            std::cout << "              " << i + 1 << ". " << lista[i].get_numeIngredient();
            if (lista[i].get_alergen())
                std::cout << "*" << "                ";
            else
                std::cout << "            ";
        } else
            std::cout << "                  " << i + 1 << ". " << lista[i].get_numeIngredient() << '\n';
    }

    std::cout << "\nCe ingrediente contine? Scrieti-le despartite printr-o virgula. \n";
    string listaCitita;
    std::getline(in, listaCitita);

    std::vector<std::string> listaCititaConvertita;
    listaCititaConvertita = stringParse(listaCitita, ',');
    std::vector<int> answer;


    answer.reserve(listaCititaConvertita.size());
    for (auto const &numar: listaCititaConvertita)
        answer.push_back(stoi(numar));

    for (auto i: answer) {
        std::cout << "Cantitate pentru " << lista[i - 1].get_numeIngredient() << ": ";
        float cantitate;
        in >> cantitate;
        lista[i - 1].set_stoc(cantitate);
        if (lista[i - 1].get_alergen()) preparat.esteAlergen = true;
        preparat.reteta.push_back(lista[i - 1]);

        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return in;
}

float Preparat::calculeazaPret() {
    float sumaTotala=0;
    for(int i=0;i<this->reteta.size();i++)
        sumaTotala+=this->reteta[i].get_pret()*(this->reteta[i].get_stoc()/100);

    return sumaTotala;
}

float Preparat::calculeazaCalorii() {
    float caloriiTotale=0;
    for(int i=0;i<reteta.size();i++)
        caloriiTotale+=reteta[i].get_kcalorii()*(reteta[i].get_stoc()/100);

    return caloriiTotale;
}


void Preparat::adaugaPreparat(Preparat preparat) {

    int tipDePreparat;

    std::cout<<"1 - pentru mancare";
    std::cout<<"2 - pentru bautura";

    std::cin>>tipDePreparat;
    if(tipDePreparat==1 || tipDePreparat==2) {

        std::ofstream fisier;
        if(tipDePreparat==1) {
            fisier.open("..//Preparate//Mancare.csv", std::ios::app);
            if (!fisier.is_open())
                throw ExceptionInput("Fisierul Mancare.csv nu a putut fi deschis");
        }
        else
        {
            fisier.open("..//Preparate//Bautura.csv", std::ios::app);
            if (!fisier.is_open())
                throw ExceptionInput("Fisierul Bautura.csv nu a putut fi deschis");
        }

        fisier << '\n';
        fisier << preparat.denumire << ";";

        for (int i = 0; i < preparat.reteta.size(); i++) {
            fisier << preparat.reteta[i].get_numeIngredient() << ","
                   << preparat.reteta[i].get_stoc() << ","
                   << (preparat.reteta[i].get_alergen() ? "true" : "false");
            if (i < preparat.reteta.size() - 1)
                fisier << ";";
        }
        fisier.close();
    }
}

bool Preparat::verificaStocIngrediente(const Preparat &preparat) {
    for (const auto &ingredient: preparat.get_reteta())
        if (!Ingredient::verificaInStoc(ingredient)) return false;

    return true;
}

void Preparat::modificaStocIngrediente(const Preparat &preparat, const std::string &flag) {

    for (auto const &ingredient: preparat.get_reteta()) {
        Ingredient::modificaStoc(ingredient, flag);
    }

}


