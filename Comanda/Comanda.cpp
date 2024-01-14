//
// Created by Laura on 12/4/2023.
//

#include "Comanda.h"
#include "../Meniu/Meniu.h"
#include "../Helper/Helper.h"
#include<fstream>
#include<algorithm>
#include <iomanip>


Comanda::Comanda() {}

Comanda::Comanda(int id, const std::vector<Preparat> &listaPreparate,
                 float sumaDePlata, metodaPlata plata) : id(id), listaPreparate(listaPreparate) {

    if (sumaDePlata < 0)
        throw ExceptionInput("Nota trebuie sa fie pozitiva!");
    else
        this->sumaDePlata = sumaDePlata;

    if (plata == byCash || plata == byCard)
        this->plata = plata;
    else
        throw ExceptionInput("Metoda de plata invalida!.");


}

void Comanda::set_id(int id) {
    this->id=id;
}

Comanda::Comanda(Comanda &&sursa)
        : id(sursa.id),
          listaPreparate(std::move(sursa.listaPreparate)),
          sumaDePlata(sursa.sumaDePlata),
          plata(sursa.plata) {

}

void Comanda::genereazaRaportComenzi(const Comanda *comanda) {
    std::fstream raport;
    raport.open("..//Rapoarte//ComenziInregistrate.txt", std::ios::app);

    if (comanda->id != 0 && comanda->sumaDePlata != 0 && !comanda->listaPreparate.empty()) {
        raport << std::setw(10) << comanda->id;
        raport << std::setw(22) << comanda->sumaDePlata;
        raport << std::setw(26) << dataCurenta() << "\n";
    }

    raport.close();

}

void Comanda::set_listaPreparate(const std::vector<Preparat> &listaPreparate) {
    this->listaPreparate = listaPreparate;
}

void Comanda::set_sumaDePlata(float sumadeplata) {
    if (sumadeplata > 0)
        this->sumaDePlata = sumadeplata;
    else
        throw ExceptionInput("Nota trebuie sa fie pozitiva!");
}

void Comanda::set_plata(metodaPlata plata) {
    if (plata == byCard || plata == byCard) {
        this->plata = plata;
    } else {
        throw ExceptionInput("Metoda de plata invalida!");
    }
}

std::vector<Preparat> Comanda::get_listaPreparate() const {
    return this->listaPreparate;
}

float Comanda::get_sumaDePlata() const {
    return this->sumaDePlata;
}

Comanda::metodaPlata Comanda::get_plata() const {
    return this->plata;
}

void Comanda::adaugaLaComanda(const Preparat &preparat) {


    bool inStoc = Preparat::verificaStocIngrediente(preparat);
    if (inStoc) {
        Preparat::modificaStocIngrediente(preparat, "minus");
        this->listaPreparate.push_back(preparat);
        sumaDePlata = calculeazaSumaDePlata();
    } else
        throw ExceptionInput("Stoc insuficient!");


}

void Comanda::stergeDinComanda(const Preparat &preparat) {


    Preparat::modificaStocIngrediente(preparat, "plus");
    for (int i = 0; i < listaPreparate.size(); i++)
        if (listaPreparate[i] == preparat) {
            this->listaPreparate.erase(listaPreparate.begin() + i - 1);
            sumaDePlata = calculeazaSumaDePlata();
            std::cout << "Preparat eliminat cu succes!";
            break;
        }


}

void Comanda::raportFrecventaPreparate(const std::vector<Comanda> &comenzi) {

    std::fstream raportTopPreparate;
    raportTopPreparate.open("..//Rapoarte//TopPreparate.txt", std::ios::app);

    std::map<std::string, int> contorPreparate;

    for (const auto &comanda: comenzi) {
        for (const auto &preparat: comanda.listaPreparate) {
            contorPreparate[preparat.get_denumire()]++;
        }
    }

    std::vector<std::pair<std::string, int>> aux;
    for (auto it2 = contorPreparate.begin(); it2 != contorPreparate.end(); it2++)
        aux.push_back(make_pair(it2->first, it2->second));

    std::sort(aux.begin(), aux.end(), sortMapByVal);


    std::cout << "Raportul top preparate:\n";
    for (int i = 0; i < aux.size(); i++) {
        std::cout << "Preparat: " << aux[i].first << ", Aparitii: " << aux[i].second << "\n";
    }
    for (int i = 0; i < aux.size(); i++) {
        raportTopPreparate << "\n";
        raportTopPreparate << std::setw(21) << aux[i].first;
        raportTopPreparate << std::setw(15) << aux[i].second;
    }

    raportTopPreparate.close();
}


