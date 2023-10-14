#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>


class ChessBoard {
private:
	bool turn; // False == Black, True == White

	// Chessboard Variables
	char chessboard[8][8]; // Row, Column

	ChessBoard* previousPosition; // Pointer to the previous ChessBoard object

	//std::vector <std::pair<char, std::pair <short, short>>> legalMoves; // Contains all the legal moves in algebraic chess notation

	std::vector<ChessBoard> positions;

	//Different tools for the chessboard
	void placePiece(char piece, short col);
	char numberToLetter(short num);
	bool sameColor(char piece1, char piece2);



	//Move Generation
	void movePiece(short row, short col, short newRow, short newCol);

	void generateMovesPawn(short row, short col, char pieceLetter);

	void generateMovesKnight(short row, short col, char pieceLetter);

	void generateMovesRook(short row, short col, char pieceLetter);

	bool RookMovement(short inintRows, short initCol, short row, short col, char pieceLetter);

	void generateMovesBishop(short row, short col, char pieceLetter);

	//For queen move generation, I've combined bishop and rook

	//New position constructor
	ChessBoard(char initialChessboard[8][8], ChessBoard* previousPosition, bool previousTurn);



public:
	ChessBoard(); //Default constructor


	void generateMoves();

	void printBoard();

	std::vector<ChessBoard> getPositions();
};
#endif // CHESSBOARD_H