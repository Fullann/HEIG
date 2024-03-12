// Rat.cpp
// Description: Implémentation de la classe Rat pour représenter un nombre rationnel
#include "Rat.hpp"
#include <iomanip>
/**
 * @brief Constructeur par défaut de Rat
 */
Rat::Rat() : numerator(), denominator(1) {}
/**
 * @brief Constructeur de Rat à partir d'un numérateur et d'un dénominateur
 * @param numerator Le numérateur
 * @param denominator Le dénominateur
 */
Rat::Rat(const Sint &numerator, const Sint &denominator) : numerator(numerator), denominator(denominator)
{
    validateDenominator(denominator);
    normalize();
}
/**
 * @brief Constructeur de Rat à partir d'un entier
 * @param integerPart L'entier à convertir en Rat
 */
Rat::Rat(const Sint &integerPart) : numerator(integerPart), denominator(1) {}
/**
 * @brief Surcharge de l'opérateur d'addition composé pour Rat
 * @param rhs Le Rat à additionner
 * @return Le résultat de l'addition
 */
Rat &Rat::operator+=(const Rat &rhs)
{
    numerator = numerator * rhs.denominator + rhs.numerator * denominator;
    denominator *= rhs.denominator;

    normalize();
    return *this;
}
/**
 * @brief Surcharge de l'opérateur de soustraction composé pour Rat
 * @param rhs Le Rat à soustraire
 * @return Le résultat de la soustraction
 */
Rat &Rat::operator-=(const Rat &rhs)
{
    numerator = numerator * rhs.denominator - rhs.numerator * denominator;
    denominator *= rhs.denominator;

    normalize();
    return *this;
}
/**
 * @brief Surcharge de l'opérateur de multiplication composé pour Rat
 * @param rhs Le Rat à multiplier
 * @return Le résultat de la multiplication
 */
Rat &Rat::operator*=(const Rat &rhs)
{
    numerator *= rhs.numerator;
    denominator *= rhs.denominator;

    normalize();
    return *this;
}
/**
 * @brief Surcharge de l'opérateur de division composé pour Rat
 * @param rhs Le Rat à diviser
 * @return Le résultat de la division
 */
Rat &Rat::operator/=(const Rat &rhs)
{
    if (rhs.numerator == Sint::ZERO)
    {
        throw std::invalid_argument("Erreur: division par zéro.");
    }

    numerator *= rhs.denominator;
    denominator *= rhs.numerator;

    normalize();
    return *this;
}
/**
 * @brief Surcharge de l'opérateur de comparaison pour Rat
 * @param rhs Le Rat à comparer
 * @return Le résultat de la comparaison
 */
bool Rat::operator==(const Rat &rhs) const
{
    return numerator == rhs.numerator && denominator == rhs.denominator;
}
/**
 * @brief Surcharge de l'opérateur de comparaison pour Rat
 * @param rhs Le Rat à comparer
 * @return Le résultat de la comparaison
 */
bool Rat::operator!=(const Rat &rhs) const
{
    return !(*this == rhs);
}
/**
 * @brief Surcharge de l'opérateur de comparaison pour Rat
 * @param rhs Le Rat à comparer
 * @return Le résultat de la comparaison
 */
bool Rat::operator<(const Rat &rhs) const
{
    return numerator * rhs.denominator < rhs.numerator * denominator;
}
/**
 * @brief Surcharge de l'opérateur de comparaison pour Rat
 * @param rhs Le Rat à comparer
 * @return Le résultat de la comparaison
 */
bool Rat::operator<=(const Rat &rhs) const
{
    return (*this < rhs) || (*this == rhs);
}
/**
 * @brief Surcharge de l'opérateur de comparaison pour Rat
 * @param rhs Le Rat à comparer
 * @return Le résultat de la comparaison
 */
bool Rat::operator>(const Rat &rhs) const
{
    return !(*this <= rhs);
}
/**
 * @brief Surcharge de l'opérateur de comparaison pour Rat
 * @param rhs Le Rat à comparer
 * @return Le résultat de la comparaison
 */
bool Rat::operator>=(const Rat &rhs) const
{
    return !(*this < rhs);
}
Rat Rat::operator-() const
{
    return { -numerator, denominator };
}
/**
 * @brief Surcharge de l'opérateur d'affichage pour Rat
 * @param os Le flux de sortie
 * @param obj Le Rat à afficher
 * @return Le flux de sortie
 */
std::ostream &operator<<(std::ostream &os, const Rat &obj)
{
    os << obj.numerator;
    if (obj.denominator != 1)
    {
        os << '/' << obj.denominator;
    }
    return os;
}
/**
 * @brief Surcharge de l'opérateur d'entrée pour Rat
 * @param is Le flux d'entrée
 * @param obj Le Rat à remplir
 * @return Le flux d'entrée
 */
std::istream &operator>>(std::istream &is, Rat &obj)
{
    is >> obj.numerator >> obj.denominator;
    return is;
}
/**
 * @brief Surcharge de l'opérateur d'addition pour Rat
 * @param lhs Le Rat de gauche
 * @param rhs Le Rat de droite
 * @return Le résultat de l'addition
 */
Rat operator+(const Rat &lhs, const Rat &rhs)
{
    Rat result = lhs;
    result += rhs;
    return result;
}
/**
 * @brief Surcharge de l'opérateur de soustraction pour Rat
 * @param lhs Le Rat de gauche
 * @param rhs Le Rat de droite
 * @return Le résultat de la soustraction
 */
Rat operator-(const Rat &lhs, const Rat &rhs)
{
    Rat result = lhs;
    result -= rhs;
    return result;
}
/**
 * @brief Surcharge de l'opérateur de multiplication pour Rat
 * @param lhs Le Rat de gauche
 * @param rhs Le Rat de droite
 * @return Le résultat de la multiplication
 */
Rat operator*(const Rat &lhs, const Rat &rhs)
{
    Rat result = lhs;
    result *= rhs;
    return result;
}
/**
 * @brief Surcharge de l'opérateur de division pour Rat
 * @param lhs Le Rat de gauche
 * @param rhs Le Rat de droite
 * @return Le résultat de la division
 */
Rat operator/(const Rat &lhs, const Rat &rhs)
{
    Rat result = lhs;
    result /= rhs;
    return result;
}
/**
 * @brief Normalise le Rat
 */
void Rat::normalize()
{
    if (denominator < Sint::ZERO)
    {
        numerator = -numerator;
        denominator = -denominator;
    }

    // Utilisez la méthode gcd de Sint pour calculer le GCD
    Sint gcdValue = Sint::gcd(numerator, denominator);

    // Divise numerator et denominator par le GCD calculé
    numerator /= gcdValue;
    denominator /= gcdValue;
}
/**
 * @brief Valide le dénominateur
 * @param denominator Le dénominateur à valider
 */
void Rat::validateDenominator(const Sint &denominator)
{
    if (denominator == Sint::ZERO)
    {
        throw std::invalid_argument("Erreur: dénominateur ne peut pas être nul.");
    }
}
