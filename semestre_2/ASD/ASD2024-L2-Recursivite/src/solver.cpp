#include "solver.h"
#include "pieces.h"
#include "iostream"

using namespace std;

static unsigned int counter_call;

/**
 * Function to check if the piece is compatible with the current solution of the puzzle
 * @param puzzle The current solution of the puzzle
 * @param piece The piece to be placed
 * @return True if the piece is compatible with the current solution of the puzzle, false otherwise
 */
bool isCompatible(const vector<PieceData> &puzzle, const PieceData &piece)
{
    const size_t currentPosition = puzzle.size();

    // Check if the piece contains an inverse sprinkler and if its position is valid
    if (piece.ReversePuzzle() && !checkPositionReverseSprinkler(piece, currentPosition))
    {
        return false;
    }
    // If the puzzle is empty, any piece can be placed
    if (puzzle.empty())
    {
        return true;
    }
    // If the current position is less than 3, check compatibility with the piece on its left
    if (currentPosition < 3)
    {
        return comparePieces(piece, Direction::LEFT, puzzle[currentPosition - 1], Direction::RIGHT);
    }
    // If the current position is not at the leftmost column and the piece category is not compatible
    if (currentPosition % 3 < 2 &&
        comparePieceCategories(piece, Direction::RIGHT, puzzle[currentPosition - 2], Direction::DOWN))
    {
        return false;
    }
    // If the current position is at the leftmost column, check compatibility with the piece above
    if (currentPosition % 3 == 0)
    {
        return comparePieces(piece, Direction::UP, puzzle[currentPosition - 3], Direction::DOWN);
    }

    // Check compatibility with both the piece above and the piece on the left
    return comparePieces(piece, Direction::UP, puzzle[currentPosition - 3], Direction::DOWN) && comparePieces(piece, Direction::LEFT, puzzle[currentPosition - 1], Direction::RIGHT);
}

/**
 * Function to solve the puzzle
 * @param availablePieces The pieces available to solve the puzzle
 * @param currentSolution The current solution of the puzzle
 * @param solutions The list of solutions to the puzzle
 * @return The list of solutions to the puzzle
 */
void solver(const Puzzle &availablePieces, Puzzle &currentSolution, vector<Puzzle> &solutions) {
    // Increment the number of calls
    ++counter_call;
    // If the current solution is complete, add it to the list of solutions
    if (currentSolution.size() == PIECES.size()) {
        solutions.push_back(currentSolution);
        return;
    }
    // Create a copy of the available pieces
    Puzzle nextAvailablePieces = availablePieces;
    // Iterate through the available pieces
    for (size_t i = 0; i < availablePieces.size(); ++i) {
        // Get the next piece to be placed
        PieceData piece = availablePieces[i];
        // Try all possible rotations of the piece
        for (char rotation = 'a'; rotation <= 'd'; ++rotation) {
            piece.rotate(rotation);
            // Check if the piece is compatible with the current solution of the puzzle
            if (isCompatible(currentSolution, piece)) {
                // Add the piece to the current solution and remove it from the available pieces
                currentSolution.push_back(piece);
                piece.remove(nextAvailablePieces);
                // Recursively call the solver function with the updated available pieces and current solution
                solver(nextAvailablePieces, currentSolution, solutions);
                // Remove the piece from the current solution and add it back to the available pieces
                currentSolution.pop_back();
                nextAvailablePieces.push_back(piece);
            }
        }
    }
}


/**
 * Function to solve the puzzle
 * @param referencePuzzle The reference puzzle to solve
 * @return The list of solutions to the puzzle
 */
vector<Puzzle> solve(const Puzzle &referencePuzzle)
{
    vector<Puzzle> solutions;
    Puzzle currentSolution;
    counter_call = 0;
    solver(referencePuzzle, currentSolution, solutions);
    cout << "Nombre d'appel : " << counter_call << endl;
    return solutions;
}

/**
 * Function to compare two puzzle pieces based on their attachment types
 * @param newPiece The new puzzle piece to be placed
 * @param newPieceSide The side of the new puzzle piece
 * @param placedPiece The puzzle piece already placed
 * @param placedPieceSide The side of the placed puzzle piece
 * @return True if the pieces are compatible, false otherwise
 */
bool comparePieces(const PieceData &newPiece, Direction newPieceSide, const PieceData &placedPiece, Direction placedPieceSide)
{
    // Check if the attachment types of the two pieces are compatible
    const AttachementType testAttachment = newPiece.getPuzzleSide(newPieceSide);
    const AttachementType placedAttachment = placedPiece.getPuzzleSide(placedPieceSide);
    for (const auto &pair : MATCHING_TYPES)
    {
        // If the attachment types are compatible, return true
        if ((pair.first == testAttachment && pair.second == placedAttachment)
            || (pair.second == testAttachment && pair.first == placedAttachment))
        {
            return true;
        }
    }
    return false;
}


/**
 * Function to compare the categories of two puzzle pieces based on their attachment types
 * @param newPiece The new puzzle piece to be placed
 * @param newPieceSide The side of the new puzzle piece
 * @param placedPiece The puzzle piece already placed
 * @param placedPieceSide The side of the placed puzzle piece
 * @return True if the pieces are compatible, false otherwise
 */
bool comparePieceCategories(const PieceData &newPiece, Direction newPieceSide, const PieceData &placedPiece, Direction placedPieceSide)
{
    const AttachementType testAttachment = newPiece.getPuzzleSide(newPieceSide);
    const AttachementType placedAttachment = placedPiece.getPuzzleSide(placedPieceSide);
    for (const auto &pair : MATCHING_TYPES)
    {
        // If the attachment types are compatible, return true
        if ((pair.first == testAttachment && pair.second == placedAttachment)
            || (pair.second == testAttachment && pair.first == placedAttachment)
            || (pair.first == testAttachment && pair.first == placedAttachment)
            || (pair.second == testAttachment && pair.second == placedAttachment))
        {
            return true;
        }
    }
    return false;
}

/**
 * Function to check if the position of the reverse sprinkler is valid
 * @param piece The piece to be placed
 * @param puzzlePosition The position of the piece in the puzzle
 * @return True if the position of the reverse sprinkler is valid, false otherwise
 */
bool checkPositionReverseSprinkler(const PieceData &piece, size_t puzzlePosition)
{
    if (!piece.ReversePuzzle())
    {
        return true;
    }
    // Check if the position of the reverse sprinkler is valid based on its attachment type
    switch (piece.findAttachementType(ARROSOIR_INVERSE))
    {
    case Direction::UP: // first line
        return puzzlePosition <= 2;
    case Direction::RIGHT: // last column
        return puzzlePosition % 3 == 2;
    case Direction::DOWN: // last line
        return puzzlePosition >= 6;
    case Direction::LEFT: // first column
        return puzzlePosition % 3 == 0;
    default:
        return false;
    }
}
