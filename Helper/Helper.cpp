//
// Created by Laura on 12/10/2023.
//


#include "Helper.h"
#include <sstream>


bool sortMapByVal(const std::pair<std::string, int>&a, const std::pair<std::string, int>&b){
    return a.second>b.second;
}

std::string dataCurenta() {
    auto end = std::chrono::system_clock::now();

    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    struct tm const *dataLocala = std::localtime(&end_time);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", dataLocala);

    return std::string(buffer);

}


std::string convertLowercase(std::string &sir) {
    for (int i = 0; i < sir.size(); i++)
        tolower(sir[i]);
    return sir;
}

std::vector<std::string> stringParse(const std::string &s, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string token="";

    std::string delimiterToString="";
    delimiterToString+=delimiter;

    while (getline(ss, token, delimiter)) {
        if (!token.empty())
            result.push_back(token);
    }


    return result;
}