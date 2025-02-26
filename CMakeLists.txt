cmake_minimum_required(VERSION 3.28)
project(cpp_catch2_data_provider VERSION 0.0.1)

# Вычисляем разные полезные переменные
set(USER_HOME_DIRECTORY $ENV{USERPROFILE})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-12")
#set(CMAKE_CXX_FLAGS "-mavx")   Включение SIMD (SSE) команд при использовании библиотеки xsimd

# ВНИМАНИЕ!!! Если не было сделано ранее, нужно предварительно дать команду
#             git submodule add https:\//github.com/catchorg/Catch2.git cmake/Catch2
#             для добавления Catch2 в виде подмодуля
# Добавляем Catch2 как подмодуль
add_subdirectory(cmake/Catch2)

# Ищем Catch2
#find_package(Catch2 REQUIRED)

# Связываем файлы проекта (основной код) в исполняемый файл с именем "cpp_catch2_exec"
add_executable(cpp_catch2_exec
        main.cpp
        src/cube.h
        src/cube.cpp
)

# Создаем отдельную тестовую цель, чтобы тесты не включались в основной исполняемый файл.
# При сборке этой цели будет создан исполняемый файл с именем "catch2_test_exec"
add_executable(catch2_test_exec
        tests/main.cpp          # Основной файл для тестов (с CATCH_CONFIG_MAIN)
        tests/cube_tests.cpp    # Файл с тестами для cube.h
        #src/cube.h              # !!! Заголовочные файлы доступны из тестов через #include, можно не подключать повторно здесь
        src/cube.cpp            # !!! Файл с определениями тестируемых функций, иначе линкер не увидит нешаблонные функции
)

# Связываем Catch2 ТОЛЬКО с тестовой целью (link against Catch2WithMain target if you use Catch2's default main)
target_link_libraries(catch2_test_exec Catch2::Catch2WithMain)

# Добавляем каталог src в include path для тестовой цели, чтобы тесты могли найти src/*.h файлы Catch2
# ${CMAKE_SOURCE_DIR} в данном случае ссылается на корневую папку проекта
target_include_directories(catch2_test_exec PRIVATE ${CMAKE_SOURCE_DIR}/cmake/Catch2/src)

# Опционально: Добавляем CTest интеграцию (для автоматического запуска тестов CMake)
include(CTest)
# Создает цель "CubeTests", которую можно запустить из IDE или с помощью командной строки
add_test(NAME CubeTests COMMAND catch2_test_exec)

#               !!!!!!!!!!!!!!!!ВОЗМОЖНЫЕ ПРОБЛЕМЫ С ЗАПУСКОМ ТЕСТОВ!!!!!!!!!!!!!!!!
# ОШИБКА: Test framework quit unexpectedly
# ========================================
#
# РЕШЕНИЕ #1:
# -----------
# Вероятно, линкер выполняет оптимизацию Dead Code Elimination и удаляет неиспользуемый код Catch2,
# т.к. библиотека состоит из заголовков с макросами (НЕ функциями!) и, по мнению компилятора, не используется.
# Как проверить в IDE:
# В tests/main.cpp строка      #include "catch2/catch_all.hpp"      отображается серой (неактивной).
# Необходимо явно вызвать какой-либо код из библиотеки.
# Вариант 1) Просто и эффективно: добавим в tests/main.cpp в main() строчку
#     int main(int argc, char* argv[])
#     {
#         int result = Catch::Session().run(argc, argv);
#         return result;
#     }
# Вариант 2) Попробовать флаг set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-as-needed")
#     Флаг "-Wl,--no-as-needed" говорит линкеру не удалять неиспользуемые библиотеки (может увеличить размер файла).
#
# РЕШЕНИЕ #2 (не работает):
# -------------------------
# По умолчанию тесты запускаются через IDE (Run test) командой "<path>/catch2_test_exec -r xml -d yes --order lex"
# В CLion есть проблема с отображением XML из-за неверной схемы. Нужно убрать опцию показа XML, либо запускать
# тесты из командной строки
#   Run -> Edit Configurations, указать только нужные аргументы "-d yes --order lex"
#
# ЗАПУСК ТЕСТОВ ИЗ КОМАНДНОЙ СТРОКИ:
# ==================================
# Запуск тестов из командной строки:
#   Перейти в терминале в папку с исполняемым файлом (имя как у тестовой цели: catch2_test_exec) и запустить его:
#       cd cpp-catch2-data-provider/cmake-build-debug
#       ./catch2_test_exec                              <- Запуск всех тестов
#       ./catch2_test_exec -d yes --order lex           <- Запуск тестов с отсчетом времени каждого теста
#       ./catch2_test_exec -r xml -d yes --order lex    <- Вывод в терминал XML документа с результатами теста
#       ./catch2_test_exec [get_cube]                   <- Запуск тестов только с указанным тегом
#   Вывод результатов будет произведен в терминал
