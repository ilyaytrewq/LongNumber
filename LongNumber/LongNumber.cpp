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
    bits.insert(bits.end(), precision + 1, 0);
    precision = Max_Precision;
}

LongNumber::LongNumber(int number, unsigned int _precision)
{
    sign = (number >= 0);
    precision = _precision;

    if (number == 0)
    {
        bits.insert(bits.end(), precision + 1, 0);
        return;
    }

    number = abs(number);
    while (number > 0)
    {
        bits.push_back(number % 2);
        number >>= 1;
    }

    std::reverse(bits.begin(), bits.end());

    bits.insert(bits.end(), precision, 0);
}

LongNumber::LongNumber::LongNumber(double number, unsigned int _precision)
{
    precision = _precision;
    sign = (number >= 0);
    if (number == 0)
    {
        bits.insert(bits.end(), precision + 1, 0);
        return;
    }
    if (number < 0)
        number = -number;
    int exp;
    double mnt = std::frexp(number, &exp);

    int it = 0;
    while (mnt != 0.0 && int(bits.size()) <= precision + exp)
    {
        mnt *= 2;
        int bit = static_cast<int>(mnt);
        bits.push_back(bit);
        mnt -= bit;
        it++;
    }

    if (int(bits.size()) <= precision + exp)
    {
        bits.insert(bits.end(), precision + exp - (int)bits.size(), 0);
    }

    if (bits.size() < precision + 1)
    {
        bits.insert(bits.begin(), precision + 1 - (int)bits.size(), 0);
    }

    Normalize();
}

LongNumber::LongNumber::LongNumber(long double number, unsigned int _precision)
{
    precision = _precision;
    sign = (number >= 0);
    if (number == 0)
    {
        bits.insert(bits.end(), precision, 0);
        return;
    }
    if (number < 0)
        number = -number;
    int exp;
    long double mnt = std::frexp(number, &exp);

    int it = 0;
    while (mnt != 0 && (int)bits.size() <= precision + exp)
    {
        mnt *= 2;
        int bit = static_cast<int>(mnt);
        bits.push_back(bit);
        mnt -= bit;
        it++;
    }

    if ((int)bits.size() <= precision + exp)
    {
        bits.insert(bits.end(), precision + exp - (int)bits.size(), 0);
    }

    if (bits.size() < precision + 1)
    {
        bits.insert(bits.begin(), precision + 1 - (int)bits.size(), 0);
    }
    Normalize();
}

LongNumber::LongNumber(const LongNumber &other)
{
    bits = other.bits;
    precision = other.precision;
    sign = other.sign;
}

LongNumber::~LongNumber()
{
    bits.clear();
    bits.shrink_to_fit();
}

int LongNumber::get_magnitude() const
{
    return (int)bits.size() - precision;
}

void LongNumber::make_fixed_precision(unsigned int _precision)
{
    if (_precision < precision)
    {
        bits.resize(bits.size() - (precision - _precision));
    }
    else
    {
        bits.insert(bits.end(), _precision - precision, 0);
    }

    precision = _precision;
}

void LongNumber::make_fixed_magnitude(unsigned int magn)
{
    bits.insert(bits.begin(), std::max((unsigned int)0, magn - get_magnitude()), 0);
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
    sign = other.sign;
    return *this;
}

bool LongNumber::operator==(const LongNumber &other) const
{
    // if (bits.size() != other.bits.size())
    //     return false;

    // for (int i = 0; i < (int)bits.size(); ++i)
    // {
    //     if (bits[i] != other.bits[i])
    //         return false;
    // }

    return bits == other.bits;
}

bool LongNumber::operator!=(const LongNumber &other) const
{
    return !(*this == other);
}

bool LongNumber::operator<(const LongNumber &other) const
{
    if (get_magnitude() != other.get_magnitude())
        return get_magnitude() < other.get_magnitude();

    // for (int i = 0; i < (int)bits.size(); ++i)
    // {
    //     if (bits[i] != other.bits[i])
    //         return bits[i] < other.bits[i];
    // }

    return bits < other.bits;
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
    if(bits[0] == 1)
        return;


    int pos = -1;
    for (int i = 0; i < get_magnitude() - 1; ++i)
    {
        if (bits[i] > 0)
        {
            break;
        }
        pos = i;
    }

    bits.erase(bits.begin(), bits.begin() + pos + 1);
}

