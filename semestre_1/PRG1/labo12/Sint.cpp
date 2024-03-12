// Sint.cpp
// Description: Déclaration de la classe Sint pour représenter un nombre entier signé
#include "Sint.hpp"
#include <iostream>
#include <stdexcept>

const Sint Sint::ZERO = Sint(0);
/**
 * @brief Constructeur par défaut de Sint
 */
Sint::Sint() : uintPart(), isNegative(false) {}
/**
 * @brief Constructeur de Sint à partir d'un int64_t
 * @param value L'entier à convertir en Sint
 */
Sint::Sint(int64_t value) : uintPart(static_cast<Uint>(std::abs(value))), isNegative(value < 0)
{
    normalize();
}
/**
 * @brief Constructeur de Sint à partir d'un Uint et d'un booléen
 * @param uintValue L'Uint à convertir en Sint
 * @param negative Le booléen indiquant si le nombre est négatif
 */
Sint::Sint(const Uint &uintValue, bool negative) : uintPart(uintValue), isNegative(negative)
{
    normalize();
}
/**
 * @brief Surcharge de l'opérateur unaire moins pour Sint
 * @return Le résultat de la négation
 */
Sint Sint::operator-() const
{
    return {uintPart, !isNegative};
}
/**
 * @brief Surcharge de l'opérateur d'addition composé pour Sint
 * @param rhs Le Sint à additionner
 * @return Le résultat de l'addition
 */
Sint &Sint::operator+=(const Sint &rhs)
{
    *this = *this + rhs;
    return *this;
}


/**
 * @brief Surcharge de l'opérateur de soustraction composé pour Sint
 * @param rhs Le Sint à soustraire
 * @return Le résultat de la soustraction
 */
Sint &Sint::operator-=(const Sint &rhs)
{
    *this = *this - rhs;
    return *this;
}

/**
 * @brief Surcharge de l'opérateur de multiplication composé pour Sint
 * @param rhs Le Sint à multiplier
 * @return Le résultat de la multiplication
 */
Sint &Sint::operator*=(const Sint &rhs)
{
    Sint result = *this * rhs;
    *this = result;
    return *this;
}
/**
 * @brief Surcharge de l'opérateur de division composé pour Sint
 * @param rhs Le Sint à diviser
 * @return Le résultat de la division
 */
Sint &Sint::operator/=(const Sint &rhs)
{
    Sint result = *this / rhs;
    *this = result;
    return *this;
}
/**
 * @brief Surcharge de l'opérateur de modulo pour Sint
 * @param rhs Le Sint à diviser
 * @return Le résultat de la division
 */
Sint Sint::operator%(const Sint &rhs) const
{
    if (rhs == ZERO)
    {
        throw std::invalid_argument("Erreur: division par zéro.");
    }

    Sint result = *this - (static_cast<Sint>(*this / rhs) * rhs);
    return result;
}
/**
 * @brief Surcharge de l'opérateur d'égalité pour Sint
 * @param rhs Le Sint à comparer
 * @return Le résultat de la comparaison
 */
bool Sint::operator==(const Sint &rhs) const
{
    return uintPart == rhs.uintPart && isNegative == rhs.isNegative;
}
/**
 * @brief Surcharge de l'opérateur de différence pour Sint
 * @param rhs Le Sint à comparer
 * @return Le résultat de la comparaison
 */
bool Sint::operator!=(const Sint &rhs) const
{
    return !(*this == rhs);
}
/**
 * @brief Surcharge de l'opérateur de comparaison inférieure pour Sint
 * @param rhs Le Sint à comparer
 * @return Le résultat de la comparaison
 */
bool Sint::operator<(const Sint &rhs) const
{
    if (isNegative == rhs.isNegative)
    {
        if (isNegative)
        {
            return uintPart > rhs.uintPart; // Ordre inverse pour les nombres négatifs
        }
        else
        {
            return uintPart < rhs.uintPart;
        }
    }
    else
    {
        return isNegative; // Négatif est toujours plus petit que positif
    }
}
/**
 * @brief Surcharge de l'opérateur de comparaison inférieure ou égale pour Sint
 * @param rhs Le Sint à comparer
 * @return Le résultat de la comparaison
 */
