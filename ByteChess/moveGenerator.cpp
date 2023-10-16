#include "ChessBoard.h"
#include "DepthGen.h"

extern DepthGen myGen;
/*
* Here it generates all the legal moves the position can have
* Once everything is generated it will be passed to a make move function
* And once a move is made, it will create a new ChessBoard object and then again
* it will create a new one to make a depth of X.
* After a certain depth is reached, the data will be collected to show what is the best move for this position
*/


void ChessBoard::generateMoves(bool turn) {

	for (uint8_t row = 0; row < 8; row++) {
		for (uint8_t col = 0; col < 8; col++) {
			char curpiece = chessboard[row][col];
			if (curpiece != ' ' && !(myUpper(curpiece) ^ turn)) {
				switch (toupper(curpiece)) {
				case 'P':
					generateMovesPawn(row, col, turn);
					break;
				case 'N':
					generateMovesKnight(row, col, turn);
					break;
				case 'R':
					generateMovesRook(row, col, turn);
					break;
				case 'B':
					generateMovesBishop(row, col, turn);
					break;
					// Add more cases for other piece types if needed
				case 'Q':
					generateMovesRook(row, col, turn);
					generateMovesBishop(row, col, turn);
					break;
				case 'K':
					generateMovesKing(row, col, turn);
					break;
				default:
					break;

				}
			}
		}
	}
}



//--------PAWN--------//
void ChessBoard::generateMovesPawn(short row, short col, bool curPiece) {
	short color = (!curPiece) ? -1 : 1;  // -1 for black, 1 for white
	short newRow = row + color;

	if (newRow >= 0 && newRow <= 7) {
		// Move one square forward if the path is clear
		if (chessboard[newRow][col] == ' ') {
			movePiece(row, col, newRow, col);

			// Special case: Moving two squares forward from the starting position
			if ((row == 1 && color == 1) || (row == 6 && color == -1)) {
				short doubleRow = newRow + color;
				if (chessboard[doubleRow][col] == ' ') {
					movePiece(row, col, doubleRow, col);
				}
			}
		}

		// Check left and right for possible captures
		short leftCol = col - 1;
		short rightCol = col + 1;

		if (leftCol >= 0) {
			char leftPiece = chessboard[newRow][leftCol];
			if (leftPiece != ' ' && !sameColor(curPiece, leftPiece)) {
				movePiece(row, col, leftCol, newRow);
			}
		}

		if (rightCol <= 7) {
			char rightPiece = chessboard[newRow][rightCol];
			if (rightPiece != ' ' && !sameColor(curPiece, rightPiece)) {
				movePiece(row, col, rightCol, newRow);
			}
		}
	}
}




//--------KNIGHT--------//
void ChessBoard::generateMovesKnight(short row, short col, bool turn) {
	// Possible knight move offsets
	const short dx[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
	const short dy[] = { 1, -1, 1, -1, 2, -2, 2, -2 };

	for (short i = 0; i < 8; ++i) {
		short newRow = row + dx[i];
		short newCol = col + dy[i];

		// Check if the new position is within the chessboard
		if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
			// Check if the move is valid according to your game logic (e.g., not attacking your own pieces)
			if (!sameColor(turn, chessboard[newRow][newCol]) || chessboard[newRow][newCol] == 0) {
				movePiece(row, col, newRow, newCol);
			}
		}
	}
}


//--------THE ROOK--------//
void ChessBoard::generateMovesRook(short row, short col, bool turn) {
	// Horizontal right movement
	for (short newCol = col + 1; newCol < 8; newCol++) {
		if (!RookMovement(row, col, row, newCol, turn)) {
			break;
		}
	}

	// Horizontal left movement
	for (short newCol = col - 1; newCol >= 0; newCol--) {
		if (!RookMovement(row, col, row, newCol, turn)) {
			break;
		}
	}

	// Vertical up movement
	for (short newRow = row + 1; newRow < 8; newRow++) {
		if (!RookMovement(row, col, newRow, col, turn)) {
			break;
		}
	}

	// Vertical down movement
	for (short newRow = row - 1; newRow >= 0; newRow--) {
		if (!RookMovement(row, col, newRow, col, turn)) {
			break;
		}
	}
}

bool ChessBoard::RookMovement(short initRow, short initCol, short row, short col, bool turn) {
	if (chessboard[row][col] == ' ') {
		movePiece(initRow, initCol, row, col);
		return true;
	}
	else if (!sameColor(turn, chessboard[row][col])) {
		movePiece(initRow, initCol, row, col);
	}
	return false;
}



//--------BISHOP--------//
void ChessBoard::generateMovesBishop(short row, short col, bool turn) {
	static const short directions[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

	for (int dir = 0; dir < 4; dir++) {
		for (int step = 1; step < 8; step++) {
			short newRow = row + step * directions[dir][0];
			short newCol = col + step * directions[dir][1];

			if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8) {
				// Out of the board bounds
				break;
			}

			char targetPiece = chessboard[newRow][newCol];
			if (targetPiece == ' ') {
				movePiece(row, col, newRow, newCol);
			}
			else {
				if (!sameColor(turn, targetPiece)) {
					movePiece(row, col, newRow, newCol);
				}
				break;  // Stop moving in this direction after capturing or blocking
			}
		}
	}
}

//--------KING--------//
void ChessBoard::generateMovesKing(short row, short col, bool turn) {
	static const short directions[8][2] = {
		{-1, -1}, {-1, 0}, {-1, 1},	{0, -1},{0, 1},{1, -1}, {1, 0}, {1, 1}
	};

	for (int dir = 0; dir < 8; dir++) {
		short newRow = row + directions[dir][0];
		short newCol = col + directions[dir][1];

		if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
			char targetPiece = chessboard[newRow][newCol];
			if (targetPiece == ' ' || !sameColor(turn, targetPiece)) {
				movePiece(row, col, newRow, newCol);
			}
		}
	}
}


void ChessBoard::movePiece(short row, short col, short newRow, short newCol) {
	char curPiece = this->chessboard[row][col];
	char newChessboard[8][8];

	memcpy(newChessboard, this->chessboard, 64);


	// Make the move by updating the newChessboard
	newChessboard[row][col] = ' ';
	newChessboard[newRow][newCol] = curPiece;

	// Check duplicates logic

	myGen.positions.push_back(ChessBoard(newChessboard, this));

	return;
}