LongNumber LongNumber::sum_of_positive(const LongNumber &number1, const LongNumber &number2) const
{
    unsigned int new_precision = std::max(number1.precision, number2.precision);
    unsigned int new_magnitude = std::max(number1.get_magnitude(), number2.get_magnitude());

    LongNumber first(number1), second(number2), ans(0, new_precision);

    first.make_fixed(new_magnitude, new_precision);
    second.make_fixed(new_magnitude, new_precision);
    ans.make_fixed_magnitude(new_magnitude + 1);

    unsigned int carry = 0;
    for (int i = (int)first.bits.size() - 1; i >= 0; --i)
    {
        ans.bits[i + 1] = (first.bits[i] ^ second.bits[i] ^ carry);
        carry = (first.bits[i] + second.bits[i] + carry) >> 1;
    }

    ans.bits[0] = carry;
    ans.Normalize();

    return ans;
}

LongNumber LongNumber::diff_of_positive(const LongNumber &number1, const LongNumber &number2) const // number1 >= number2
{
    unsigned int new_precision = std::max(number1.precision, number2.precision);
    unsigned int new_magnitude = std::max(number1.get_magnitude(), number2.get_magnitude());

    LongNumber first(number1), second(number2), ans(0, 0);

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
    if (shift >= (int)bits.size())
        return LongNumber(0, precision);

    LongNumber ans(*this);

    ans.bits.erase(ans.bits.end() - shift, ans.bits.end());

    if (ans.get_magnitude() < shift)
        ans.bits.insert(ans.bits.begin(), shift - ans.get_magnitude(), 0);

    ans.Normalize();

    return ans;
}

LongNumber LongNumber::operator*(const LongNumber &other) const
{
    //     int new_precision = precision + other.precision;
    //     int size = bits.size() + other.bits.size();

    //     LongNumber res;
    //     res.bits.assign(size, 0);

    //     for (int i = (int)bits.size() - 1; i >= 0; --i)
    //     {
    //         int carry = 0;
    //         for (int j = (int)other.bits.size() - 1; j >= 0; --j)
    //         {
    //             int product = bits[i] * other.bits[i] + res.bits[i + j + 1] + carry;
    //             res.bits[i + j + 1] = product & 1;
    //             carry = product >> 1;
    //         }
    //         res.bits[i] = carry;
    //     }

    //     // res.precision = std::max(precision, other.precision);
    //     res.precision = new_precision;
    //     res.sign = (sign == other.sign);
    //     // res.bits.erase(res.bits.end() - (precision + other.precision - res.precision), res.bits.end());

    //     res.Normalize();

    //     return res;

    int mx_prec = std::max(precision, other.precision);

    LongNumber res(0, mx_prec);

    LongNumber num(*this);
    num.make_fixed_precision(mx_prec);

    for (int i = (int)other.bits.size() - other.precision - 1; i >= 0; --i)
    {
        if (other.bits[i])
            res = res + num;

        num = num << 1;
    }

    num = *this >> 1;
    num.make_fixed_precision(mx_prec);

    for (int i = (int)other.bits.size() - other.precision; i < (int)other.bits.size(); ++i)
    {
        if (other.bits[i])
            res = res + num;

        num = num >> 1;
    }

    res.Normalize();

    return res;
}

