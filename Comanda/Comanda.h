////
//// Created by Laura on 12/4/2023.
////
//
//#ifndef PROIECT_OOP_COMANDA_H
//#define PROIECT_OOP_COMANDA_H
//
//#include<string>
//#include<vector>
//#include <cstring>
//#include "../ExceptionInput/ExceptionInput.h"
//
//class Comanda {
//    const int id;
//
//    //std::string mentiuni;
//    float sumaDePlata = 0.0;
//    enum metodaPlata {
//        byCash, byCard
//    };
//    metodaPlata plata;
//
//public:
//    Comanda(const int id) : id(id) {}
//
//    Comanda(const int id, std::vector<std::string> &listaPreparate, std::string mentiuni,
//            float sumaDePlata, metodaPlata plata) : id(id) {
//        this->listaPreparate = listaPreparate;
//
//        this->mentiuni = mentiuni;
//
//        if (sumaDePlata < 0)
//            throw ExceptionInput("Nota trebuie sa fie pozitiva!");
//        else
//            this->sumaDePlata = sumaDePlata;
//
//        if (plata == byCash || plata == byCard)
//            this->plata=plata;
//        else
//            throw ExceptionInput("Metoda de plata nu exista.");
//    }
//    void set_listaPreparate (std::vector<std::string> listapreparate)
//    {
//        this->listaPreparate=listapreparate;
//    }
//    void set_mentiuni(std::string mentiuni)
//    {
//        this->mentiuni=mentiuni;
//    }
//    void set_sumaDePlata(float sumadeplata){
//        if(sumadeplata>0)
//            this->sumaDePlata=sumadeplata;
//        else
//            throw ExceptionInput("Nota trebuie sa fie pozitiva!");
//    }
//    void set_plata(metodaPlata plata){
//        this->plata=plata;
//    }
//
//    std::vector<std::string> get_listaPreparate() const{
//        return this->listaPreparate;
//    }
//    std::string get_mentiuni() const {
//        return this->mentiuni;
//    }
//    float get_sumaDePlata() const {
//        return this->sumaDePlata;
//    }
//    metodaPlata get_plata() const {
//        return this->plata;
//    }
//
//    void adaugaLaComanda(std::string preparat){
//        this->listaPreparate.push_back(preparat);
//    }
//    void stergeDinComanda(std::string preparat){
//        for()
//    }
//
//
//    ~Comanda() {}
//
//};
//
//
//#endif //PROIECT_OOP_COMANDA_H
