//
// Created by Laura on 12/10/2023.
//

#ifndef PROIECT_OOP_CLIENT_H
#define PROIECT_OOP_CLIENT_H

#include<iostream>

class Client {
    std::string nume;
    std::string prenume;
    const std::string email;
    int nrComenziDate;
public:
    Client(std::string email);

    Client(std::string nume, std::string prenume, std::string email, int nrComenzi);

    Client(const Client &client);

    void set_nume(const std::string nume);

    void set_prenume(const std::string prenume);

    void set_nrComenziDate(const int nrComenzi);

    std::string get_nume() const;

    std::string get_email() const;

    std::string get_prenume() const;

    int get_nrComenziDate() const;

    friend std::ostream &operator<<(std::ostream &out, const Client &client);

    friend std::istream &operator>>(std::istream &in, Client client);

    Client& operator=(const Client &client);

    Client &operator++();

    ~Client();

};


#endif //PROIECT_OOP_CLIENT_H
