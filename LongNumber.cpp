#include "LongNumber.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>

#define Max_Precision 1000

LongNumber::LongNumber()
{
    sign = true;
    point = 0;
    bits.push_back(0);
    precision = Max_Precision;
}

LongNumber::LongNumber(int number, unsigned int _precision)
{
    sign = (number >= 0);
    point = 0;
    precision = _precision;

    if (number == 0)
    {
        bits.push_back(0);
        return;
    }

    number = abs(number);
    while (number > 0)
    {
        bits.push_back(number % 2);
        number >>= 1;
    }

    std::reverse(bits.begin(), bits.end());
}

LongNumber::LongNumber::LongNumber(double number, unsigned int _precision)
{

    precision = _precision;
    sign = (number >= 0);
    point = 0;
    bits.push_back(0);

    if (number == 0)
    {
        return;
    }
    if (number < 0)
        number = -number;
    int exp;
    double mnt = std::frexp(number, &exp);

    while (mnt != 0 && bits.size() < 2 * (precision + abs(exp)))
    {
        mnt *= 2;
        int bit = static_cast<int>(mnt);
        bits.push_back(bit);
        mnt -= bit;
        point++;
    }

    if (exp < 0)
        *this = *this >> -exp;
    else
        *this = *this << exp;

    Normalize();
}

LongNumber::LongNumber::LongNumber(long double number, unsigned int _precision)
{

    precision = _precision;
    sign = (number >= 0);
    point = 0;
    bits.push_back(0);

    if (number == 0)
    {
        return;
    }
    if (number < 0)
        number = -number;
    int exp;
    long double mnt = std::frexp(number, &exp);

    while (mnt != 0 && bits.size() < 2 * (precision + abs(exp)))
    {
        mnt *= 2;
        int bit = static_cast<int>(mnt);
        bits.push_back(bit);
        mnt -= bit;
        point++;
    }

    if (exp < 0)
        *this = *this >> -exp;
    else
        *this = *this << exp;

    Normalize();
}

LongNumber::LongNumber(std::string s, unsigned int _precicsion)
{
    if (s[0] == '-')
        sign = false;
    else
        sign = true;

    precision = _precicsion;
    for (char bit : s)
    {
        if (bit == '.')
        {
            point = 0;
            continue;
        }

        bits.push_back(bit - '0');
        point++;

        if (point == precision)
            break;
    }
}

LongNumber::LongNumber(const LongNumber &other)
{
    bits = other.bits;
    precision = other.precision;
    point = other.point;
    sign = other.sign;
}

LongNumber::~LongNumber()
{
    bits.clear();
    bits.shrink_to_fit();
}

int LongNumber::get_magnitude() const
{
    return (int)bits.size() - point;
}

void LongNumber::make_fixed_precision(unsigned int _precision)
{
    while (_precision < point)
    {
        point--;
        bits.pop_back();
    }

    while (point < _precision)
    {
        point++;
        bits.push_back(0);
    }

    precision = _precision;
}

void LongNumber::make_fixed_magnitude(unsigned int magn)
{
    while (get_magnitude() < magn)
        bits.insert(bits.begin(), 0);
}

void LongNumber::make_fixed(unsigned int magn, unsigned int _precision)
{
    make_fixed_magnitude(magn);
    make_fixed_precision(_precision);
}

LongNumber &LongNumber::operator=(const LongNumber &other)
{
    bits = other.bits;
    precision = other.precision;
    point = other.point;
    sign = other.sign;
    return *this;
}

bool LongNumber::operator==(const LongNumber &other) const
{
    if (bits.size() != other.bits.size()) // что делать если разный precision?
        return false;

    if (point != other.point)
        return false;

    for (int i = 0; i < (int)bits.size(); ++i)
    {
        if (bits[i] != other.bits[i])
            return false;
    }

    return true;
}

bool LongNumber::operator!=(const LongNumber &other) const
{
    return !(*this == other);
}

