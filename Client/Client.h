//
// Created by Laura on 12/10/2023.
//

#ifndef PROIECT_OOP_CLIENT_H
#define PROIECT_OOP_CLIENT_H

#include<iostream>
#include "../Comanda/Comanda.h"
#include<list>

class Client {
    std::string nume;
    std::string prenume;
    const std::string email;
    std::map<int, Comanda> comenziDate;
public:
    Client(const std::string &email);

    Client(const std::string &nume, const std::string &prenume, const std::string &email, std::map<int, Comanda> comenziDate);

    Client(const Client &client);

    void set_nume(const std::string &nume);

    void set_prenume(const std::string &prenume);

    void set_comenziDate(const std::map<int, Comanda> &comenziDate);

    void adaugaComandaLaClient(int id, const Comanda &comanda);

    static void raportClienti(const std::vector<Client>&clienti);

    std::string get_nume() const;

    std::string get_email() const;

    std::string get_prenume() const;

    std::map<int, Comanda> get_comenziDate() const;

    friend std::ostream &operator<<(std::ostream &out, const Client &client);

    friend std::istream &operator>>(std::istream &in, Client &client);

    Client& operator=(const Client &client);

    std::pair<std::string,int> preparatFavorit();

    ~Client();

};


#endif //PROIECT_OOP_CLIENT_H
