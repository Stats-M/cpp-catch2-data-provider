#include "catch2/catch_all.hpp"         // Catch2

#include "TestDataProvider.h"

#include <vector>
#include <tuple>
#include <string>

/*******************************************************************
 * Реализация концепции DataProvider при использовании Catch2.
 * Способ 1): Функция, возвращающая тестовые данные (гибкость)
 *******************************************************************/

// Функция, возвращающая тестовые данные
std::vector<std::tuple<std::string, double, double>> get_cube_test_data()
{
    return
    {
        {"Positive input", 2.0, 8.0},
        {"Negative input", -2.0, -8.0},
        {"Zero input", 0.0, 0.0}
    };
}
