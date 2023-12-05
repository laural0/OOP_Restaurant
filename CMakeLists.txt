cmake_minimum_required(VERSION 3.26)
project(Proiect_OOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(Proiect_OOP main.cpp
        Comanda/Comanda.cpp
        Comanda/Comanda.h
        ExceptionInput/ExceptionInput.cpp
        ExceptionInput/ExceptionInput.h
        Preparate/Preparate.cpp
        Preparate/Preparate.h
        Ingredient/Ingrediente.cpp
        Ingredient/Ingrediente.h)
