//
// Created by Laura on 12/4/2023.
//


#include<string>
#include<vector>
#include <cstring>
#include "../ExceptionInput/ExceptionInput.h"
#include "../Preparate/Preparate.h"

class Comanda {
    int id=0;
    std::vector<Preparat> listaPreparate;
    float sumaDePlata = 0.0;
    enum metodaPlata {
        byCash, byCard
    };
    metodaPlata plata; //todo: verific ca plata sa aiba doar valoarea 1 sau 0

public:
    Comanda();

    Comanda(int id) : id(id) {}

    Comanda(int id, const std::vector<Preparat> &listaPreparate, float sumaDePlata, metodaPlata plata);

    Comanda(Comanda &&sursa);

    void set_listaPreparate(const std::vector<Preparat> &listaPreparate);

    void set_sumaDePlata(float sumadeplata);

    void set_plata(metodaPlata plata);

    void set_id(int id);

    std::vector<Preparat> get_listaPreparate() const;

    float get_sumaDePlata() const;

    metodaPlata get_plata() const;

    float get_caloriiTotale();

    float calculeazaSumaDePlata();

    void adaugaLaComanda(const Preparat &preparat);

    void stergeDinComanda(const Preparat &preparat);

    ~Comanda();

    friend std::istream &operator>>(std::istream &in, Comanda &comanda);

    friend std::ostream &operator<<(std::ostream &out, const Comanda &comanda);

    Comanda(const Comanda &comanda);

    Comanda &operator=(const Comanda &comanda);

    bool operator==(const Comanda &comanda);

    static void raportFrecventaPreparate(const std::vector<Comanda>& comenzi);

    static void genereazaRaportComenzi(const Comanda *comanda);
};
