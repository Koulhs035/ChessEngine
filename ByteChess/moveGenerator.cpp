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


void ChessBoard::generateMoves(const bool turn) {

	for (short row = 0; row < 8; row++) {
		for (short col = 0; col < 8; col++) {
			char curpiece = chessboard[row][col];

			// Check if the square is occupied by a piece
			if (curpiece != ' ' && myUpper(curpiece) == turn) {
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
void ChessBoard::generateMovesPawn(const short row, const short col, const bool turn) {
	short color = turn ? 1 : -1;  // -1 for black, 1 for white
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
			if (leftPiece != ' ' && !sameColor(turn, leftPiece)) {
				movePiece(row, col, leftCol, newRow);
			}


		}
		enPassant(row, col, rightCol);

		if (rightCol <= 7) {
			char rightPiece = chessboard[newRow][rightCol];
			if (rightPiece != ' ' && !sameColor(turn, rightPiece)) {
				movePiece(row, col, rightCol, newRow);
			}
		}
		enPassant(col, rightCol, turn);

	}
}


void ChessBoard::enPassant(const short curCol, const short prevCol, const bool turn) {

	if (previousPosition != nullptr) {
		//White side En Passant
		if (!turn && (chessboard[4][prevCol] == 'p' && previousPosition->chessboard[6][prevCol] == 'p' && previousPosition->chessboard[5][prevCol] == ' ')) {
			char newChessboard[8][8];

			memcpy(newChessboard, this->chessboard, 64);
			newChessboard[4][curCol] = ' ';

			newChessboard[4][prevCol] = ' '; // Pawn captured

			newChessboard[5][prevCol] = 'P';

			myGen.positions.push_back(ChessBoard(newChessboard, this, 1));




		} // Black side En Passant
		else if (turn && (chessboard[3][prevCol] == 'P' && previousPosition->chessboard[1][prevCol] == 'P' && previousPosition->chessboard[2][prevCol] == ' ')) {
			char newChessboard[8][8];

			memcpy(newChessboard, this->chessboard, 64);

			newChessboard[2][curCol] = ' ';

			newChessboard[3][prevCol] = ' '; // Pawn captured

			newChessboard[2][prevCol] = 'p';

			myGen.positions.push_back(ChessBoard(newChessboard, this, -1));


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
			// Check if the move is valid according to your game logic (e.g., not attack your own pieces)
			if (!sameColor(turn, chessboard[newRow][newCol]) || chessboard[newRow][newCol] == 0) {
				movePiece(row, col, newRow, newCol);
			}
		}
	}
}


//--------THE ROOK--------//
void ChessBoard::generateMovesRook(const short row, const short col, const bool turn) {
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

bool ChessBoard::RookMovement(const short initRow, const short initCol, const short row, const short col, const bool turn) {
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


	if (chessboard[0][4] == 'K' || chessboard[7][4] == 'k') {
		switch (turn)
		{
		case true: // White side castling
			if (castlingMovementCheck(0, 0)) { //Castle long check
				castleLong(true);
			}
			else if (castlingMovementCheck(0, 7)) { //Castle short check
				castleShort(true);
			}
			break;
		case false: // Black side castling
			if (castlingMovementCheck(7, 0)) { //Castle long check
				castleLong(false);
			}
			else if (castlingMovementCheck(7, 7)) { //Castle short check
				castleShort(false);

			}
			break;
		}
	}
}




bool ChessBoard::castlingMovementCheck(bool turn, short rook) {
	char king = turn ? 'K' : 'k';
	short row = turn ? 0 : 7;

	ChessBoard* curPos = previousPosition;
	// Go through all the previous positions
	while (curPos != nullptr) {
		// Check if the necessary pieces moved
		if (previousPosition->chessboard[row][rook] != ' ' && (previousPosition->chessboard[row][4] != 'K')) {
			return false; // Return false if the conditions are not met
		}
		curPos = curPos->previousPosition;
	}
	return true;
}




void ChessBoard::castleLong(bool turn) {
	// Sets the king or Rook type depending on turn
	char king = turn ? 'K' : 'k';
	char rook = turn ? 'R' : 'r';
	short row = turn ? 0 : 7;

	if (chessboard[row][1] != ' ' && chessboard[row][2] != ' ' && chessboard[row][3] != ' ') {
		return;
	}

	// Creates a special case for move piece that matches castling
	char newChessboard[8][8];
	memcpy(newChessboard, chessboard, 64);

	// Change evaluation
	short color = turn ? 1 : -1;  // 1 if the piece is white and -1 if piece is black
	evaluation += 0.1 * color;

	// Sets the pieces correctly
	newChessboard[row][4] = ' ';
	newChessboard[row][0] = ' ';
	newChessboard[row][3] = rook;
	newChessboard[row][2] = king;
}


void ChessBoard::castleShort(bool turn) {
	// Sets the king or Rook type depending on turn
	char king = turn ? 'K' : 'k';
	char rook = turn ? 'R' : 'r';
	short row = turn ? 0 : 7;

	if (chessboard[row][5] != ' ' && chessboard[row][6] != ' ') {
		return;
	}

	char newChessboard[8][8];
	memcpy(newChessboard, chessboard, 64);

	// Change evaluation
	short color = turn ? 1 : -1;  // 1 if the piece is white and -1 if piece is black
	evaluation += 0.1 * color;

	// Sets the pieces correctly
	newChessboard[row][4] = ' ';
	newChessboard[row][7] = ' ';
	newChessboard[row][5] = rook;
	newChessboard[row][6] = king;
}






//----------------Generate new class----------------//
void ChessBoard::movePiece(const short row, const short col, const short newRow, const short newCol) {

	//If there was a checkmate on the previous move, continue no further
	if (previousPosition != nullptr && (previousPosition->getEval() > 500 || previousPosition->getEval() < -500)) {
		return;
	}

	char curPiece = this->chessboard[row][col];
	short color = (myUpper(curPiece)) ? 1 : -1;  // 1 if the piece is white and -1 if piece is black
	evaluation += 0.1 * color;

	// Create a replica of the current position 
	char newChessboard[8][8];
	memcpy(newChessboard, chessboard, 64);


	// Make the move by updating new chessboard
	char takenPiece = newChessboard[newRow][newCol];

	newChessboard[row][col] = ' '; // Set the position that piece moved from to 0
	newChessboard[newRow][newCol] = curPiece; // And put it in its new position

	// Add the new position to the vector with all the possible positions
	myGen.positions.push_back(ChessBoard(newChessboard, this, countEval(takenPiece)));

	return;
}