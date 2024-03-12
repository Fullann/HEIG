// Uint.cpp
// Classe Uint pour représenter un nombre entier non signé de taille arbitraire
#include "Uint.hpp"
#include <iostream>

// Constructeur par défaut
Uint::Uint() : data("0"), base(DEFAULT_BASE) {}

/**
 * @brief Constructeur de Uint à partir d'un uint64_t
 * @param value L'entier à convertir en Uint
 * @param base La base de la chaîne de caractères
 */
Uint::Uint(uint64_t value) : base(DEFAULT_BASE)
{
    if (value == 0)
    {
        data = "0";
        return;
    }

    while (value > 0)
    {
        size_t digit = value % base;
        data = digitToChar(static_cast<int>(digit)) + data;
        value /= base;
    }
}
/**
 * @brief Constructeur de Uint à partir d'une chaîne de caractères
 * @param str La chaîne de caractères à convertir en Uint
 * @param base La base de la chaîne de caractères
 */
std::pair<Uint, Uint> Uint::divide(const Uint &divisor) const
{
    validateDivision(divisor);

    Uint quotient;
    Uint remainder = *this;

    while (remainder.compare(divisor) >= 0)
    {
        Uint temp = divisor;
        Uint multiple = Uint(1);

        while (remainder.compare(temp * Uint(2)) >= 0)
        {
            temp *= Uint(2);
            multiple *= Uint(2);
        }

        remainder -= temp;
        quotient += multiple;
    }

    return {quotient, remainder};
}
/**
 * @brief Surcharge de l'opérateur d'addition composé pour Uint
 * @param rhs Le Uint à additionner
 * @return Le résultat de l'addition
 */
Uint &Uint::operator+=(const Uint &rhs)
{
    int carry = 0;

    // Assurer que les deux nombres ont la même longueur
    while (data.length() < rhs.data.length())
    {
        data = "0" + data;
    }
    // Assurer que les deux nombres ont la même longueur
    for (size_t i = data.length() - 1; i > 0; --i)
    {
        int sum = charToDigit(data[i]) + charToDigit(rhs.data[i]) + carry;
        carry = sum / base;
        data[i] = digitToChar(sum % base);
    }

    // S'il reste une retenue, l'ajouter comme nouveau chiffre le plus significatif
    if (carry > 0)
    {
        data = digitToChar(carry) + data;
    }

    return *this;
}
/**
 * @brief Surcharge de l'opérateur de soustraction composé pour Uint
 * @param rhs Le Uint à soustraire
 * @return Le résultat de la soustraction
 */
