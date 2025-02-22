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
    int mx_prec = std::max(precision, other.precision);

    LongNumber res(0, mx_prec);
    LongNumber first(*this), second(other);

    first.make_fixed_precision(mx_prec);
    second.make_fixed_precision(mx_prec);

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

    if (other.bits.size() == 1 && other.bits[0] == 0)
    {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

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

std::string LongNumber::multiplyByTwo(const std::string &s) const
{
    std::string result = "";
    int carry = 0;
    for (int i = (int)s.size() - 1; i >= 0; --i)
    {
        int digit = s[i] - '0';
        int value = digit * 2 + carry;
        carry = value / 10;
        result.push_back(char(value % 10 + '0'));
    }

    result.push_back(char('0' + carry));

    std::reverse(result.begin(), result.end());
    return result;
}

std::string LongNumber::divideByTwo(const std::string &s) const
{
    std::string result = "";
    int carry = 0;
    for (char c : s)
    {
        int digit = c - '0';
        int value = carry * 10 + digit;
        carry = value % 2;
        result.push_back(char('0' + value / 2));
    }
    while(carry != 0){
        carry *= 10;
        result.push_back(char('0' + carry /2));
        carry %= 2;
    }
    return result;
}

std::string LongNumber::addTwoStrings(const std::string &num1, const std::string &num2, int type) const
{
    int len = std::max(num1.size(), num2.size());
    std::string a(num1), b(num2);
    if (type == 0)
    {
        a.insert(a.begin(), len - num1.size(), '0');
        b.insert(b.begin(), len - num2.size(), '0');
    }
    else
    {
        a.insert(a.end(), len - num1.size(), '0');
        b.insert(b.end(), len - num2.size(), '0');
    }
    std::string result = "";
    int carry = 0;
    for (int i = len - 1; i >= 0; --i)
    {
        int digit1 = (i < a.size() ? a[i] : '0') - '0';
        int digit2 = (i < b.size() ? b[i] : '0') - '0';
        int value = digit1 + digit2 + carry;
        carry = value / 10;
        value %= 10;
        result.push_back(char('0' + value));
    }
    if(type == 0)
        result.push_back(char('0' + carry));
    std::reverse(result.begin(), result.end());
    return result;
}

std::string LongNumber::getValue() const
{
    std::string int_part = "", frac_part = "";
    std::string t = "1";

    for (int i = (int)bits.size() - point - 1; i >= 0; --i)
    {
        if (bits[i])
            int_part = addTwoStrings(int_part, t, 0);

        if (i > 0)
            t = multiplyByTwo(t);

        while (t[0] == '0')
            t.erase(t.begin());

        while (int_part[0] == '0')
            int_part.erase(int_part.begin());
    }

    t = "5";
    for (int i = (int)bits.size() - point; i < (int)bits.size(); ++i)
    {
        if (bits[i])
            frac_part = addTwoStrings(frac_part, t, 1);

        if (i < bits.size() - 1)
            t = divideByTwo(t);

        while (t.back() == '0')
            t.pop_back();

        while (frac_part.back() == '0')
            frac_part.pop_back();
    }

    while (int_part[0] == '0')
        int_part.erase(int_part.begin());

    while (frac_part.back() == '0')
        frac_part.pop_back();

    return int_part + "." + frac_part;
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

// int main()
// {
//     {
//         LongNumber num1(123.456789, 60);
//         LongNumber num2(987.654321, 60);
//         LongNumber res = num1 + num2;
//         double expected = 1111.11111;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1000.123456, 40);
//         LongNumber num2(500.54321, 40);
//         LongNumber res = num1 - num2;
//         double expected = 499.580246;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(12.3456789, 40);
//         LongNumber num2(9.87654321, 40);
//         LongNumber res = num1 * num2;
//         double expected = 121.932631;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1000.0, 40);
//         LongNumber num2(3.0, 40);
//         LongNumber res = num1 / num2;
//         double expected = 333.333333;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1982.23487297, 100);
//         LongNumber num2(87284.187391, 100);
//         LongNumber res = num1 / num2;
//         double expected = 0.022725849;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(192.23487297, 60);
//         LongNumber num2(8784.187391, 60);
//         LongNumber res = num1 * num2;
//         double expected = 1688627.1472535606;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(87284.187391, 40);
//         LongNumber num2(0.000123456, 40);
//         LongNumber res = num1 * num2;
//         double expected = 10.77575663;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1.000123456, 40);
//         LongNumber num2(1.000987654, 40);
//         LongNumber res = num1 * num2;
//         double expected = 1.001111577626;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(0.0, 40);
//         LongNumber num2(123.456789, 40);
//         LongNumber res = num1 + num2;
//         double expected = 123.456789;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(123.456789, 40);
//         LongNumber num2(0.0, 40);
//         LongNumber res = num1 * num2;
//         double expected = 0.0;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(0.0, 40);
//         LongNumber num2(123.456789, 40);
//         LongNumber res = num1 / num2;
//         double expected = 0.0;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1e6, 40);
//         LongNumber num2(1e6, 40);
//         LongNumber res = num1 + num2;
//         double expected = 2000000.0;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1e-6, 40);
//         LongNumber num2(1e-6, 40);
//         LongNumber res = num1 + num2;
//         double expected = 2e-6;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1.000123456, 40);
//         LongNumber num2(1.000987654, 40);
//         LongNumber res = num1 / num2;
//         double expected = 0.99913665468;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(355.0, 40);
//         LongNumber num2(113.0, 40);
//         LongNumber res = num1 / num2;
//         double expected = 3.1415929203539825;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(22.0, 40);
//         LongNumber num2(7.0, 40);
//         LongNumber res = num1 / num2;
//         double expected = 3.142857142857143;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }
// }

/*
g++ -c LongNumber.cpp -o LongNumber.o
ar cr LongNumber.a LongNumber.o
g++ -c Tests.cpp -o Tests.o
g++ Tests.o LongNumber.a -o Tests.exe

*/
