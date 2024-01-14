//
// Created by Laura on 12/10/2023.
//

#ifndef PROIECT_OOP_HELPER_H
#define PROIECT_OOP_HELPER_H

#include<iostream>
#include <vector>
#include <chrono>
#include <ctime>

std::string dataCurenta();

void convertLowercase(std::string sir);

std::vector<std::string> stringParse(const std::string &s, char delimiter);

bool sortMapByVal(const std::pair<std::string, int>&a, const std::pair<std::string, int>&b);

#endif //PROIECT_OOP_HELPER_H
