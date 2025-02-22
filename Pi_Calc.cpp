#include "LongNumber.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

#define Max_Precision 1000

// Функция для вычисления числа Пи с помощью ряда Лейбница
LongNumber computePi(unsigned int precision)
{
    LongNumber pi(0, precision);
    LongNumber n0{1, precision};
    LongNumber n(16, precision);

    LongNumber a0{4, precision};
    LongNumber b0{2, precision};
    LongNumber c0{1, precision};
    LongNumber d0{1, precision};

    LongNumber a(1, precision);
    LongNumber b(4, precision);
    LongNumber c(5, precision);
    LongNumber d(6, precision);

    LongNumber eight(8, precision);

    if (precision == 0)
    {
        pi = pi + LongNumber(3, precision);
    }

    for (auto k = 0; k < precision; ++k)
    {
        pi = pi + n0 * (a0 / a - b0 / b - c0 / c - d0 / d);
        n0 = n0 / n;
        a = a + eight;
        b = b + eight;
        c = c + eight;
        d = d + eight;
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

    unsigned int precision = std::stoi(argv[1]);

    LongNumber pi = computePi(precision * 4);

    std::cout << pi << '\n'
              << pi.getValue() << '\n';

    return 0;
}

/*
g++ -c LongNumber.cpp -o LongNumber.o
ar cr LongNumber.a LongNumber.o
g++ -c Pi_Calc.cpp -o Pi_calc.o
g++ Pi_Calc.o LongNumber.a -o Pi_Calc.exe

*/