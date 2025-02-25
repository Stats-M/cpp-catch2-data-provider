/**
 * Этот файл используется ТОЛЬКО для подключения тестов Catch2.
 * НИЧЕГО БОЛЬШЕ СЮДА ДОБАВЛЯТЬ НЕ НУЖНО!!!
 */

// Определяем точку входа для тестов Catch2
// НЕ НУЖНО в каждый файл это вставлять, ДОСТАТОЧНО 1 РАЗА ЗДЕСЬ

#define CATCH_CONFIG_MAIN

//#include "../cmake/Catch2/src/catch2/catch_all.hpp"     // Заголовочный файл тестов
// Мы используем предопределенный префикс пути для подключаемых файлов из CmakeLists.txt
// см.  target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/cmake/Catch2/src)
// Поэтому можно сделать #include независимым от локальных путей:

#include "catch2/catch_all.hpp"                           // Заголовочный файл тестов

#include <iostream>

int main( int argc, char* argv[] )
{
    std::cout << "Tests are starting..." << std::endl;
    int result = Catch::Session().run( argc, argv );
    std::cout << "Tests are finished." << std::endl;
    return result;
}