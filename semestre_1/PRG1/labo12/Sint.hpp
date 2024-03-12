// Sint.h
#ifndef SINT_H
#define SINT_H

#include "Uint.hpp"

class Sint
{
public:
    Sint();
    Sint(int64_t value);
    Sint(const Uint &uintValue, bool isNegative);
    Uint uintPart;
    bool isNegative;
    static const Sint ZERO;
    Sint operator-() const;

    Sint &operator+=(const Sint &rhs);
    Sint &operator-=(const Sint &rhs);
    Sint &operator*=(const Sint &rhs);
    Sint &operator/=(const Sint &rhs);

    Sint operator%(const Sint &rhs) const;
    bool operator==(const Sint &rhs) const;
    bool operator!=(const Sint &rhs) const;
    bool operator<(const Sint &rhs) const;
    bool operator<=(const Sint &rhs) const;
    bool operator>(const Sint &rhs) const;
    bool operator>=(const Sint &rhs) const;

    static Sint gcd(const Sint &numerator, const Sint &denominator);

    friend std::ostream &operator<<(std::ostream &os, const Sint &obj);
    friend std::istream &operator>>(std::istream &is, Sint &obj);

private:
    void normalize();
};

Sint operator+(const Sint &lhs, const Sint &rhs);
Sint operator-(const Sint &lhs, const Sint &rhs);
Sint operator*(const Sint &lhs, const Sint &rhs);
Sint operator/(const Sint &lhs, const Sint &rhs);

#endif // SINT_H