LongNumber LongNumber::operator/(const LongNumber &other) const
{

    if (other.bits.size() == 1 + other.precision && other.bits[0] == 0)
    {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    LongNumber dividend(*this), divisor(other);

    int max_precision = std::max(dividend.precision, divisor.precision);

    LongNumber res(0, max_precision);

    divisor.sign = true;
    dividend.sign = true;

    int cnt = divisor.precision;
    for(int i = divisor.bits.size() - 1; i >= divisor.bits.size() - divisor.precision; --i){
        if(divisor.bits[i] == 1)
            break;
        cnt--;
    }

    divisor.bits.resize(divisor.bits.size() - (divisor.precision - cnt));

    if (dividend.precision >= cnt)
    {
        dividend.precision -= cnt;
    }
    else
    {
        dividend.bits.insert(dividend.bits.end(), cnt - dividend.precision, 0);
        dividend.precision = 0;
    }

    int add = max_precision - dividend.precision;
    dividend.precision = max_precision;
    divisor.precision = 0;

    LongNumber temp(0, 0);


    for (int i = 0; i < (int)divisor.bits.size() - 1; ++i)
    {
        temp.bits.push_back(dividend.bits[i]);
    }
    temp.Normalize();


    for (int i = (int)divisor.bits.size() - 1; i < (int)dividend.bits.size() + add; ++i)
    {
        if (temp.bits.size() > 1 || temp.bits[0] > 0)
            temp.bits.push_back(0);
        if (i < dividend.bits.size() && dividend.bits[i])
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
    }

    res.precision = dividend.precision;
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
    while (carry != 0)
    {
        carry *= 10;
        result.push_back(char('0' + carry / 2));
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
    if (type == 0)
        result.push_back(char('0' + carry));
    std::reverse(result.begin(), result.end());
    return result;
}

std::string LongNumber::getValue() const
{
    std::string int_part = "", frac_part = "";
    std::string t = "1";

    for (int i = (int)bits.size() - precision - 1; i >= 0; --i)
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
    for (int i = (int)bits.size() - precision; i < (int)bits.size(); ++i)
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

    if (int_part.empty())
        int_part = "0";
    if (frac_part.empty())
        frac_part = "0";

    return int_part + "." + frac_part;
}

std::ostream &operator<<(std::ostream &out, const LongNumber &number)
{
    out << number.getValue();
    return out;
}

LongNumber operator""_longnum(long double number)
{
    return LongNumber(number, Max_Precision);
}

// int main()
// {

//     std::cout.precision(100);

//     // while (1)
//     // {
//     //     double a, b;
//     //     std::cin >> a >> b;
//     //     std::cout << a * b << '\n';
//     //     LongNumber A(a, 200), B(b, 200);
//     //     // std::cout << A << '\n'
//     //     //           << B << '\n';
//     //     std::cout << A * B << '\n';
//     //     std::cout << a / b << '\n';
//     //     std::cout << A / B << '\n';
//     // }

//     {
//         LongNumber num1(123.456789, 100);
//         LongNumber num2(987.654321, 100);
//         LongNumber res = num1 + num2;
//         double expected = 1111.11111;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1000.123456, 100);
//         LongNumber num2(500.54321, 100);
//         LongNumber res = num1 - num2;
//         double expected = 499.580246;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(12.3456789, 100);
//         LongNumber num2(9.87654321, 100);
//         LongNumber res = num1 * num2;
//         double expected = 121.932631;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1000.0, 100);
//         LongNumber num2(3.0, 100);
//         LongNumber res = num1 / num2;
//         double expected = 333.333333;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1982.23487297, 100);
//         LongNumber num2(87284.187391, 100);
//         LongNumber res = num1 / num2;
//         double expected = 0.022710125765281412;
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
//         LongNumber num1(87284.187391, 100);
//         LongNumber num2(0.000123456, 100);
//         LongNumber res = num1 * num2;
//         double expected = 10.77575663;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1.000123456, 100);
//         LongNumber num2(1.000987654, 100);
//         LongNumber res = num1 * num2;
//         double expected = 1.001111577626;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(0.0, 100);
//         LongNumber num2(123.456789, 100);
//         LongNumber res = num1 + num2;
//         double expected = 123.456789;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(123.456789, 100);
//         LongNumber num2(0.0, 100);
//         LongNumber res = num1 * num2;
//         double expected = 0.0;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(0.0, 100);
//         LongNumber num2(123.456789, 100);
//         LongNumber res = num1 / num2;
//         double expected = 0.0;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1e6, 100);
//         LongNumber num2(1e6, 100);
//         LongNumber res = num1 + num2;
//         double expected = 2000000.0;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1e-6, 100);
//         LongNumber num2(1e-6, 100);
//         LongNumber res = num1 + num2;
//         double expected = 2e-6;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(1.000123456, 100);
//         LongNumber num2(1.000987654, 100);
//         LongNumber res = num1 / num2;
//         double expected = 0.99913665468;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(355.0, 100);
//         LongNumber num2(113.0, 100);
//         LongNumber res = num1 / num2;
//         double expected = 3.1415929203539825;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }

//     {
//         LongNumber num1(22.0, 100);
//         LongNumber num2(7.0, 100);
//         LongNumber res = num1 / num2;
//         double expected = 3.142857142857143;
//         std::cout << "Result: " << res.getValue() << "\n";
//     }
// }

// /*
// g++ -c LongNumber.cpp -o LongNumber.o
// ar cr LongNumber.a LongNumber.o
// g++ -c Tests.cpp -o Tests.o
// g++ Tests.o LongNumber.a -o Tests.exe

// */
