#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>


class ChessBoard {
private:
	// Chessboard Variables
	char chessboard[8][8]; // Row, Column
	ChessBoard* previousPosition; // Pointer to the previous ChessBoard object

	//Different tools for the chessboard
	void placePiece(char piece, short col);
	char numberToLetter(short num);
	bool sameColor(bool piece1, char piece2);
	bool myUpper(char piece);



	//Move Generation
	void movePiece(short row, short col, short newRow, short newCol);

	void generateMovesPawn(short row, short col, bool turn);

	void generateMovesKnight(short row, short col, bool turn);

	void generateMovesRook(short row, short col, bool turn);

	bool RookMovement(short inintRows, short initCol, short row, short col, bool turn);

	void generateMovesBishop(short row, short col, bool turn);

	void generateMovesKing(short row, short col, bool turn);

	//For queen move generation, I've combined bishop and rook

	//New position constructor
	ChessBoard(char initialChessboard[8][8], ChessBoard* previousPosition);



public:
	ChessBoard(); //Default constructor


	void generateMoves(bool turn);

	void printBoard();

	char(*getChessboard())[8];
};
#endif // CHESSBOARD_H