#include <iostream>
#include <sstream>
#include "Ingredient/Ingrediente.h"
#include "Preparate/Preparate.h"
#include "Helper/Helper.h"
#include <fstream>

//            listaIngrediente.emplace_back(lista[0].c_str(), stof(lista[1]), stof(lista[2]), stof(lista[3]), esteAlergen); //se blocheaza aici

int main() {


    Preparat a("bors");



    std::vector<Preparat> lista;
    lista = Preparat::getListaPreparate();

    for(int i=0;i<lista.size();i++)
        std::cout<<lista[i]<<"\n";

    return 0;
}

