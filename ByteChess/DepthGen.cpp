#include <algorithm>
#include "DepthGen.h"
extern DepthGen myGen;

/*
* Here are all the positions, they are saved here from the generateMoves() function
* Once all the positions are generated for the specific move, they are pushed inside another vector
* In order to avoid duplicate positions and take up more space.
* Plus it makes the structure like a Tree, which will make it a bit easier for future calculations
*/

// Function to load new depth.
void DepthGen::loadToDepth(int depth) {
	bool turn = false; // Sets turn to white
	positions.push_back(ChessBoard());
	inDepthPositions.push_back(positions);
	positions.clear();

	for (int d = 0; d < depth; d++) {
		turn = !turn;

		std::cout << "In depth: " << d + 1 << '\n';
		size_t secondVectorSize = inDepthPositions[d].size();
		for (int i = 0; i < secondVectorSize; i++) {
			inDepthPositions[d][i].generateMoves(turn);
		}



		short movesCut = 50;
		if (positions.size() >= movesCut && d % 4 == 0) {
			SortAndTruncate(movesCut, true);

		}

		if (positions.size() >= movesCut && d % 9 == 1) {
			SortAndTruncate(movesCut, true);
		}

		inDepthPositions.push_back(positions); //Puts all the positions from the current turn in a vector
		std::cout << "Legal moves found: " << secondVectorSize << '\n' << '\n';

		positions.clear(); // And clears the positions saved to avoid calculating positions from a previous move
	}
}


// TODO: I have to make this actually work
void DepthGen::SortAndTruncate(int n, bool ascending) {
	std::sort(positions.begin(), positions.end(), [ascending]( ChessBoard& board1,  ChessBoard& board2) {
		return (ascending ? (board1.getEval() < board2.getEval()) : (board1.getEval() > board2.getEval()));
		});

		positions.erase(positions.begin() + n, positions.end());	
}