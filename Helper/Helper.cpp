//
// Created by Laura on 12/10/2023.
//


#include "Helper.h"
#include <sstream>

void convertLowercase(char *sir) {

    char *p = sir;
    for (; *p; ++p) *p = tolower(*p);

}

std::vector<std::string> stringParse(const std::string &s, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string token;

    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }


    return result;
}