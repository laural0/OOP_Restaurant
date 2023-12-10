//
// Created by Laura on 12/10/2023.
//

#include "Client.h"
#include<iostream>
#include "../ExceptionInput/ExceptionInput.h"

Client::Client(std::string email) : email(email) {}

Client::Client(std::string nume, std::string prenume, std::string email, int nrComenzi) : email(email) {
    this->nume = nume;
    this->prenume = prenume;

    if (nrComenzi < 0)
        throw ExceptionInput("Numarul comenzilor trebuie sa fie pozitiv!");
    else {
        this->nrComenziDate = nrComenzi;
    }
}

Client::Client(const Client &client) : email(client.email) {
    this->nume = client.nume;
    this->prenume = client.prenume;

    this->nrComenziDate = client.nrComenziDate;

}

void Client::set_nume(const std::string nume) {
    this->nume = nume;
}

void Client::set_prenume(const std::string prenume) {
    this->prenume = prenume;
}

void Client::set_nrComenziDate(const int nrComenzi) {
    if (nrComenzi < 0)
        throw ExceptionInput("Numarul comenzilor trebuie sa fie pozitiv!");
    else {
        this->nrComenziDate = nrComenzi;
    }
}

std::string Client::get_nume() const{
    return this->nume;
}

std::string Client::get_email() const{
    return this->email;
}

std::string Client::get_prenume() const {
    return this->prenume;
}

int Client::get_nrComenziDate() const {
    return this->nrComenziDate;
}

std::ostream&operator<<(std::ostream &out, const Client &client){
    out<<"Nume client: ";
    out<<client.nume<<"\n";
    out<<"Prenume client: ";
    out<<client.prenume<<"\n";

    out<<"Email: ";
    out<<client.email<<"\n";

    out<<"Numar de comenzi date: ";
    out<<client.nrComenziDate<<"\n";

    return out;
}
std::istream &operator>>(std::istream &in, Client client){
    std::cout<<"\nIntroduceti numele clientului: ";
    in>>client.nume;

    std::cout<<"\nIntroduceti prenumele clientului: ";
    in>>client.prenume;

    std::cout<<"\nEmail: ";
    in>>client.email;

    int nrComenzi;
    std::cout<<"\nComenzi efectuate: ";
    std::cin>>nrComenzi;

    if (nrComenzi < 0)
        throw ExceptionInput("Numarul comenzilor trebuie sa fie pozitiv!");
    else {
        client.nrComenziDate = nrComenzi;
    }

    return in;
}
Client& Client::operator=(const Client &client){
    if(this!=&client)
    {
        this->nume=client.nume;
        this->prenume=client.prenume;
        this->nrComenziDate=client.nrComenziDate;
    }
    return *this;
}

Client& Client::operator++(){
    this->nrComenziDate++;
    return *this;
}

Client::~Client(){}

