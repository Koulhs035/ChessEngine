#include <thread>
#include <chrono>
#include "Chessboard.h"

//--------------------------------------Generic tools for the chessboard--------------------------------------//

void ChessBoard::printBoard() {
	for (short row = 7; row >= 0; row--) {
		for (short col = 0; col < 8; col++) {
			std::cout << "|" << chessboard[row][col] << "|";
		}
		std::cout << '\n';
	}
	std::cout << '\n' << '\n';
	std::this_thread::sleep_for(std::chrono::milliseconds(150));

}


char ChessBoard::numberToLetter(short number) {
	if (number >= 0 && number <= 7) {
		return 'a' + number;
	}
	else {
		// Out of range input
		return '0';
	}
}

bool ChessBoard::sameColor(char piece1, char piece2) {
	return (!(isupper(piece1) ^ isupper(piece2)));
}



std::vector<ChessBoard> ChessBoard::getPositions() {
	return positions;
}


