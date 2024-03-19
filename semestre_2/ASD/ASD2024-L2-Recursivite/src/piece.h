#ifndef PieceData_H
#define PieceData_H

#include "pieces.h"
#include <array>
#include <ostream>
#include <vector>
#include <algorithm>

// Enumeration for directions
enum class Direction
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
    NONE = -1
};

// Forward declaration of PieceData class
class PieceData;

// Alias for puzzle vector
using Puzzle = std::vector<PieceData>;

// Class representing a puzzle piece
class PieceData
{

private:
    Piece pieceData;
    unsigned puzzleIndex;
    char puzzleRotation;
    bool hasReverseSprinkler;

public:
    // Constructor
    explicit PieceData(
        const Piece &sourcePiece, unsigned index, char rotation = 'a') : pieceData(sourcePiece),
                                                                         puzzleIndex(index),
                                                                         puzzleRotation(rotation)
    {

        hasReverseSprinkler = std::any_of(sourcePiece.begin(), sourcePiece.end(),
                                       [](auto &piece)
                                       { return piece == ARROSOIR_INVERSE; });
    }

    // Operator overloading for checking equality of PieceData objects
    bool operator==(const PieceData &rhs) const;
    inline bool operator!=(const PieceData &rhs) const { return !(rhs == *this); }

    // Static method to generate a puzzle
    static Puzzle generate();
     // Method to remove the puzzle piece from the puzzle
    void remove(Puzzle &puzzle) const;

    // Method to rotate the puzzle piece a certain number of times
    void rotateTimes(size_t rotations);

    // Method to rotate the puzzle piece
    void rotate(char rotation);

    // Static method to get rotation amount
    static unsigned getRotationAmount(char rotation) { return (unsigned)(rotation - 'a'); }

    // Method to get rotation amount of the puzzle piece
    unsigned getPuzzleRotationAmount() const { return getRotationAmount(puzzleRotation); }

    // Method to get attachment type of the puzzle piece based on direction
    AttachementType getPuzzleSide(Direction side = Direction::UP) const { return pieceData.at(unsigned(side)); }

    // Method to check if the piece contains an inverse sprinkler
    bool ReversePuzzle() const { return hasReverseSprinkler; };

    // Method to find the attachment type in a puzzle piece
    Direction findAttachementType(AttachementType attachementType) const;

    // Friend function for outputting PieceData objects
    friend std::ostream &operator<<(std::ostream &os, const PieceData &rhs);
};

#endif // PieceData_H
