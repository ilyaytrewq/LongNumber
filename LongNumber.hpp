#ifndef LongNumber_HPP
#define LongNumber_HPP

#include <vector>
#include <algorithm>
#include <string>

class LongNumber
{
private:
    std::vector<bool> bits;
    unsigned int point;
    unsigned int precision;
    bool sign;

    LongNumber negative(const LongNumber &number) const;

    int get_magnitude() const;

    void make_fixed_precision(unsigned int _precision);

    void make_fixed_magnitude(unsigned int magn);

    void make_fixed(unsigned int magn, unsigned int _precision);

    void Normalize();

    LongNumber sum_of_positive(const LongNumber &number1, const LongNumber &number2) const;

    LongNumber diff_of_positive(const LongNumber &number1, const LongNumber &number2) const;

public:
    LongNumber();

    LongNumber(int, unsigned int);

    LongNumber(long double, unsigned int);

    LongNumber(std::string, unsigned int);

    LongNumber(const LongNumber & other);

    ~LongNumber();

    LongNumber &operator=(const LongNumber &other);

    bool operator==(const LongNumber &other) const;

    bool operator!=(const LongNumber &other) const;

    bool operator<(const LongNumber &other) const;

    bool operator<=(const LongNumber &other) const;

    bool operator>(const LongNumber &other) const;

    bool operator>=(const LongNumber &other) const;

    LongNumber operator+(const LongNumber &other) const;

    LongNumber operator-(const LongNumber &other) const;

    LongNumber operator*(const LongNumber &other) const;

    LongNumber operator/(const LongNumber &other) const;

    LongNumber operator<<(unsigned int shift) const;

    LongNumber operator>>(unsigned int shift) const;

    friend std::ostream& operator<<(std::ostream& out, const LongNumber& number);
};

LongNumber operator"" _longnum(long double number);

#endif // LongNumber_HPP