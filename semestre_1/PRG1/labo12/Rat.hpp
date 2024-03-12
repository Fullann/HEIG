// Rat.h
#ifndef RAT_H
#define RAT_H

#include "Sint.hpp"
#include <iostream>

class Rat
{
public:
    Rat();
    Rat(const Sint &numerator, const Sint &denominator);
    explicit Rat(const Sint &integerPart);

    Rat &operator+=(const Rat &rhs);
    Rat &operator-=(const Rat &rhs);
    Rat &operator*=(const Rat &rhs);
    Rat &operator/=(const Rat &rhs);

    bool operator==(const Rat &rhs) const;
    bool operator!=(const Rat &rhs) const;
    bool operator<(const Rat &rhs) const;
    bool operator<=(const Rat &rhs) const;
    bool operator>(const Rat &rhs) const;
    bool operator>=(const Rat &rhs) const;
    Rat operator-() const;

    friend std::ostream &operator<<(std::ostream &os, const Rat &obj);
    friend std::istream &operator>>(std::istream &is, Rat &obj);

    static void validateDenominator(const Sint &denominator);
private:
    Sint numerator;
    Sint denominator;

    void normalize();
};

Rat operator+(const Rat &lhs, const Rat &rhs);
Rat operator-(const Rat &lhs, const Rat &rhs);
Rat operator*(const Rat &lhs, const Rat &rhs);
Rat operator/(const Rat &lhs, const Rat &rhs);

#endif // RAT_H
