#include "DepthGen.h"

extern DepthGen myGen;

// Function to load new depth.
void DepthGen::loadToDepth(int maxDepth, ChessBoard initialPosition) {
    bool turn = true;
	positions.push_back(initialPosition);
	inDepthPositions.push_back(positions);
	positions.clear();
	for (int d = 0; d < maxDepth; d++) {
		std::cout <<"In depth: " << d + 1<< '\n';
		size_t secondVectorSize = inDepthPositions[d].size();
		
		for (int i = 0; i < secondVectorSize; i++) {
			inDepthPositions[d][i].generateMoves(turn);
		}
		
		inDepthPositions.push_back(positions);
		std::cout << "Legal moves found: " << secondVectorSize << '\n' << '\n';

		positions.clear();
	}
}



