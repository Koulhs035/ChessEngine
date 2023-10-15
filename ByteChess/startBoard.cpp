#include "ChessBoard.h"


/*
*  The board is initialized here.
*  The pieces are represented by a Char of 1 byte to make memory usage as little as possible
*  Naturally the board is displayed by White's side
*  Upper case letters are used for white, lower case for black
*/


//--------------------------------------Constructors--------------------------------------//

// Starting position constructor
ChessBoard::ChessBoard() : previousPosition(nullptr) {
	// Here is the starting position of the board
	for (short row = 2; row < 6; row++) {
		for (short col = 0; col < 8; col++) {
			this->chessboard[row][col] = ' ';
		}
	}



	//Pawn placement
	for (short col = 0; col < 8; col++) {
		chessboard[1][col] = 'P'; //White pawn
		chessboard[6][col] = 'p'; //Black pawn
	}


	placePiece('R', 0);
	placePiece('N', 1);
	placePiece('B', 2);

	chessboard[0][3] = 'Q';
	chessboard[7][3] = 'q';

	chessboard[0][4] = 'K';
	chessboard[7][4] = 'k';
}

ChessBoard::ChessBoard(char initialChessboard[8][8], ChessBoard* previousPosition) {
	// Initialize the previousPosition
	this->previousPosition = previousPosition;

	memcpy(this->chessboard, initialChessboard, 64);
}


void ChessBoard::placePiece(char piece, short col) {
	char blackPiece = tolower(piece);
	chessboard[0][col] = piece;
	chessboard[0][7 - col] = piece;

	chessboard[7][7 - col] = blackPiece;
	chessboard[7][col] = blackPiece;
}



