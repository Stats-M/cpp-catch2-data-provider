#pragma once

#include <vector>
#include <type_traits>

/**
 * Пример шаблонной функции, которую требуется протестировать
 * @tparam T Тип параметра функции
 * @param args Вектор значений типа T
 * @return Сумма значений вектора
 */
template <typename T>
T get_sum(std::vector<T> args)
{
    T sum = static_cast<T>(0);
    for (T el : args)
    {
        sum += el;
    }
    return sum;
}

/**
 * Пример обычной нешаблонной функции, которую требуется протестировать
 * @param arg
 * @return Кубическая степень параметра arg
 */
double get_cube(double arg = 0.0);

/**
 * Пример обычной нешаблонной функции, которую требуется протестировать
 * @param arg
 * @return Квадрат параметра arg
 */
double get_pow_2(double arg = 0.0);

/**
* Пример шаблонной функции для умножения каждого элемента вектора на 2
* @tparam T Тип параметра и результата функции (std::is_arithmetic_v<T>)
* @param v Входящий вектор (const)
* @return Результирующий вектор (копия)
*/
template <typename T> requires (std::is_arithmetic_v<T>)
std::vector<T>  multiply_by_two(const std::vector<T>& v)
{
    std::vector<T> result;

    T multiplier = static_cast<T>(2);

    for (const T& element : v)
    {
        result.push_back(element * multiplier);
    }

    return result;
}

/**
* Пример шаблонной функции для умножения каждого элемента вектора на 2.
* Операции производятся непосредственно над вектором, переданным в качестве аргумента
* @tparam T Тип параметра функции (std::is_arithmetic_v<T>)
* @param v Входящий вектор
*/
template <typename T> requires (std::is_arithmetic_v<T>)
void multiply_by_two_void(std::vector<T>& v)
{
    T multiplier = static_cast<T>(2);

    for (T& element : v)
    {
        element *= multiplier;
    }
}