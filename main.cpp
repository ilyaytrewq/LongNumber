#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include "LongNumber.hpp"

#define Max_Precision 1000

int main() {
    int n;
    std::cin >> n;
    for(int i = 0; i < n; ++i){
        long double a, b;
        std::cin >> a >> b;
        LongNumber A(a, 100), B(b, 100);
        std::cout << "Numbers A and B\n";
        std::cout << A << '\n' << B << '\n';
        std::cout << "A + B\n" << A + B << '\n';
        std::cout << "A - B\n" << A - B << "\n";
        std::cout << "A * B\n" << A * B << "\n";
        std::cout << "A / B\n" << A / B << '\n';
    }

    return 0;
}
