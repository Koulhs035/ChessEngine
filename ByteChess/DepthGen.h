#ifndef DEPTHGEN_H
#define DEPTHGEN_H

#include <vector>
#include "ChessBoard.h"


struct DepthGen {
	// Positions are saved here
	std::vector<ChessBoard> positions;
	std::vector<std::vector<ChessBoard>> inDepthPositions;

	void loadToDepth(int depth);

	void SortAndTruncate(int n, bool ascending);

};

#endif