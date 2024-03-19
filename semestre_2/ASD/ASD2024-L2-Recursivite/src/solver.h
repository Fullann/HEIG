#ifndef SOLVER_H
#define SOLVER_H

#include "piece.h"
#include <vector>

using namespace std;
// Function declaration for solving the puzzle
vector<Puzzle> solve(const vector<PieceData> &referencePuzzle);

// Array holding matching attachment types
constexpr array<pair<AttachementType, AttachementType>, 4> MATCHING_TYPES = {
        make_pair(FILLE_HAUT, FILLE_BAS),
        make_pair(DAME_HAUT, DAME_BAS),
        make_pair(ARROSOIR_GAUCHE, ARROSOIR_DROIT),
        make_pair(GATEAU_GAUCHE, GATEAU_DROIT),
};

// Function to check if the position is valid for the inverse sprinkler attachment type
bool checkPositionReverseSprinkler(const PieceData &piece, size_t puzzlePosition);

// Function to compare two puzzle pieces based on their attachment types
bool comparePieces(const PieceData &newPiece,Direction newPieceSide,const PieceData &placedPiece,Direction placedPieceSide);

// Function to compare two puzzle pieces based on their attachment type categories
bool comparePieceCategories(const PieceData &newPiece,Direction newPieceSide,const PieceData &placedPiece,Direction placedPieceSide);

#endif // SOLVER_H
