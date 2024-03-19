#include <iostream>
#include <vector>
#include "piece.h"
#include "solver.h"

using namespace std;

int main() {
    // Solve the puzzle and store the solutions
    vector<Puzzle> solutions = solve(PieceData::generate());

    // Display the solutions
    cout << "Toutes les solutions : \n";
    for (const auto &solution: solutions) {
        for (const PieceData &piece: solution) {
            cout << piece << " ";
        }
        cout << endl;
    }
    return 0;
}