Uint &Uint::operator-=(const Uint &rhs)
{
    if (*this < rhs)
    {
        throw std::invalid_argument("Erreur: la soustraction donne un résultat négatif.");
    }

    int borrow = 0;
    // Assurer que les deux nombres ont la même longueur
    for (size_t i = data.length() - 1; i > 0; --i)
    {
        int diff = charToDigit(data[i]) - charToDigit(rhs.data[i]) - borrow;
        if (diff < 0)
        {
            diff += base;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        data[i] = digitToChar(diff);
    }

    removeLeadingZeros();

    return *this;
}
/**
 * @brief Surcharge de l'opérateur de multiplication composé pour Uint
 * @param rhs Le Uint à multiplier
 * @return Le résultat de la multiplication
 */
Uint &Uint::operator*=(const Uint &rhs)
{
    // Copie de l'objet courant
    Uint temp = *this;

    // Initialisation à zéro (0)
    *this = Uint(0);

    // Copie de rhs pour la décrémenter
    Uint decrementedRhs = rhs;

    // Effectuer la multiplication en utilisant l'addition
    while (!decrementedRhs.isEqual(Uint(0)))
    {
        *this += temp;
        decrementedRhs -= Uint(1);
    }

    return *this;
}
/**
 * @brief Surcharge de l'opérateur de division composé pour Uint
 * @param rhs Le Uint à diviser
 * @return Le résultat de la division
 */
Uint &Uint::operator/=(const Uint &rhs)
{
    validateDivision(rhs);

    Uint quotient;
    Uint remainder = *this;

    while (remainder.compare(rhs) >= 0)
    {
        Uint temp = rhs;
        Uint multiple = Uint(1);

        while (remainder.compare(temp * Uint(2)) >= 0)
        {
            temp *= Uint(2);
            multiple *= Uint(2);
        }

        remainder -= temp;
        quotient += multiple;
    }

    *this = quotient;
    return *this;
}
/**
 * @brief Surcharge de l'opérateur de modulo composé pour Uint
 * @param rhs Le Uint à diviser
 * @return Le résultat du modulo
 */
int Uint::compare(const Uint &other) const
{
    // Comparaison basée sur la longueur des chaînes
    if (data.length() < other.data.length())
    {
        return -1;
    }
    else if (data.length() > other.data.length())
    {
        return 1;
    }

    // Comparaison caractère par caractère
    for (size_t i = 0; i < data.length(); ++i)
    {
        if (data[i] < other.data[i])
        {
            return -1;
        }
        else if (data[i] > other.data[i])
        {
            return 1;
        }
    }

    // Les nombres sont égaux
    return 0;
}
/**
 * @brief Surcharge de l'opérateur d'égalité pour Uint
 * @param rhs Le Uint à comparer
 * @return Le résultat de la comparaison
 */
bool Uint::isEqual(const Uint &other) const
{
    return compare(other) == 0;
}
/**
 * @brief Surcharge de l'opérateur d'affichage pour Uint
 * @return La chaîne de caractères représentant le Uint
 */
std::string Uint::toString() const
{
    return data;
}

/**
 * @brief Surcharge de l'opérateur d'affichage pour Uint
 * @param os Le flux de sortie
 * @param obj Le Uint à afficher
 * @return Le flux de sortie
 */
std::ostream &operator<<(std::ostream &os, const Uint &obj)
{
    os << obj.toString();
    return os;
}
/**
 * @brief Surcharge de l'opérateur d'entrée pour Uint
 * @param is Le flux d'entrée
 * @param obj Le Uint à modifier
 * @return Le flux d'entrée
 */
std::istream &operator>>(std::istream &is, Uint &obj)
{
     uint64_t inputValue;
    is >> inputValue;
    obj = Uint(inputValue);
    return is;
}
/**
 * @brief Methoe pour valider la base
 */
void Uint::validateBase() const
{
    if (base < 2 || base > 36)
    {
        throw std::invalid_argument("Erreur: base d'affichage invalide.");
    }
}

/**
 * @brief Methode pour valider que le nombre est positif
 */
void Uint::validateNonNegative() const
{
    if (compare(Uint(0)) < 0)
    {
        throw std::invalid_argument("Erreur: opération impossible sur un nombre négatif.");
    }
}

/**
 * @brief Methode pour valider la division
 * @param divisor Le Uint à diviser
 */
static void validateDivision(const Uint &divisor)
{
    if (divisor.isEqual(Uint(0)))
    {
        throw std::invalid_argument("Erreur: division par zéro.");
    }
}

/**
 * @brief Methode pour enlever les zéros inutiles
 */
void Uint::removeLeadingZeros()
{
    size_t pos = data.find_first_not_of('0');
    if (pos != std::string::npos)
    {
        data = data.substr(pos);
    }
    else
    {
        data = "0";
    }
}

/**
 * @brief Methode pour convertir un chiffre en caractère
 * @param digit Le chiffre à convertir
 * @return Le caractère correspondant
 */
char Uint::digitToChar(int digit) const
{
    if (digit < 0 || digit >= base)
    {
        throw std::out_of_range("Erreur: chiffre invalide lors de la conversion en caractère.");
    }

    if (digit < 10)
    {
        return static_cast<char>('0' + digit);
    }
    else
    {
        return static_cast<char>('A' + (digit - 10));
    }
}
/**
 * @brief Methode pour convertir un caractère en chiffre
 * @param c Le caractère à convertir
 * @return Le chiffre correspondant
 */
int Uint::charToDigit(char c)
{
    if ('0' <= c && c <= '9')
    {
        return c - '0';
    }
    else if ('A' <= c && c <= 'Z')
    {
        return c - 'A' + 10;
    }
    else
    {
        throw std::invalid_argument("Erreur: caractère invalide lors de la conversion en chiffre.");
    }
}

