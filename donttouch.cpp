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

    number = abs(number);
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

LongNumber::~LongNumber() {}

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

    dividend.make_fixed_precision(max_precision);

    res.sign = (dividend.sign == divisor.sign);
    dividend.sign = true;
    divisor.sign = true;

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

    res.Normalize();
    return res;
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