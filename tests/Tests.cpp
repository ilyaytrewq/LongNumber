#include "LongNumber.hpp"
#include <iostream>
#include <string>
#include <cmath>

bool compareStrings(const std::string& result, const std::string& expected) {
    size_t dotPosResult = result.find('.');
    size_t dotPosExpected = expected.find('.');

    if (dotPosResult == std::string::npos || dotPosExpected == std::string::npos) {
        return result == expected;
    }

    std::string resultSubstr = result.substr(0, dotPosResult + 13);
    std::string expectedSubstr = expected.substr(0, dotPosExpected + 13);

    return resultSubstr == expectedSubstr;
}

int main()
{
    {
        LongNumber num1(123.843759, 100);
        LongNumber num2(987.36535645, 100);
        LongNumber res = num1 + num2;
        std::string expected = "1111.209115450000";
        std::cout << "TEST 1: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        LongNumber num1(1000.123456, 100);
        LongNumber num2(500.54321, 100);
        LongNumber res = num1 - num2;
        std::string expected = "499.580246000000";
        std::cout << "TEST 2: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        LongNumber num1(12.3456789, 100);
        LongNumber num2(9.87654321, 100);
        LongNumber res = num1 * num2;
        std::string expected = "121.932631112635";
        std::cout << "TEST 3: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        LongNumber num1(1000.0, 100);
        LongNumber num2(3.0, 100);
        LongNumber res = num1 / num2;
        std::string expected = "333.333333333333";
        std::cout << "TEST 4: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        LongNumber num1(1982.23487297, 100);
        LongNumber num2(87284.187391, 100);
        LongNumber res = num1 / num2;
        std::string expected = "0.022710125765289432";
        std::cout << "TEST 5: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        LongNumber num1(192.23487297, 100);
        LongNumber num2(8784.187391, 100);
        LongNumber res = num1 * num2;
        std::string expected = "1688627.14725356060229";
        std::cout << "TEST 6: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        LongNumber num1(87284.187391, 100);
        LongNumber num2(0.000123456, 100);
        LongNumber res = num1 * num2;
        std::string expected = "10.775756638543296";
        std::cout << "TEST 7: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        LongNumber num1(1.000123456, 100);
        LongNumber num2(1.000987654, 100);
        LongNumber res = num1 * num2;
        std::string expected = "1.0011112319318123";
        std::cout << "TEST 8: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        LongNumber num1(0.0, 100);
        LongNumber num2(123.456789, 100);
        LongNumber res = num1 + num2;
        std::string expected = "123.456789000000";
        std::cout << "TEST 9: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        LongNumber num1(123.456789, 100);
        LongNumber num2(0.0, 100);
        LongNumber res = num1 * num2;
        std::string expected = "0.0";
        std::cout << "TEST 10: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        LongNumber num1(0.0, 100);
        LongNumber num2(123.456789, 100);
        LongNumber res = num1 / num2;
        std::string expected = "0.0";
        std::cout << "TEST 11: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        try
        {
            LongNumber num1(123.456789, 100);
            LongNumber num2(0.0, 100);
            LongNumber res = num1 / num2;
            std::cout << "TEST 12: FAIL (no exception thrown)\n";
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "TEST 12: OK (exception thrown)\n";
        }
    }

    {
        LongNumber num1(1e6, 100);
        LongNumber num2(1e6, 100);
        LongNumber res = num1 + num2;
        std::string expected = "2000000.0";
        std::cout << "TEST 13: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        LongNumber num1(1.000123456, 100);
        LongNumber num2(1.000987654, 100);
        LongNumber res = num1 / num2;
        std::string expected = "0.9991366546864524";
        std::cout << "TEST 14: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        LongNumber num1(355.0, 100);
        LongNumber num2(113.0, 100);
        LongNumber res = num1 / num2;
        std::string expected = "3.1415929203539825";
        std::cout << "TEST 15: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }

    {
        LongNumber num1(22.0, 100);
        LongNumber num2(7.0, 100);
        LongNumber res = num1 / num2;
        std::string expected = "3.142857142857";
        std::cout << "TEST 16: " << (compareStrings(res.getValue(), expected) ? "OK" : "FAIL") << "\n";
    }
}