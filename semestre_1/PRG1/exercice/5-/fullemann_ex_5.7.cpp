/**
 * Laboratoire sur l'exercice 5.7
 * Author : Nathan Füllemann
 * Date : 30.10.2023
 * Updated on :
 *
 * Name:   Somme de deux nombres binaires
 * Desc :  Ce programme calcule la somme de deux nombres binaires
 */

#include <iostream>
#include <string>
using namespace std;

string operator+(const string &lhs, const string &rhs)
{
    int carry = 0;
    string result;

    size_t i = 0;
    while (i < lhs.size() || i < rhs.size() || carry)
    {
        int digit1 = (i < lhs.size()) ? (lhs[i] - '0') : 0;
        int digit2 = (i < rhs.size()) ? (rhs[i] - '0') : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 2;
        int bit = sum % 2;

        result.insert(result.begin(), '0' + bit);
        i++;
    }

    return result;
}

int main()
{
    string binary1 = "1101";
    string binary2 = "1010";

    string sum = binary1 + binary2;

    cout << "Somme en binaire inversé : " << sum << endl;

    return 0;
}