bool LongNumber::operator<(const LongNumber &other) const
{
    if (get_magnitude() != other.get_magnitude())
        return get_magnitude() < other.get_magnitude();

    for (int i = 0; i < (int)bits.size(); ++i)
    {
        if (bits[i] != other.bits[i])
            return bits[i] < other.bits[i];
    }
    return false;
}

bool LongNumber::operator<=(const LongNumber &other) const
{
    return *this < other || *this == other;
}

bool LongNumber::operator>(const LongNumber &other) const
{
    return !(*this <= other);
}

bool LongNumber::operator>=(const LongNumber &other) const
{
    return !(*this < other);
}

LongNumber LongNumber::negative(const LongNumber &number) const
{
    LongNumber ans(number);
    ans.sign = !ans.sign;
    return ans;
}

void LongNumber::Normalize()
{
    while (point > precision || (point > 0 && bits.back() == false))
    {
        bits.pop_back();
        point--;
    }
    while (get_magnitude() > 1 && bits[0] == false)
    {
        bits.erase(bits.begin());
    }
}

LongNumber LongNumber::sum_of_positive(const LongNumber &number1, const LongNumber &number2) const
{
    unsigned int new_precision = std::max(number1.precision, number2.precision);
    unsigned int new_magnitude = std::max(number1.get_magnitude(), number2.get_magnitude());

    LongNumber first(number1), second(number2), ans;

    first.make_fixed(new_magnitude, new_precision);
    second.make_fixed(new_magnitude, new_precision);
    ans.make_fixed(new_magnitude, new_precision);

    unsigned int carry = 0;
    for (int i = (int)first.bits.size() - 1; i >= 0; --i)
    {
        ans.bits[i] = (first.bits[i] ^ second.bits[i] ^ carry);
        carry = (first.bits[i] + second.bits[i] + carry) >> 1;
    }

    if (carry)
    {
        ans.bits.insert(ans.bits.begin(), 1);
    }

    ans.Normalize();

    return ans;
}

LongNumber LongNumber::diff_of_positive(const LongNumber &number1, const LongNumber &number2) const // number1 >= number2
{
    unsigned int new_precision = std::max(number1.precision, number2.precision);
    unsigned int new_magnitude = std::max(number1.get_magnitude(), number2.get_magnitude());

    LongNumber first(number1), second(number2), ans;

    first.make_fixed(new_magnitude, new_precision);
    second.make_fixed(new_magnitude, new_precision);
    ans.make_fixed(new_magnitude, new_precision);

    bool borrow = false;

    for (int i = (int)first.bits.size() - 1; i >= 0; --i)
    {
        bool bit1 = first.bits[i];
        bool bit2 = second.bits[i];

        ans.bits[i] = (bit1 ^ bit2 ^ borrow);

        if ((bit1 == false && bit2 == true) || (bit1 == false && borrow == true) || (bit2 == true && borrow == true))
            borrow = true;
        else
            borrow = false;
    }

    ans.Normalize();

    return ans;
}

LongNumber LongNumber::operator+(const LongNumber &other) const // ans precision = max(this prec, other prec)
{
    if (sign && other.sign)
        return sum_of_positive(*this, other);

    if (sign == false && other.sign == false)
    {
        LongNumber ans = sum_of_positive(*this, other);
        ans.sign = !ans.sign;
        return ans;
    }

    if (sign == true && other.sign == false)
    {
        if (*this > negative(other))
            return diff_of_positive(*this, other);
        else
            return negative(diff_of_positive(other, *this));
    }
    else
    {
        if (negative(*this) < other)
            return diff_of_positive(other, *this);
        else
            return diff_of_positive(*this, other);
    }
}

LongNumber LongNumber::operator-(const LongNumber &other) const
{
    if (sign == true && other.sign == true)
    {
        if (*this > other)
            return diff_of_positive(*this, other);
        else
            return negative(diff_of_positive(other, *this));
    }

    if (sign == false && other.sign == false)
        return *this + negative(other);

    if (sign == true && other.sign == false)
        return sum_of_positive(*this, other);

    if (sign == false && other.sign == true)
        return negative(sum_of_positive(*this, other));

    return *this;
}

