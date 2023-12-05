//
// Created by Laura on 12/5/2023.
//

#ifndef PROIECT_OOP_EXCEPTIONINPUT_H
#define PROIECT_OOP_EXCEPTIONINPUT_H

#include<exception>
#include<string>

class ExceptionInput : public std::exception {
    std::string message;

public:
    ExceptionInput(char const *what_arg) : message(what_arg) {}

    ExceptionInput(std::string const &what_arg) : message(what_arg) {}

    const char *what() const noexcept override {
        return message.c_str();
    }

};


#endif //PROIECT_OOP_EXCEPTIONINPUT_H
