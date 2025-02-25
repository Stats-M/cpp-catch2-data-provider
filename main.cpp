/**
 * Здесь можно разместить основную логику приложения, она не будет
 * конфликтовать с содержимым tests/main.cpp
 */

#include "src/cube.h"       // Для примера использования функции из cube.h

#include <iostream>

int main() {
    std::cout << "Main application entry point." << std::endl;
    std::cout << "Cube of 5 is: " << get_cube(5.0) << std::endl;
    return 0;
}
