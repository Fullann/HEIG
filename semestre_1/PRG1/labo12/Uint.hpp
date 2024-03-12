// Uint.h
#ifndef UINT_H
#define UINT_H

#include <string>
#include <cstdint>
#include <stdexcept>

class Uint
{
public:
    Uint();
    explicit Uint(uint64_t value);
    [[nodiscard]] std::pair<Uint, Uint> divide(const Uint &divisor) const;

    Uint &operator+=(const Uint &rhs);
    Uint &operator-=(const Uint &rhs);
    Uint &operator*=(const Uint &rhs);
    Uint &operator/=(const Uint &rhs);

    [[nodiscard]] int compare(const Uint &other) const;
    [[nodiscard]] bool isEqual(const Uint &other) const;

    [[nodiscard]] std::string toString() const;
    friend std::ostream &operator<<(std::ostream &os, const Uint &obj);
    friend std::istream &operator>>(std::istream &is, Uint &obj);

    static void validateDivision(const Uint &divisor);
private:
    std::string data;
    int base;

    static const int DEFAULT_BASE = 10;

    void validateBase() const;
    void validateNonNegative() const;
    void removeLeadingZeros();
    [[nodiscard]] char digitToChar(int digit) const;
    [[nodiscard]] static int charToDigit(char c);
};

Uint operator+(const Uint &lhs, const Uint &rhs);
Uint operator-(const Uint &lhs, const Uint &rhs);
Uint operator*(const Uint &lhs, const Uint &rhs);
Uint operator/(const Uint &lhs, const Uint &rhs);
bool operator==(const Uint &lhs, const Uint &rhs);
bool operator!=(const Uint &lhs, const Uint &rhs);
bool operator<(const Uint &lhs, const Uint &rhs);
bool operator<=(const Uint &lhs, const Uint &rhs);
bool operator>(const Uint &lhs, const Uint &rhs);
bool operator>=(const Uint &lhs, const Uint &rhs);

#endif // UINT_H
