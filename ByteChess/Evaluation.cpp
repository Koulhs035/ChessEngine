#include "ChessBoard.h"
#include <unordered_map>

static std::unordered_map<char, short> pieceValues = {
	{'P', 1},
	{'N', 3},
	{'B', 3},
	{'R', 5},
	{'K', 500},
	{'Q', 9},
	{' ', 0}
};


short ChessBoard::countEval(const char& piece) {
	int color = (myUpper(piece)) ? 1 : -1;

	return pieceValues[toupper(piece)] * color;
}
