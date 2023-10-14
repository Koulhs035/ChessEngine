#include "ChessBoard.h"

/*
* Here it generates all the legal moves the position can have
* Once everything is generated it will be passed to a make move function
* And once a move is made, it will create a new ChessBoard object and then again
* it will create a new one to make a depth of X.
* After a certain depth is reached, the data will be collected to show what is the best move for this position
*/

void ChessBoard::generateMoves() {

	positions.clear();

	for (short row = 0; row < 8; row++) {
		for (short col = 0; col < 8; col++) {
			char curpiece = chessboard[row][col];
			if (isupper(curpiece) xor turn) {

				if (curpiece != ' ') {
					switch (toupper(curpiece)) {
					case 'P':
						generateMovesPawn(row, col, curpiece);
						break;
					case 'N':
						generateMovesKnight(row, col, curpiece);
						break;
					case 'R':
						generateMovesRook(row, col, curpiece);
						break;
					case 'B':
						generateMovesBishop(row, col, curpiece);
						break;
						// Add more cases for other piece types if needed
					case 'Q':
						generateMovesRook(row, col, curpiece);
						generateMovesBishop(row, col, curpiece);
						break;
					default:
						break;
					}
				}
			}
		}
	}
}


//--------PAWN--------//
void ChessBoard::generateMovesPawn(short row, short col, char curPiece) {
	short color = (islower(curPiece)) ? -1 : 1;  // -1 for black, 1 for white
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
void ChessBoard::generateMovesKnight(short row, short col, char pieceLetter) {
	// Possible knight move offsets
	short dx[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
	short dy[] = { 1, -1, 1, -1, 2, -2, 2, -2 };

	for (int i = 0; i < 8; ++i) {
		short newRow = row + dx[i];
		short newCol = col + dy[i];

		// Check if the new position is within the chessboard
		if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
			// Check if the move is valid according to your game logic (e.g., not attacking your own pieces)
			if (!sameColor(pieceLetter, chessboard[newRow][newCol]) || chessboard[newRow][newCol] == 0) {
				movePiece(row, col, newRow, newCol);
			}
		}
	}
}


//--------THE ROOK--------//
void ChessBoard::generateMovesRook(short row, short col, char pieceLetter) {
	// Horizontal right movement
	for (short newCol = col + 1; newCol < 8; newCol++) {
		if (!RookMovement(row, col, row, newCol, pieceLetter)) {
			break;
		}
	}

	// Horizontal left movement
	for (short newCol = col - 1; newCol >= 0; newCol--) {
		if (!RookMovement(row, col, row, newCol, pieceLetter)) {
			break;
		}
	}

	// Vertical up movement
	for (short newRow = row + 1; newRow < 8; newRow++) {
		if (!RookMovement(row, col, newRow, col, pieceLetter)) {
			break;
		}
	}

	// Vertical down movement
	for (short newRow = row - 1; newRow >= 0; newRow--) {
		if (!RookMovement(row, col, newRow, col, pieceLetter)) {
			break;
		}
	}
}

bool ChessBoard::RookMovement(short initRow, short initCol, short row, short col, char pieceLetter) {
	if (chessboard[row][col] == ' ') {
		movePiece(initRow, initCol, row, col);
		return true;
	}
	else if (!sameColor(pieceLetter, chessboard[row][col])) {
		movePiece(initRow, initCol, row, col);
	}
	return false;
}



//--------BISHOP--------//
void ChessBoard::generateMovesBishop(short row, short col, char curPiece) {
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
				if (!sameColor(curPiece, targetPiece)) {
					movePiece(row, col, newRow, newCol);
				}
				break;  // Stop moving in this direction after capturing or blocking
			}
		}
	}
}


void ChessBoard::movePiece(short row, short col, short newRow, short newCol) {
	char curPiece = this->chessboard[row][col];
	char newChessboard[8][8];

	// Copy the contents of the current chessboard to the newChessboard
	for (short i = 0; i < 8; i++) {
		for (short j = 0; j < 8; j++) {
			newChessboard[i][j] = this->chessboard[i][j];
		}
	}

	// Make the move by updating the newChessboard
	newChessboard[row][col] = ' ';
	newChessboard[newRow][newCol] = curPiece;

	ChessBoard newBoard(newChessboard, this, this->turn);

	// Check if the new position is unique before adding it
	positions.push_back(newBoard);

}
