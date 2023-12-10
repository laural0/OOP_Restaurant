//
// Created by Laura on 12/5/2023.
//

#include "Preparate.h"
#include "../Helper/Helper.h"

float Preparat::adaosComercial = 400;

Preparat::Preparat() {}

Preparat::Preparat(char *numePreparat) {
    if (numePreparat != nullptr) {
        this->denumire = new char[strlen(numePreparat) + 1];
        strcpy(this->denumire, numePreparat);

        convertLowercase(this->denumire);
    } else {
        throw ExceptionInput("Numele preparatului nu poate fi null.");
    }
}

Preparat::Preparat(char *numePreparat, std::map<Ingredient, float> &reteta, bool dePost) {
    if (numePreparat != nullptr) {
        this->denumire = new char[strlen(numePreparat) + 1];
        strcpy(this->denumire, numePreparat);

        convertLowercase(this->denumire);
    } else {
        throw ExceptionInput("Numele preparatului nu poate fi null.");
    }

    this->reteta = reteta;

    this->dePost = dePost;
}

Preparat::Preparat(Preparat &preparat) {
    this->denumire = preparat.denumire;
    this->reteta = preparat.reteta;
    this->dePost = preparat.dePost;

}

Preparat::~Preparat() {
    delete[]this->denumire;
    this->denumire = nullptr;
}

void Preparat::set_denumire(const char *denumire) {
    if (denumire != nullptr) {
        this->denumire = new char[strlen(denumire) + 1];
        strcpy(this->denumire, denumire);

        convertLowercase(this->denumire);
    } else {
        throw ExceptionInput("Numele preparatului nu poate fi null.");
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


std::map<Ingredient, float> Preparat::get_reteta() const {
    return this->reteta;
}

float Preparat::get_adaosComercial() {
    return Preparat::adaosComercial;
}

bool Preparat::get_dePost() const {
    return this->dePost;
}

std::ostream &operator<<(std::ostream &out, const Preparat &preparat) {
    out << "\nNume preparat: ";
    if (preparat.denumire != nullptr) {
        out << preparat.denumire;
    } else {
        throw ExceptionInput("Numele preparatului nu poate fi null");
    }

    out << "\nReteta: ";
    for (auto it = preparat.reteta.begin(); it != preparat.reteta.end(); it++) {
        out << "\n      " << it->first << "  " << it->second;
    }
    out << "\nDe post: ";
    if (preparat.dePost) { out << "Da"; }
    else { out << "Nu"; }

    return out;
}

std::istream &operator>>(std::istream &in, Preparat &preparat) {
    if (preparat.denumire != nullptr) {
        delete[] preparat.denumire;
        preparat.denumire = nullptr;
    }

    std::cout << "\nIntroduceti denumirea preparatului: ";
    std::string buffer;
    in >> buffer;

    preparat.denumire = new char[buffer.size() + 1];
    strcpy(preparat.denumire, buffer.data());

    convertLowercase(preparat.denumire);

    std::cout << "\nSi acum ingredientele......";
    std::vector<Ingredient> lista = Ingredient::getListaIngrediente();
    for (int i = 0; i < lista.size(); i++)
        std::cout << i + 1 << ". " << lista[i] << "\n";

    std::cout << "Doriti sa adaugati un ingredient? Y/N\n";
    char response;
    std::cin >> response;
    response == 'Y' || response=='y' ? response=true : response=false;
    if(response) {
        while (response) {


            Ingredient ingredientNou;
            std::cin >> ingredientNou;

            ingredientNou.adaugaIngredient();

            std::cout << "Doriti sa mai adaugati?\n";
            std::cin >> response;

        }
        std::cout << "Aceasta este lista actualizata: \n";
        lista = Ingredient::getListaIngrediente();
        for (int i = 0; i < lista.size(); i++)
            std::cout << "      " << i + 1 << ". " << lista[i] << "\n";
    }


    std::cout << "Ce ingrediente doriti sa includeti in noul preparat? Scrieti "
                 "numerele ingredientelor urmate de o virgula.\n";
    std::vector<int>answer;
    int index;
    while(std::cin>>index)
        answer.push_back(index);

    float cant;
    std::cout << "Introduceti cantitatile pentru fiecare ingredient! \n";
    for (int i = 0; i < answer.size(); i++) {
        std::cout << "  Pentru " << lista[answer[i]-1].get_numeIngredient() << ": \n";
        in >> cant;
        preparat.reteta.insert(std::make_pair(lista[answer[i-1]], cant));

    }

    std::cout << "Este de post?  Y/N";
    char reponse;
    std::cin >> response;
    reponse == 'Y' || response == 'y' ? preparat.dePost = true : preparat.dePost = false;

    return in;
}

void Preparat::getListaPreparate(){

}

void Preparat::adaugaPreparat() {

}