std::istream &operator>>(std::istream &in, Comanda &comanda) {

    std::cout<<"\nIntroduceti id-ul comenzii:";
    in>>comanda.id;

    Meniu::afiseazaMeniu();

    std::vector<Preparat> listameniuMancare;
    std::vector<Preparat> listameniuBauturi;

    listameniuMancare = Meniu::getListaMancare();
    listameniuBauturi = Meniu::getListaBauturi();

    std::vector<Preparat> listameniu;
    listameniu.reserve(listameniuBauturi.size() + listameniuMancare.size());
    listameniu.insert(listameniu.end(), listameniuMancare.begin(), listameniuMancare.end());
    listameniu.insert(listameniu.end(), listameniuBauturi.begin(), listameniuBauturi.end());

    std::cout << "\nIntroduceti codurile preparatelor pe care le doriti separate de virgula:";
    std::string raspuns;

    in >> raspuns;
    std::vector<std::string> raspunsParsat;
    raspunsParsat = stringParse(raspuns, ',');

    std::vector<int> raspunsConvertit;
    raspunsConvertit.reserve(raspunsParsat.size());
    for (auto const &i: raspunsParsat)
        raspunsConvertit.push_back(stoi(i));


    for (auto index: raspunsConvertit) {
        if (Preparat::verificaStocIngrediente(listameniu[index - 1])) {
            comanda.listaPreparate.push_back(listameniu[index - 1]);
            Preparat::modificaStocIngrediente(listameniu[index - 1], "minus");
            for (int i = 0; i < listameniu[index - 1].get_reteta().size(); i++) {
                {
                    int locatieIngredient = Ingredient::cautaLinieIngredient(
                            listameniu[index - 1].get_reteta()[i].get_numeIngredient());
                    Ingredient ingredientAuxiliar;
                    ingredientAuxiliar = Ingredient::getIngredientDinLista(locatieIngredient);
                    comanda.sumaDePlata +=
                            listameniu[index - 1].get_reteta()[i].get_stoc() / 100 * ingredientAuxiliar.get_pret();
                }
            }
            comanda.sumaDePlata += Preparat::get_adaosComercial();
        } else
            std::cout << "Nu este suficient stoc pentru preparatul " << listameniu[index - 1].get_denumire();
    }


    std::cout << "\nSuma totala de plata: ";
    std::cout << comanda.sumaDePlata;

    if (comanda.sumaDePlata) {
        std::cout << "\nMetoda de plata: Cash/Card. \nPentru cash inserati - 0 ; \nPentru card inserati - 1 ;\n";
        std::cout << "Optiunea:";
        int metodaPlata;
        in >> metodaPlata;
        if (metodaPlata == 0) {
            comanda.plata = Comanda::byCash;
        } else {
            comanda.plata = Comanda::byCard;
        }
    }

    return in;
}

std::ostream &operator<<(std::ostream &out, const Comanda &comanda) {
    out << "\nCod comanda:" << comanda.id;
    out << "\nLista de preparate:";
    for (int i = 0; i < comanda.listaPreparate.size(); i++) {
        out << comanda.listaPreparate[i].get_denumire();
        if (i < comanda.listaPreparate.size() - 1) out << ", ";
    }

    out << "\nSuma totala de plata :" << comanda.sumaDePlata;
    if (comanda.plata == 0) {

        out << "\nMetoda de plata: CASH";
    } else {

        out << "\nMetoda de plata: CARD";
    }
    return out;
}

float Comanda::get_caloriiTotale() {
    float caloriiTotale = 0;
    for (auto preparat: this->listaPreparate)
        caloriiTotale += preparat.calculeazaCalorii();

    return caloriiTotale;
}

float Comanda::calculeazaSumaDePlata() {
    float sumaDePlata = 0;
    for (auto preparat: this->listaPreparate)
        sumaDePlata = sumaDePlata + preparat.calculeazaPret();

    return sumaDePlata + Preparat::get_adaosComercial();
}

Comanda::Comanda(const Comanda &comanda) : id(comanda.id) {

    this->listaPreparate = comanda.listaPreparate;
    this->sumaDePlata = comanda.sumaDePlata;
    this->plata = comanda.plata;
}

Comanda &Comanda::operator=(const Comanda &comanda) {
    if (this != &comanda) {

        this->listaPreparate = comanda.listaPreparate;
        this->sumaDePlata = comanda.sumaDePlata;
        this->plata = comanda.plata;
    }
    return *this;
}

bool Comanda::operator==(const Comanda &comanda) {
    if (this->listaPreparate.size() == comanda.listaPreparate.size())
        return true;
    return false;
}

Comanda::~Comanda() {
    genereazaRaportComenzi(this);
}
