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

    Comanda(const int id, std::vector<std::string> &listaPreparate, float sumaDePlata, metodaPlata plata);

    void set_listaPreparate(std::vector<std::string> &listaPreparate);

    void set_sumaDePlata(float sumadeplata);

    void set_plata(metodaPlata plata);

    std::vector<std::string> get_listaPreparate() const;

    float get_sumaDePlata() const;

    metodaPlata get_plata() const;

    void adaugaLaComanda(std::string denumirePreparat, std::vector<Preparat> listaPreparate);

    void stergeDinComanda(std::string denumirePreparat); //todo

    ~Comanda();

    friend std::istream &operator>>(std::istream &in, Comanda &comanda);

    friend std::ostream &operator<<(std::ostream &out, const Comanda &comanda);

    Comanda(const Comanda &comanda);

    Comanda &operator=(const Comanda &comanda);

    bool operator==(const Comanda &comanda);
};
