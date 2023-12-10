//
// Created by Laura on 12/4/2023.
//


#include<string>
#include<vector>
#include <cstring>
#include "../ExceptionInput/ExceptionInput.h"
#include "../Preparate/Preparate.h"

class Comanda {
    int id;

    std::vector<std::string> listaPreparate;
    float sumaDePlata = 0.0;
    enum metodaPlata {
        byCash, byCard
    };
    metodaPlata plata;

public:
    Comanda(const int id) : id(id) {}

    Comanda(const int id, std::vector<std::string> &listaPreparate,
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

    void set_listaPreparate(std::vector<std::string> &listaPreparate) {
        this->listaPreparate = listaPreparate;
    }

    void set_sumaDePlata(float sumadeplata) {
        if (sumadeplata > 0)
            this->sumaDePlata = sumadeplata;
        else
            throw ExceptionInput("Nota trebuie sa fie pozitiva!");
    }

    void set_plata(metodaPlata plata) {
        if (plata == byCard || plata == byCard) {
            this->plata = plata;
        } else {
            throw ExceptionInput("Metoda de plata invalida!");
        }
    }

    std::vector<std::string> get_listaPreparate() const {
        return this->listaPreparate;
    }

    float get_sumaDePlata() const {
        return this->sumaDePlata;
    }

    metodaPlata get_plata() const {
        return this->plata;
    }

    void adaugaLaComanda(std::string denumirePreparat, std::vector<Preparat> listaPreparate) {

        for (auto preparat: listaPreparate) {
            if (denumirePreparat == preparat.get_denumire()) {
                bool inStoc = Preparat::verificaStocIngrediente(preparat);
                if (inStoc) {
                    Preparat::modificaStocIngrediente(preparat, "minus");
                    this->listaPreparate.push_back(denumirePreparat);
                }
            }
        }

    }

    void stergeDinComanda(std::string denumirePreparat) {
//        for ()
    }


    ~Comanda() {}


    friend std::istream &operator>>(std::istream &in, Comanda &comanda) {

        std::cout
                << "\n Lista de ingrediente. Adaugati ingredientele dupa denumire, cand doriti sa terminati inserati done: ";
        std::string buffer;

        while (buffer != "done") {
            in >> buffer;
            if (buffer != "done") {

                comanda.listaPreparate.push_back(buffer);
                std::cout << "\n Adaugati alt ingredient. Daca doriti sa incheiati adaugarea, inserati done: ";
            }
        }

        std::cout << "\n Inserati suma totala de plata: ";
        in >> comanda.sumaDePlata;

        std::cout << "\n Metoda de plata: Cash/Card. Pentru cash inserati - 0 ; Pentru card inserati - 1: ";
        int metodaPlata;
        in >> metodaPlata;
        if (metodaPlata == 0) {
            comanda.plata = byCash;
        } else {
            comanda.plata = byCard;
        }

        return in;
    }


    friend std::ostream &operator<<(std::ostream &out, const Comanda &comanda) {
        out << "\n Lista de ingrediente : ";
        for (int i = 0; i < comanda.listaPreparate.size(); i++) {
            out << comanda.listaPreparate[i];
            if (i < comanda.listaPreparate.size() - 1) {
                out << ", ";
            } else {
                out << ".";
            }
        }
        out << "\n Suma totala de plata : " << comanda.sumaDePlata;
        if (comanda.plata == 0) {

            out << "\n Metoda de plata: CASH ";
        } else {

            out << "\n Metoda de plata: CARD ";
        }
        return out;
    }

    Comanda(Comanda const &comanda) {
        this->id = comanda.id;
        this->listaPreparate = comanda.listaPreparate;
        this->sumaDePlata = comanda.sumaDePlata;
        this->plata = comanda.plata;
    }


    Comanda &operator=(const Comanda &comanda) {
        this->id = comanda.id;
        this->listaPreparate = comanda.listaPreparate;
        this->sumaDePlata = comanda.sumaDePlata;
        this->plata = comanda.plata;
        return *this;
    }
};
