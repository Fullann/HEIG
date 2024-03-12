/**
 * Laboratoire sur l'exercice 5.6
 * Author : Nathan Füllemann
 * Date : 30.10.2023
 * Updated on :
 *
 * Name:   Conversion d'un nombre entier en binaire
 * Desc :  Ce programme convertit un nombre entier en binaire
 */
#include <iostream>
using namespace std;
string decimalToBinary(size_t number) {
    if (number == 0) {
        return "0";
    }

    string binaryRepresentation = "";
    while (number > 0) {
        int bit = number % 2;
        binaryRepresentation = to_string(bit) + binaryRepresentation;
        number /= 2;
    }

    return binaryRepresentation;
}

int main() {
    size_t number ;
    cout << "Entrez le nombre à convertir : ";
    cin >> number;
    string binaryString = decimalToBinary(number);
    cout << "La représentation binaire de " << number << " est : " << binaryString << endl;
    return 0;
}
