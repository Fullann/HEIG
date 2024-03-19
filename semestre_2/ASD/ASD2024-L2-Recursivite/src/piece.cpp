#include "piece.h"
#include <vector>

using namespace std;

// Operator overloading for checking equality of PieceData objects
bool PieceData::operator==(const PieceData &rhs) const
{
    return pieceData == rhs.pieceData && puzzleRotation == rhs.puzzleRotation && puzzleIndex == rhs.puzzleIndex;
}

// Operator overloading for outputting PieceData objects
ostream &operator<<(ostream &os, const PieceData &rhs)
{
    os << rhs.puzzleIndex << rhs.puzzleRotation;
    return os;
}

/**
 * Function to rotate the puzzle piece
 * @param rotation The rotation to be performed on the puzzle piece
 */
void PieceData::rotate(char rotation)
{
    // Check if the rotation input is valid
    if (rotation < 'a' || rotation > 'd')
    {
        return;
    }
    // Rotate clockwise if needed
    if (puzzleRotation < rotation)
    {
        rotateTimes(getRotationAmount(rotation) - getPuzzleRotationAmount());
        return;
    }
    // Rotate counter-clockwise otherwise
    rotateTimes((pieceData.size() - getPuzzleRotationAmount() + getRotationAmount(rotation)) % pieceData.size());
}

/**
 * Method to remove the puzzle piece from the puzzle
 * @param puzzle The puzzle from which the piece is to be removed
 * @return The puzzle with the piece removed
 */
void PieceData::remove(Puzzle &puzzle) const {
    // Iterate through the puzzle
    for (auto it = puzzle.begin(); it != puzzle.end(); ++it) {
        // If the puzzle piece is found, remove it from the puzzle
        if (it->puzzleIndex == this->puzzleIndex) {
            puzzle.erase(it);
            break;
        }
    }
}


/**
 * Static method to generate a puzzle
 * @return The generated puzzle
 */
Puzzle PieceData::generate()
{
    Puzzle pieces;
    for (const auto &piece : PIECES)
    {
        // Add the puzzle piece to the puzzle
        pieces.emplace_back(piece, pieces.size() + 1);
    }
    return pieces;
}

/**
 * Method to rotate the puzzle piece a certain number of times
 * @param rotations The number of rotations to be performed on the puzzle piece
 */
void PieceData::rotateTimes(size_t rotations)
{
    const size_t sidesSize = pieceData.size();
    Piece result;
    // Perform rotations on the puzzle piece
    for (size_t i = rotations % sidesSize, j = 0; j < sidesSize; ++i, ++j)
    {
        result[j] = pieceData[i % sidesSize];
    }
    pieceData = result;
    // Update puzzle rotation based on the number of rotations
    puzzleRotation = char('a' + ((getPuzzleRotationAmount() + rotations) % sidesSize));
}

/**
 * Method to find the attachment type in a puzzle piece
 * @param attachementType The attachment type to be found in the puzzle piece
 * @return The direction of the attachment type in the puzzle piece
 */
Direction PieceData::findAttachementType(AttachementType attachementType) const
{
    auto pieceIt = find(pieceData.begin(), pieceData.end(), attachementType);
    // If attachment type is not found, return NONE
    if (pieceIt == pieceData.end())
    {
        return Direction::NONE;
    }
    // Otherwise, return the direction of attachment type in the piece
    return Direction(distance(pieceData.begin(), pieceIt));
}
