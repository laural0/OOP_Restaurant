//
// Created by Laura on 1/5/2024.
//

#include "Meniu.h"
#include "../Preparate/Preparate.h"
#include<fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "../Helper/Helper.h"


void Meniu::afiseazaMeniu() {

    std::vector<Preparat>meniuMancare;
    std::vector<Preparat>meniuBauturi;

    meniuMancare=getListaMancare();
    meniuBauturi=getListaBauturi();


    std::cout<<"\n\n_____________________________MENIU_____________________________\n";
    std::cout<<"\n^^^MANCARE^^^\n";
    int numarMancare=meniuMancare.size();
    int numarBauturi=meniuBauturi.size();

    for(int i=0;i<numarMancare;i++)
    {
        std::cout<<i+1<<". "<<meniuMancare[i].get_denumire()<<"\n";
    }

    std::cout<<"\n^^^BAUTURI^^^\n";
    for(int i=0;i<numarBauturi;i++)
    {
        std::cout<<i+numarMancare+1<<". "<<meniuBauturi[i].get_denumire()<<"\n";
    }

    std::cout<<"\n_______________________________________________________________";
}

std::vector<Preparat> Meniu::getListaMancare() {
    std::fstream fisier;

    fisier.open("..//Preparate//Mancare.csv", std::ios::in);
    if (!fisier.is_open())
        throw ExceptionInput("Fisierul nu a putut fi deschis");

    std::string line;
    std::vector<std::string> preparatParsat;
    std::vector<std::unique_ptr<Preparat>> result;
    while (std::getline(fisier, line)) {

        auto p = std::make_unique<Preparat>();
        std::vector<Ingredient> vectorDeIngrediente;
        preparatParsat = stringParse(line, ';');

        for (int i = 0; i < preparatParsat.size(); i++) //3k+1
        {
            Ingredient ingredient;
            if (i == 0)
                p->set_denumire(preparatParsat[i]);
            else {
                std::vector<std::string> ingredientNecesar;
                bool alergen;
                ingredientNecesar = stringParse(preparatParsat[i], ',');
                ingredient.set_denumire(ingredientNecesar[0]);
                ingredient.set_stoc(stof(ingredientNecesar[1]));
                alergen = (ingredientNecesar[2] == "true");
                ingredient.set_alergen(alergen);
                if (alergen) p->set_Alergen(true);
                vectorDeIngrediente.push_back(ingredient);
            }

        }
        p->set_reteta(vectorDeIngrediente);
        result.push_back(std::move(p));

    }

    std::vector<Preparat> actualPreparate;

    for (auto &i: result) {
        actualPreparate.push_back(std::move(*i));
    }

    fisier.close();
    return actualPreparate;

}

std::vector<Preparat>Meniu::getListaBauturi() {
    std::fstream fisier;

    fisier.open("..//Preparate//Bautura.csv", std::ios::in);
    if (!fisier.is_open())
        throw ExceptionInput("Fisierul nu a putut fi deschis");

    std::string line;
    std::vector<std::string> preparatParsat;
    std::vector<std::unique_ptr<Preparat>> result;
    while (std::getline(fisier, line)) {

        auto p = std::make_unique<Preparat>();
        std::vector<Ingredient> vectorDeIngrediente;
        preparatParsat = stringParse(line, ';');

        for (int i = 0; i < preparatParsat.size(); i++) //3k+1
        {
            Ingredient ingredient;
            if (i == 0)
                p->set_denumire(preparatParsat[i]);
            else {
                std::vector<std::string> ingredientNecesar;
                bool alergen;
                ingredientNecesar = stringParse(preparatParsat[i], ',');
                ingredient.set_denumire(ingredientNecesar[0]);
                ingredient.set_stoc(stof(ingredientNecesar[1]));
                alergen = (ingredientNecesar[2] == "true");
                ingredient.set_alergen(alergen);
                if (alergen) p->set_Alergen(true);
                vectorDeIngrediente.push_back(ingredient);
            }

        }
        p->set_reteta(vectorDeIngrediente);
        result.push_back(std::move(p));

    }

    std::vector<Preparat> actualPreparate;

    for (auto &i: result) {
        actualPreparate.push_back(std::move(*i));
    }

    fisier.close();
    return actualPreparate;
}

void Meniu::genereazaRaportProfit() {
    std::fstream raportProfit;
    std::fstream raportComenzi;
    raportProfit.open("..//Rapoarte//CalculProfit.txt", std::ios::app);
    if(!raportProfit.is_open())
        throw ExceptionInput("Fisierul CalculProfit.txt nu a putut fi deschis.");

    raportComenzi.open("..//Rapoarte//ComenziInregistrate.txt", std::ios::in);
    if(!raportComenzi.is_open())
        throw ExceptionInput("Fisierul CalculProfit.txt nu a putut fi deschis.");

    int index=0;
    std::string line;
    std::vector<std::string>lines;
    while(getline(raportComenzi, line))
    {
        index++;
        if(index>2 && !line.empty())
            lines.push_back(line);
    }

    std::map<std::string, float>profitpeData; //zilele si sumele totale

    std::vector<std::string>dateInOrdine;

    for(int i=0;i<lines.size();i++)
    {
        std::vector<std::string>elementeDinRaportComenzi;
        elementeDinRaportComenzi.reserve(4);
        elementeDinRaportComenzi= stringParse(lines[i], ' ');  //idcomanda notadeplata an ora

        float notaComanda=stof(elementeDinRaportComenzi[1]);
        std::string dataComanda=elementeDinRaportComenzi[2];


        profitpeData[dataComanda]+=notaComanda;
        dateInOrdine.push_back(dataComanda);

    }

    dateInOrdine.erase(std::unique(dateInOrdine.begin(), dateInOrdine.end()), dateInOrdine.end());

    std::vector<float>rataDeCrestere;
    for(int i=0;i<dateInOrdine.size();i++)
    {
        if(i==0) rataDeCrestere.push_back(0);
        else
        {
            rataDeCrestere.push_back(((profitpeData[dateInOrdine[i]]-profitpeData[dateInOrdine[i-1]])/profitpeData[dateInOrdine[i-1]])*100);
        }
    }

    for(int i=0;i<dateInOrdine.size();i++) {
        raportProfit<<std::setw(15)<<dateInOrdine[i];
        raportProfit<<std::setw(20)<<profitpeData[dateInOrdine[i]];
        raportProfit<<std::setw(26)<<rataDeCrestere[i]<<"%\n";
    }

    raportProfit.close();
    raportComenzi.close();

}