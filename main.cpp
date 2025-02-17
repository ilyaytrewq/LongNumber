#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include "LongNumber.hpp"

#define Max_Precision 1000

/*
Tests

First test
12.9253 65.893873534

+) 1001110.1101000110
-) -110100.1111011111
*) 1101010011.1011001010
/) 0.0011001000

*/

int main() {
    int n;
    std::cin >> n;
    for(int i = 0; i < n; ++i){
        long double a, b;
        std::cin >> a >> b;
        LongNumber A(a, 10), B(b, 10);
        std::cout << "Numbers A and B\n";
        std::cout << A << '\n' << B << '\n';
        std::cout << "A + B\n" << A + B << '\n';
        std::cout << "A - B\n" << A - B << "\n";
        std::cout << "A * B\n" << A * B << "\n";
        std::cout << "A / B\n" << A / B << '\n';
    }

    return 0;
}



/*
g++ -c LongNumber.cpp -o LongNumber.o
ar cr LongNumber.a LongNumber.o
g++ -c main.cpp -o main.o
g++ main.o LongNumber.a -o main.exe

*/


