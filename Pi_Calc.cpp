#include "LongNumber.hpp"
#include "TimeGuard.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

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

    const std::string PI = "3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609433057270365759591953092186117381932611793105118548074462379962749567351885752724891227938183011949129833673362440656643086021394946395224737190702179860943702770539217176293176752384674818467669405132000";
    
    std::string message = "Pi calculation end";
    TimerGuard start(message, std::cout);

    unsigned int precision = std::stoi(argv[1]);

    LongNumber pi = computePi(precision * 4);

    std::cout << pi.getValue().substr(0, precision + 2) << '\n';
    std::cout << (pi.getValue().substr(0, precision + 2) == PI.substr(0, precision + 2) ? "OK\n" : "FAIL\n");

    return 0;
}