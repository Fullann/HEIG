#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nombres;
    int nombre;

    cout << "Entrez une suite de nombres entiers (terminer avec un caractère non numérique):" << endl;

    while (cin >> nombre) {
        nombres.push_back(nombre);
    }

    if (!nombres.empty()) {
        int minimum = nombres[0];
        int maximum = nombres[0];
        int occurrenceMinimum = 0;
        int occurrenceMaximum = 0;

        for (int i = 0; i < nombres.size(); i++) {
            if (nombres[i] < minimum) {
                minimum = nombres[i];
                occurrenceMinimum = 1;
            } else if (nombres[i] == minimum) {
                occurrenceMinimum++;
            }

            if (nombres[i] > maximum) {
                maximum = nombres[i];
                occurrenceMaximum = 1;
            } else if (nombres[i] == maximum) {
                occurrenceMaximum++;
            }
        }

        cout << "Minimum: " << minimum << ", occurrences: " << occurrenceMinimum << endl;
        cout << "Maximum: " << maximum << ", occurrences: " << occurrenceMaximum << endl;
    }

    return 0;
}