LongNumber LongNumber::operator<<(unsigned int shift) const
{
    LongNumber ans(*this);

    ans.bits.insert(ans.bits.end(), shift, 0);

    ans.Normalize();

    return ans;
}

LongNumber LongNumber::operator>>(unsigned int shift) const
{
    LongNumber ans(*this);

    ans.point += shift;

    ans.bits.insert(ans.bits.begin(), shift, 0);

    ans.Normalize();

    return ans;
}

LongNumber LongNumber::operator*(const LongNumber &other) const
{
    LongNumber res(0, std::max(precision, other.precision));
    LongNumber first(*this), second(other);

    first.sign = second.sign = true;

    for (int i = 0; i < (int)second.bits.size(); ++i)
    {
        if (second.bits[i] == false)
            continue;

        int shift = ((int)second.bits.size() - second.point - 1) - i;

        if (shift >= 0)
        {
            res = res + (first << shift);
        }
        else
        {
            shift = -shift;
            res = res + (first >> shift);
        }
    }

    res.sign = (sign == other.sign);
    res.Normalize();

    return res;
}

LongNumber LongNumber::operator/(const LongNumber &other) const
{

    /*
        обработать случай other = 0
    */

    LongNumber dividend(*this), divisor(other);

    int max_precision = std::max(dividend.precision, divisor.precision);

    LongNumber res(0, max_precision);

    dividend = dividend << divisor.point;
    divisor = divisor << divisor.point;

    divisor.sign = true;
    dividend.sign = true;

    dividend.make_fixed_precision(max_precision);

    LongNumber temp(0, max_precision);

    for (int i = 0; i < (int)dividend.bits.size(); ++i)
    {
        temp = temp << 1;
        temp.bits[(int)temp.bits.size() - 1] = dividend.bits[i];

        if (temp >= divisor)
        {
            temp = diff_of_positive(temp, divisor);
            res.bits.push_back(true);
        }
        else
        {
            res.bits.push_back(false);
        }
        if (i >= dividend.bits.size() - dividend.point)
            res.point++;
    }

    res.sign = (this->sign == other.sign);
    res.Normalize();
    return res;
}

long double LongNumber::getValue() const
{
    long double ans = 0;
    for (int i = 0; i < bits.size() - point; ++i)
    {
        ans *= 2;
        ans += bits[i];
    }
    long double x = 0.5;
    for (int i = bits.size() - point; i < bits.size(); ++i)
    {
        ans += bits[i] * x;
        x /= 2;
    }
    return ans * (sign ? 1 : -1);
}

std::ostream &operator<<(std::ostream &out, const LongNumber &number)
{
    out << "sign = " << number.sign << ' ' << "point = " << number.point << ' ' << "precision = " << number.precision << '\n';
    for (auto i : number.bits)
        out << i;
    long long ans = 0;
    // for (auto i : number.bits)
    // {
    //     ans *= 2;
    //     ans += i;
    // }
    // out << (number.sign ? 1 : -1) * ans;
    return out;
}

LongNumber operator""_longnum(long double number)
{
    return LongNumber(number, Max_Precision);
}

/*
main
*/

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


// int main()
// {
//     int n;
//     std::cin >> n;
//     for (int i = 0; i < n; ++i)
//     {
//         long double a, b;
//         std::cin >> a >> b;
//         LongNumber A(a, 20), B(b, 20);
//         std::cout << "Numbers A and B\n";
//         std::cout << A << '\n'
//                   << B << '\n';
//         std::cout << "A + B\n"
//                   << A + B << '\n';
//         std::cout << "A - B\n"
//                   << A - B << "\n";
//         std::cout << "A * B\n"
//                   << A * B << "\n";
//         std::cout << "A / B\n"
//                   << A / B << '\n';
//     }

//     return 0;
// }