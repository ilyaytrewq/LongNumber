#include "LongNumber.hpp"
#include <iostream>
#include <string>
#include <cmath> 

int main()
{
    {
        LongNumber num1(123.456789, 60);
        LongNumber num2(987.654321, 60);
        LongNumber res = num1 + num2;
        double expected = 1111.11111;
        std::cout << "TEST 1: " << (std::abs(res.getValue() - expected) < 1e-15 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
        std::cout << res << '\n';

    }

    {
        LongNumber num1(1000.123456, 40);
        LongNumber num2(500.54321, 40);
        LongNumber res = num1 - num2;
        double expected = 499.580246;
        std::cout << "TEST 2: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        LongNumber num1(12.3456789, 40);
        LongNumber num2(9.87654321, 40);
        LongNumber res = num1 * num2;
        double expected = 121.932631; 
        std::cout << "TEST 3: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        LongNumber num1(1000.0, 40);
        LongNumber num2(3.0, 40);
        LongNumber res = num1 / num2;
        double expected = 333.333333;
        std::cout << "TEST 4: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        LongNumber num1(1982.23487297, 50); 
        LongNumber num2(87284.187391, 50); 
        LongNumber res = num1 / num2;
        double expected = 0.022725849; 
        std::cout << "TEST 5: " << (std::abs(res.getValue() - expected) < 1e-4 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        LongNumber num1(192.23487297, 40); 
        LongNumber num2(8784.187391, 40); 
        LongNumber res = num1 * num2;
        double expected = 1688627.1472535606; 
        std::cout << "TEST 6: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        LongNumber num1(87284.187391, 40); 
        LongNumber num2(0.000123456, 40);  
        LongNumber res = num1 * num2;
        double expected = 10.77575663; 
        std::cout << "TEST 7: " << (std::abs(res.getValue() - expected) < 1e-4 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        LongNumber num1(1.000123456, 40); 
        LongNumber num2(1.000987654, 40); 
        LongNumber res = num1 * num2;
        double expected = 1.001111577626; 
        std::cout << "TEST 8: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        LongNumber num1(0.0, 40);
        LongNumber num2(123.456789, 40);
        LongNumber res = num1 + num2;
        double expected = 123.456789;
        std::cout << "TEST 9: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        LongNumber num1(123.456789, 40);
        LongNumber num2(0.0, 40);
        LongNumber res = num1 * num2;
        double expected = 0.0;
        std::cout << "TEST 10: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        LongNumber num1(0.0, 40);
        LongNumber num2(123.456789, 40);
        LongNumber res = num1 / num2;
        double expected = 0.0;
        std::cout << "TEST 11: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        try
        {
            LongNumber num1(123.456789, 40);
            LongNumber num2(0.0, 40);
            LongNumber res = num1 / num2;
            std::cout << "TEST 12: FAIL (no exception thrown)\n";
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "TEST 12: OK (exception thrown)\n";
        }
    }

    {
        LongNumber num1(1e6, 40);
        LongNumber num2(1e6, 40);
        LongNumber res = num1 + num2;
        double expected = 2000000.0;
        std::cout << "TEST 13: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        LongNumber num1(1e-6, 40);
        LongNumber num2(1e-6, 40);
        LongNumber res = num1 + num2;
        double expected = 2e-6;
        std::cout << "TEST 14: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        LongNumber num1(1.000123456, 40); 
        LongNumber num2(1.000987654, 40); 
        LongNumber res = num1 / num2;
        double expected = 0.99913665468; 
        std::cout << "TEST 15: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        LongNumber num1(355.0, 40);
        LongNumber num2(113.0, 40);
        LongNumber res = num1 / num2;
        double expected = 3.1415929203539825;
        std::cout << "TEST 16: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    {
        LongNumber num1(22.0, 40);
        LongNumber num2(7.0, 40);
        LongNumber res = num1 / num2;
        double expected = 3.142857142857143;
        std::cout << "TEST 17: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

}


/*
g++ -c LongNumber.cpp -o LongNumber.o
ar cr LongNumber.a LongNumber.o
g++ -c Tests.cpp -o Tests.o
g++ Tests.o LongNumber.a -o Tests.exe

*/
