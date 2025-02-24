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

/*
3,14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651 3282306647 0938446095 5058223172 5359408128 4811174502 8410270193 8521105559 64
3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798212942433927391720921467351410919755706319241522390790866788557093228984398881279661794504411652995879644050496276312097267816222312604450098499964995464604664127052931721121726068245790527026097133448173854587681663730336367734707891941070556
*/

/*
g++ -c LongNumber.cpp -o LongNumber.o
ar cr LongNumber.a LongNumber.o
g++ -c Pi_Calc.cpp -o Pi_calc.o
g++ Pi_Calc.o LongNumber.a -o Pi_Calc.exe

*/