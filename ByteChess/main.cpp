#include <vector>
#include <iostream>
#include "ChessBoard.h"
#include <chrono>

std::vector<ChessBoard> generatePositionsToDepth(const ChessBoard& initialBoard, int depth) {
    std::vector<std::vector<ChessBoard>> positions(depth + 1);
    positions[0].push_back(initialBoard);

    for (int d = 1; d <= depth; d++) {
        for (const ChessBoard& board : positions[d - 1]) {
            ChessBoard boardCopy = board;
            boardCopy.generateMoves();
            std::vector<ChessBoard> newPositions = boardCopy.getPositions();
            positions[d].insert(positions[d].end(), newPositions.begin(), newPositions.end());
        }
    }

    return positions[depth];
}

int main() {
    std::cout << "Hello there!" << '\n';
    // Create an initial chessboard
    ChessBoard initialBoard;

    // Specify the depth
    int depth = 6;

    // Start the timer
    auto start_time = std::chrono::high_resolution_clock::now();

    // Generate positions
    std::vector<ChessBoard> positions = generatePositionsToDepth(initialBoard, depth);

    // Stop the timer
    auto end_time = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // Output the duration
    std::cout << "Time taken to generate positions: " << duration.count() << " milliseconds" << std::endl;

    // Continue with the rest of your code using the 'positions' vector

    return 0;
}