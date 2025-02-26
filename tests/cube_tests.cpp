#include "catch2/catch_all.hpp"        // Подключаем библиотеку Catch2 v3
#include "../src/cube.h"               // Включаем заголовочный файл с тестируемыми функциями
#include "TestDataProvider.h"          // Заголовочный файл вариантов реализации DataProvider

#include <vector>

using namespace Catch;              // Для Catch::Approx() и т.п.

// Определяет тестовый случай. Второй аргумент ("[get_sum]") – тег для фильтрации тестов
TEST_CASE("get_sum function tests", "[get_sum]")
{
    // Секция разбивает тестовый случай на НЕЗАВИСИМЫЕ логические участки
    SECTION("Integer vector")
    {
        std::vector<int> data = {1, 2, 3, 4, 5};
        // Проверка условия
        REQUIRE(get_sum(data) == 15);
    }

    SECTION("Double vector")
    {
        std::vector<double> data = {1.5, 2.5, 3.5};
        REQUIRE(get_sum(data) == Approx(7.5));      // Approx для сравнения double
        //REQUIRE(get_sum(data) == 7.5);                      // Это эквивалент для Approx
    }

    SECTION("Empty vector")
    {
        std::vector<int> data = {};
        REQUIRE(get_sum(data) == 0);
    }
}

TEST_CASE("get_cube function tests", "[get_cube]")
{
    SECTION("Positive input")
    {
        REQUIRE(get_cube(2.0) == Approx(8.0));
    }

    SECTION("Negative input")
    {
        REQUIRE(get_cube(-2.0) == Approx(-8.0));
    }

    SECTION("Zero input")
    {
        REQUIRE(get_cube(0.0) == Approx(0.0));
    }

    SECTION("Default argument")
    {
        REQUIRE(get_cube() == Approx(0.0));
    }
}

TEST_CASE("get_pow_2 function tests", "[get_pow_2]")
{
    SECTION("Positive input")
    {
        REQUIRE(get_pow_2(2.0) == Approx(4.0));
    }

    SECTION("Negative input")
    {
        REQUIRE(get_pow_2(-2.0) == Approx(4.0));
    }

    SECTION("Zero input")
    {
        REQUIRE(get_pow_2(0.0) == Approx(0.0));
    }

    SECTION("Default argument")
    {
        REQUIRE(get_pow_2() == Approx(0.0));
    }
}

TEST_CASE("multiply_by_two function tests", "[multiply_by_two]")
{
    SECTION("Integer vector")
    {
        std::vector<int> input = {1, 2, 3};
        std::vector<int> expected = {2, 4, 6};
        REQUIRE(multiply_by_two(input) == expected);
    }

    SECTION("Double vector")
    {
        std::vector<double> input = {1.5, 2.5, 3.5};
        std::vector<double> expected = {3.0, 5.0, 7.0};
        std::vector<double> result = multiply_by_two(input);
        REQUIRE(result[0] == Approx(3.0));
        REQUIRE(result[1] == Approx(5.0));
        REQUIRE(result[2] == Approx(7.0));
    }

    SECTION("Empty vector")
    {
        std::vector<int> input = {};
        std::vector<int> expected = {};
        REQUIRE(multiply_by_two(input) == expected);
    }
}

TEST_CASE("multiply_by_two_void function tests", "[multiply_by_two_void]")
{
    SECTION("Integer vector")
    {
        std::vector<int> input = {1, 2, 3};
        std::vector<int> expected = {2, 4, 6};
        multiply_by_two_void(input);
        REQUIRE(input == expected);                 // Сравнение вектора целиком
    }

    SECTION("Double vector")
    {
        std::vector<double> input = {1.5, 2.5, 3.5};
        std::vector<double> expected = {3.0, 5.0, 7.0};
        multiply_by_two_void(input);
        REQUIRE(input[0] == Approx(3.0));           // Поэлементное сравнение
        REQUIRE(input[1] == Approx(5.0));
        REQUIRE(input[2] == Approx(7.0));
    }

    SECTION("Empty vector")
    {
        std::vector<int> input = {};
        std::vector<int> expected = {};
        multiply_by_two_void(input);
        REQUIRE(input == expected);
    }
}


/**
 * Тестовый случай с использованием DataProvider, реализованного в виде функции,
 * возвращающей тестовые данные (Способ №1)
 */
TEST_CASE("get_cube function tests with DP via function", "[get_cube]")
{
    // Получаем тестовые данные
    auto test_data = get_cube_test_data();

    // Итерируемся по тестовым данным
    for (const auto& data : test_data)
    {
        std::string test_name = std::get<0>(data);
        double input = std::get<1>(data);
        double expected = std::get<2>(data);

        SECTION(test_name)
        {
            REQUIRE(get_cube(input) == Approx(expected));
        }
    }
}
