#include "LongNumber.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

#define Max_Precision 1000

// Функция для вычисления числа Пи с помощью ряда Лейбница
LongNumber computePi(unsigned int precision)
{
    LongNumber pi(0, precision);
    LongNumber term(4, precision);        // Каждый член ряда умножается на 4
    LongNumber denominator(1, precision); // Знаменатель ряда (1, 3, 5, 7, ...)
    LongNumber two(2, precision);

    for (unsigned int i = 0; i < precision; ++i)
    { // Умножаем на 10 для увеличения точности
        // Вычисление следующего члена ряда
        LongNumber fraction = term / denominator;

        // Суммирование с учетом знака
        if (i % 2 == 0)
        {
            pi = pi + fraction; // Добавляем для четных индексов
        }
        else
        {
            pi = pi - fraction; // Вычитаем для нечетных индексов
        }

        // Увеличиваем знаменатель на 2 (3, 5, 7, 9,...)
        denominator = denominator + two;
    }

    return pi;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <precision>" << std::endl;
        return 1;
    }

    // Чтение количества десятичных разрядов из аргумента командной строки
    unsigned int precision = std::stoi(argv[1]);

    // Вычисление числа Пи с заданной точностью
    LongNumber pi = computePi(precision * 4);

    // Вывод числа Пи с заданной точностью
    std::cout << "Pi with " << precision << " decimal places: ";
    std::cout << pi << std::endl;

    return 0;
}

/*
g++ -c LongNumber.cpp -o LongNumber.o
ar cr LongNumber.a LongNumber.o
g++ -c Pi_Calc.cpp -o Pi_calc.o
g++ Pi_Calc.o LongNumber.a -o Pi_Calc.exe

*/