bool Sint::operator<=(const Sint &rhs) const
{
    return (*this < rhs) || (*this == rhs);
}
/**
 * @brief Surcharge de l'opérateur de comparaison supérieure pour Sint
 * @param rhs Le Sint à comparer
 * @return Le résultat de la comparaison
 */
bool Sint::operator>(const Sint &rhs) const
{
    return !(*this <= rhs);
}
/**
 * @brief Surcharge de l'opérateur de comparaison supérieure ou égale pour Sint
 * @param rhs Le Sint à comparer
 * @return Le résultat de la comparaison
 */
bool Sint::operator>=(const Sint &rhs) const
{
    return !(*this < rhs);
}
/**
 * @brief Calcule le PGCD de deux Sint
 * @param numerator Le numérateur
 * @param denominator Le dénominateur
 * @return Le PGCD
 */
Sint Sint::gcd(const Sint &numerator, const Sint &denominator)
{
    Sint a = numerator;
    Sint b = denominator;
    while (b != ZERO)
    {
        Sint temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
 * @brief Surcharge de l'opérateur d'affichage pour Sint
 * @param os Le flux de sortie
 * @param obj Le Sint à afficher
 * @return Le flux de sortie
 */
std::ostream &operator<<(std::ostream &os, const Sint &obj)
{
    if (obj.isNegative)
    {
        os << '-';
    }
    os << obj.uintPart;
    return os;
}
std::istream &operator>>(std::istream &is, Sint &obj)
{
    is >> obj.uintPart >> obj.isNegative;
    return is;
}
/**
 * @brief Surcharge de l'opérateur d'addition pour Sint
 * @param lhs Le premier Sint à additionner
 * @param rhs Le deuxième Sint à additionner
 * @return Le résultat de l'addition
 */
Sint operator+(const Sint &lhs, const Sint &rhs)
{
    if (lhs.isNegative == rhs.isNegative)
    {
        return {lhs.uintPart + rhs.uintPart, lhs.isNegative};
    }
    else
    {
        if (lhs.uintPart >= rhs.uintPart)
        {
            return {lhs.uintPart - rhs.uintPart, lhs.isNegative};
        }
        else
        {
            return {rhs.uintPart - lhs.uintPart, rhs.isNegative};
        }
    }
}

/**
 * @brief Surcharge de l'opérateur de soustraction pour Sint
 * @param lhs Le Sint à soustraire
 * @param rhs Le Sint à soustraire
 * @return Le résultat de la soustraction
 */
Sint operator-(const Sint &lhs, const Sint &rhs)
{
    if (lhs.isNegative != rhs.isNegative)
    {
        return {lhs.uintPart + rhs.uintPart, lhs.isNegative};
    }
    else
    {
        if (lhs >= rhs)
        {
            return {lhs.uintPart - rhs.uintPart, lhs.isNegative};
        }
        else
        {
            return {rhs.uintPart - lhs.uintPart, !rhs.isNegative};
        }
    }
}

/**
 * @brief Surcharge de l'opérateur de multiplication pour Sint
 * @param lhs Le premier Sint à multiplier
 * @param rhs Le deuxième Sint à multiplier
 * @return Le résultat de la multiplication
 */
Sint operator*(const Sint &lhs, const Sint &rhs)
{
    return {lhs.uintPart * rhs.uintPart, lhs.isNegative != rhs.isNegative};
}
/**
 * @brief Surcharge de l'opérateur de division pour Sint
 * @param lhs Le Sint à diviser
 * @param rhs Le Sint à diviser
 * @return Le résultat de la division
 */
Sint operator/(const Sint &lhs, const Sint &rhs)
{
    if (rhs == Sint::ZERO)
    {
        throw std::invalid_argument("Erreur: division par zéro.");
    }

    return {lhs.uintPart / rhs.uintPart, lhs.isNegative != rhs.isNegative};
}
/**
 * @brief Normalise le Sint
 */
void Sint::normalize()
{
    if (uintPart == Uint(0))
    {
        isNegative = false; // Zéro est toujours positif
    }
}
