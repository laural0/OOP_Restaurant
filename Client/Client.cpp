//
// Created by Laura on 12/10/2023.
//

#include "Client.h"
#include<iostream>
#include <algorithm>
#include "../ExceptionInput/ExceptionInput.h"
#include<fstream>
#include <iomanip>

Client::Client(const std::string &email) : email(email) {}

Client::Client(const std::string &nume, const std::string &prenume, const std::string &email,
               std::map<int, Comanda> comenziDate) : email(
        email) {
    this->nume = nume;
    this->prenume = prenume;

    this->comenziDate = comenziDate;
}

Client::Client(const Client &client) : email(client.email) {
    this->nume = client.nume;
    this->prenume = client.prenume;

    this->comenziDate = client.comenziDate;

}

void Client::set_nume(const std::string &nume) {
    this->nume = nume;
}

void Client::set_prenume(const std::string &prenume) {
    this->prenume = prenume;
}

void Client::set_comenziDate(const std::map<int, Comanda> &comenziDate) {
    this->comenziDate = comenziDate;
}

std::string Client::get_nume() const {
    return this->nume;
}

std::string Client::get_email() const {
    return this->email;
}

std::string Client::get_prenume() const {
    return this->prenume;
}

std::map<int, Comanda> Client::get_comenziDate() const {
    return this->comenziDate;
}

void Client::adaugaComandaLaClient(int id, const Comanda &comanda) {
    auto iterator = comenziDate.find(id);

    if (iterator != comenziDate.end()) {
        std::cout << "Comanda cu id-ul " << id << " exista deja pentru acest client.\n";
    } else {
        comenziDate[id] = comanda;
        std::cout << "Comanda cu id-ul " << id << " a fost adăugată cu succes.\n";
    }
}


std::pair<std::string, int> Client::preparatFavorit() {
    std::map<std::string, int> contor;
    for (auto aux: this->comenziDate) {
        for (auto preparat: aux.second.get_listaPreparate())
            contor[preparat.get_denumire()]++;
    }
    int maxFrecventa = 0;
    std::string preparatFavorit;
    for (const auto &pair: contor) {
        if (pair.second > maxFrecventa) {
            maxFrecventa = pair.second;
            preparatFavorit = pair.first;
        }
    }

    return std::make_pair(preparatFavorit, maxFrecventa);

}

void Client::raportClienti(const std::vector<Client> &clienti) {

    std::fstream fisier;

    fisier.open("..//Rapoarte//Clienti.txt", std::ios::out);

    fisier<<"    NUME      |      PRENUME    |            EMAIL           |          NUMAR COMENZI DATE          |        PREPARAT FAVORIT         |        CUMPARAT         |\n";
    std::cout<<"    NUME       PRENUME           EMAIL            NUMAR COMENZI DATE          PREPARAT FAVORIT         CUMPARAT      \n";


    std::pair<std::string, int> preparatFavorit;
    for (auto client: clienti) {

        preparatFavorit = client.preparatFavorit();

        fisier << std::setw(10) << client.nume;
        fisier << std::setw(18) << client.prenume;
        fisier << std::setw(27) << client.email;
        fisier << std::setw(33) << client.comenziDate.size();
        fisier << std::setw(39) << preparatFavorit.first;
        fisier << std::setw(23) << preparatFavorit.second<<"\n";

        std::cout<<client.nume<<"       "<<client.prenume<<"        "<<client.email<<"          "<<client.comenziDate.size()<<"              "<<client.preparatFavorit().first<<"                   "<<client.preparatFavorit().second<<"\n";
    }

    fisier.close();
}

std::ostream &operator<<(std::ostream &out, const Client &client) {
    out << "Nume client: ";
    out << client.nume << "\n";
    out << "Prenume client: ";
    out << client.prenume << "\n";

    out << "Email: ";
    out << client.email << "\n";

    out << "Comenzi date: \n";
    auto it = client.comenziDate.begin();

    while (it != client.comenziDate.end()) {
        out << "      " << "\nId: " << it->first << "\n";
        std::vector<Preparat> preparate;
        preparate = it->second.get_listaPreparate();
        out << "      " << "Comanda: \n";
        for (int i = 0; i < preparate.size(); i++)
            out << "          " << i + 1 << ". " << preparate[i].get_denumire() << "\n";
        ++it;
    }


    return out;
}

std::istream &operator>>(std::istream &in, Client &client) {
    std::cout << "\nIntroduceti numele clientului:";
    in >> client.nume;

    std::cout << "Introduceti prenumele clientului:";
    in >> client.prenume;

    std::cout << "Email: ";
    std::cout << client.email;

    int id;
    Comanda element;
    std::cout << "\nNumar comenzi:";
    int numar;
    in >> numar;
    int i = 0;
    while (i < numar) {
        id = ++i;
        element.set_id(id);
        std::cout << "Cod comanda:#" << id << "\n";
        std::cout << "Introduceti detaliile comenzii:";
        in >> element;
        client.comenziDate[id] = element;
    }
    return in;
}

Client &Client::operator=(const Client &client) {
    if (this != &client) {

        this->nume = client.nume;
        this->prenume = client.prenume;
        this->comenziDate = client.comenziDate;
    }
    return *this;
}


Client::~Client() {}

