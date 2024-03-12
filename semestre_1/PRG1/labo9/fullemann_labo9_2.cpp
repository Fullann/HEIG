/**
 * Laboratoire 9.2
 * Author : Nathan Füllemann
 * Date : 09.10.2023
 *
 * Name:   Jeux des 3 portes aléatoires
 * Desc :   Ce programme simule le jeu des 3 portes aléatoires avec différentes tactiques
 */
#include <iostream>
#include <random>
using namespace std;

// Fonction pour effectuer une simulation avec une tactique donnée
bool simulateGame(int tactic)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 3); // Porte avec le prix

    int prizeDoor = dist(gen); // La porte avec le prix est choisie aléatoirement

    int initialChoice = 0;
    int revealedDoor = 0;

    // Le joueur choisit sa porte initiale en fonction de la tactique
    if (tactic == 1 || tactic == 3)
    {
        initialChoice = 1;
    }
    else if (tactic == 2 || tactic == 4)
    {
        initialChoice = dist(gen);
    }
    else if (tactic == 5)
    {
        initialChoice = dist(gen);
        revealedDoor = dist(gen);
    }

    // Le présentateur révèle une porte
    do
    {
        revealedDoor = dist(gen);
    } while (revealedDoor == initialChoice || revealedDoor == prizeDoor);

    // Le joueur peut choisir de changer de porte en fonction de la tactique
    if (tactic == 3 || tactic == 4)
    {
        // Changer de porte
        initialChoice = 6 - initialChoice - revealedDoor;
    }
    else if (tactic == 5)
    {
        // Changer de porte avec une probabilité de 50%
        uniform_real_distribution<double> coinFlip(0.0, 1.0);
        if (coinFlip(gen) < 0.5)
        {
            initialChoice = 6 - initialChoice - revealedDoor;
        }
    }

    // Vérifier si le joueur a gagné
    return initialChoice == prizeDoor;
}

int main()
{
    int tactic, numSimulations;
    int successCount = 0;

    cout << "Choisissez la tactique (1-5) :\n";
    cout << "1. Choisir toujours la première porte\n";
    cout << "2. Choisir une porte au hasard\n";
    cout << "3. Choisir toujours la première porte et ouvrir une autre porte\n";
    cout << "4. Choisir une porte au hasard et ouvrir une autre porte\n";
    cout << "5. Choisir la première porte au hasard et tirer à pile ou face\n";
    cin >> tactic;

    cout << "Entrez le nombre de simulations : ";
    cin >> numSimulations;

    for (int i = 0; i < numSimulations; ++i)
    {
        if (simulateGame(tactic))
        {
            successCount++;
        }
    }

    double successRate = static_cast<double>(successCount) / static_cast<double>(numSimulations) * 100.0;

    cout << "Taux de succès : " << successRate << "%" << endl;

    return 0;
}
