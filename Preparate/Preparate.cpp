//
// Created by Laura on 12/5/2023.
//

#include "Preparate.h"

float Preparat::adaosComercial=400;

Preparat::Preparat(char *numePreparat) {
    if (numePreparat != nullptr) {
        this->denumire = new char[strlen(numePreparat) + 1];
        strcpy(this->denumire, numePreparat);
    } else {
        throw ExceptionInput("Numele preparatului nu poate fi null.");
    }
}

Preparat::Preparat(char *numePreparat, float numarIngrediente, std::map<Ingredient, float> &reteta, bool dePost) {
    if (numePreparat != nullptr) {
        this->denumire = new char[strlen(numePreparat) + 1];
        strcpy(this->denumire, numePreparat);
    } else {
        throw ExceptionInput("Numele preparatului nu poate fi null.");
    }
    if (numarIngrediente > 0) {
        this->numarIngrediente = numarIngrediente;
    } else {
        throw ExceptionInput("Cantitatea necesara trebuie sa fie mai mare decat 0.");
    }

    this->reteta = reteta;

    this->dePost = dePost;
}

Preparat::Preparat(Preparat &a) {
    this->denumire = a.denumire;
    this->reteta = a.reteta;
    this->numarIngrediente = a.numarIngrediente;
    this->dePost = a.dePost;

}

Preparat::~Preparat() {
    delete[]this->denumire;
    this->denumire = nullptr;
}

void Preparat::set_denumire(const char *denumire) {
    if (denumire != nullptr) {
        this->denumire = new char[strlen(denumire) + 1];
        strcpy(this->denumire, denumire);
    } else {
        throw ExceptionInput("Numele preparatului nu poate fi null.");
    }
}

void Preparat::set_numarIngrediente(const float numarIngrediente) {
    if (numarIngrediente > 0) {
        this->numarIngrediente = numarIngrediente;
    } else {
        throw ExceptionInput("Cantitatea necesara trebuie sa fie mai mare decat 0.");
    }
}

void Preparat::set_reteta(const std::map<Ingredient, float> &reteta) {
    this->reteta = reteta;
}

void Preparat::set_adaosComercial(const float adaosComercial) {
    Preparat::adaosComercial = adaosComercial;
}

void Preparat::set_dePost(const bool dePost) {
    this->dePost = dePost;
}

char *Preparat::get_denumire() const {
    return this->denumire;
}

float Preparat::get_numarIngrediente() const {
    return this->numarIngrediente;
}

std::map<Ingredient, float> Preparat::get_reteta() const {
    return this->reteta;
}

float Preparat::get_adaosComercial() {
    return Preparat::adaosComercial;
}

bool Preparat::get_dePost() const {
    return this->dePost;
}

std::ostream &operator<<(std::ostream &out, const Preparat &a) {
    out << "\nNume preparat: ";
    if (a.denumire != nullptr) {
        out << a.denumire;
    } else {
        throw ExceptionInput("Numele preparatului nu poate fi null");
    }
    out << "\nNumar ingrediente: ";
    if (a.numarIngrediente > 0) {
        out << a.numarIngrediente;
    } else {
        throw ExceptionInput("Cantitatea trebuie sa fie pozitiva.");
    }
    out << "\nReteta: ";
    for (auto it = a.reteta.begin(); it != a.reteta.end(); it++) {
        out << "\n      " << it->first << "  " << it->second;
    }
    out << "\nDe post: ";
    if (a.dePost) { out << "Da"; }
    else { out << "Nu"; }

    return out;
}

std::istream &operator>>(std::istream &in, Preparat &a) {
    delete[] a.denumire;
    a.denumire = nullptr;

    std::cout<<"\nIntroduceti denumirea preparatului: ";
    std::string buffer;
    in >> buffer;

    a.denumire = new char[buffer.size() + 1];
    strcpy(a.denumire, buffer.data());

    std::cout<<"\nReteta: ";
    for(int i=0;i<a.numarIngrediente;i++){



        //todo:  preia din lista de ingrediente numele dupa ce i se arata o lista cu coduri si alege codul
        //alege 23.zahar, preia denumirea si o baga in map

        //todo: numarIngrediente este int nu float
    }
}

