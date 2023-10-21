#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <array>
#include <vector>

class ChessBoard {
private:
	// Chessboard Variables
	char chessboard[8][8]; // Row, Column
	ChessBoard* previousPosition; // Pointer to the previous ChessBoard object
	
	float evaluation;

	//----------------Different tools----------------//
	void placePiece(char piece, short col);

	char numberToLetter(short num);

	bool sameColor(bool piece1, char piece2);

	bool myUpper(char piece);




	//----------------Move Generation----------------//
	void movePiece(short row, short col, short newRow, short newCol);

	//Pawn movement
	void generateMovesPawn(short row, short col, const bool turn);

	void enPassant(short curCol, short newCol, const bool turn);

	// Knight Movement
	void generateMovesKnight(short row, short col, const bool turn);

	//Rook movement
	void generateMovesRook(short row, short col, const bool turn);

	bool RookMovement(short inintRows, short initCol, short row, short col, const bool turn);

	//King movement
	void generateMovesBishop(short row, short col, bool turn);


	//King Movement
	void generateMovesKing(short row, short col, bool turn);

	bool castlingMovementCheck(const bool turn, const short rook);

	void castleLong(const bool turn);

	void castleShort(const bool turn);

	//For queen move generation, I've combined bishop and rook

	//----------------Evaluation tools----------------//
	short countEval(const char &piece);


	//New position constructor
	ChessBoard(char initialChessboard[8][8], ChessBoard* previousPos, short eval);

public:
	ChessBoard(); //First positions of the board

	void generateMoves(bool turn);

	void printBoard();


	short getEval();
};
#endif // CHESSBOARD_H