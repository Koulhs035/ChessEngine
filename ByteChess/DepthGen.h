#ifndef DEPTHGEN_H
#define DEPTHGEN_H

#include <vector>
#include "ChessBoard.h"


struct DepthGen {

	std::vector<ChessBoard> positions;
	std::vector<std::vector<ChessBoard>> inDepthPositions;

	void loadToDepth(int depth, ChessBoard initialPosition);

	//std::vector<ChessBoard> pruneDuplicates();
};


#endif