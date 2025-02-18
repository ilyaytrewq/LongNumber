#include "LongNumber.hpp"
#include <iostream>
#include <string>
#include <cmath>  // Для std::abs

int main() {
    // Тест 1: Сложение положительных чисел
    {
        LongNumber num1(123.456789, 40);
        LongNumber num2(987.654321, 40);
        LongNumber res = num1 + num2;
        double expected = 1111.11111;
        std::cout << "TEST 1: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 2: Вычитание положительных чисел
    {
        LongNumber num1(1000.123456, 40);
        LongNumber num2(500.54321, 40);
        LongNumber res = num1 - num2;
        double expected = 499.580246;
        std::cout << "TEST 2: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 3: Умножение положительных чисел
    {
        LongNumber num1(12.3456789, 40);
        LongNumber num2(9.87654321, 40);
        LongNumber res = num1 * num2;
        double expected = 121.931849;
        std::cout << "TEST 3: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 4: Деление положительных чисел
    {
        LongNumber num1(1000.0, 40);
        LongNumber num2(3.0, 40);
        LongNumber res = num1 / num2;
        double expected = 333.333333;
        std::cout << "TEST 4: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 5: Сложение отрицательных чисел
    {
        LongNumber num1(-123.456789, 40);
        LongNumber num2(-987.654321, 40);
        LongNumber res = num1 + num2;
        double expected = -1111.11111;
        std::cout << "TEST 5: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 6: Вычитание с отрицательным результатом
    {
        LongNumber num1(500.54321, 40);
        LongNumber num2(1000.123456, 40);
        LongNumber res = num1 - num2;
        double expected = -499.580246;
        std::cout << "TEST 6: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 7: Умножение отрицательного и положительного числа
    {
        LongNumber num1(-12.3456789, 40);
        LongNumber num2(9.87654321, 40);
        LongNumber res = num1 * num2;
        double expected = -121.931849;
        std::cout << "TEST 7: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 8: Деление отрицательного числа на положительное
    {
        LongNumber num1(-1000.0, 40);
        LongNumber num2(3.0, 40);
        LongNumber res = num1 / num2;
        double expected = -333.333333;
        std::cout << "TEST 8: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 9: Сложение нуля
    {
        LongNumber num1(0.0, 40);
        LongNumber num2(123.456789, 40);
        LongNumber res = num1 + num2;
        double expected = 123.456789;
        std::cout << "TEST 9: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 40: Умножение на ноль
    {
        LongNumber num1(123.456789, 40);
        LongNumber num2(0.0, 40);
        LongNumber res = num1 * num2;
        double expected = 0.0;
        std::cout << "TEST 40: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 11: Деление нуля на положительное число
    {
        LongNumber num1(0.0, 40);
        LongNumber num2(123.456789, 40);
        LongNumber res = num1 / num2;
        double expected = 0.0;
        std::cout << "TEST 11: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 12: Деление на ноль (должно выбрасывать исключение)
    {
        try {
            LongNumber num1(123.456789, 40);
            LongNumber num2(0.0, 40);
            LongNumber res = num1 / num2;
            std::cout << "TEST 12: FAIL (no exception thrown)\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "TEST 12: OK (exception thrown)\n";
        }
    }

    // Тест 13: Большие числа
    {
        LongNumber num1(1e6, 40);
        LongNumber num2(1e6, 40);
        LongNumber res = num1 + num2;
        double expected = 2000000.0;
        std::cout << "TEST 13: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 14: Маленькие числа
    {
        LongNumber num1(1e-6, 40);
        LongNumber num2(1e-6, 40);
        LongNumber res = num1 + num2;
        double expected = 2e-6;
        std::cout << "TEST 14: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 15: Очень маленькие числа
    {
        LongNumber num1(1e-18, 40);
        LongNumber num2(1e-18, 40);
        LongNumber res = num1 + num2;
        double expected = 2e-18;
        std::cout << "TEST 15: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 16: Приближенное вычисление числа пи
    {
        LongNumber num1(355.0, 40);
        LongNumber num2(113.0, 40);
        LongNumber res = num1 / num2;
        double expected = 3.1415929203539825;
        std::cout << "TEST 16: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }

    // Тест 17: Еще одно приближенное вычисление числа пи
    {
        LongNumber num1(22.0, 40);
        LongNumber num2(7.0, 40);
        LongNumber res = num1 / num2;
        double expected = 3.142857142857143;
        std::cout << "TEST 17: " << (std::abs(res.getValue() - expected) < 1e-5 ? "OK" : "FAIL") << "\n";
        std::cout << "Result: " << res.getValue() << "\n";
    }
}
