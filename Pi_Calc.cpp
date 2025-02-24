#include "LongNumber.hpp"
#include "TimeGuard.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

#define Max_Precision 1000

// Функция для вычисления числа Пи с помощью ряда Лейбница
LongNumber computePi(unsigned int precision)
{
    if(precision == 0)
        return LongNumber(3, precision);

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

    for (auto k = 0; k < precision; ++k)
    {
        pi = pi + n0 * (a0 / a - b0 / b - c0 / c - d0 / d);
        n0 = n0 / n;
        a = a + eight;
        b = b + eight;
        c = c + eight;
        d = d + eight;
        // std::cout << a0 << '\n' << a << '\n';
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

    const std::string PI = "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095";

    std::string message = "Pi calculation end";
    TimerGuard start(message, std::cout);

    unsigned int precision = std::stoi(argv[1]);

    LongNumber pi = computePi(precision * 3.5);

    std::cout << pi.getValue().substr(0, precision + 2) << '\n';
    std::cout << (pi.getValue().substr(0, precision + 2) == PI.substr(0, precision + 2) ? "OK\n" : "FAIL\n");

    return 0;
}