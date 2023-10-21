#include <vector>
#include <iostream>
#include <chrono>


#include "ChessBoard.h"
#include "DepthGen.h"


DepthGen myGen;

int main() {

    std::cout << "Hello there!" << '\n';


    int depth = 40;

    // Start the timer
    auto start_time = std::chrono::high_resolution_clock::now();

    myGen.loadToDepth(depth);





    // Stop the timer
    auto end_time = std::chrono::high_resolution_clock::now();
    // Calculate the duration
   
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
     // Output the duration
    std::cout << "Time taken to generate positions: " << duration.count() << " milliseconds" << std::endl;

    for (int i = 0; i < myGen.inDepthPositions[depth].size(); i++) {
        myGen.inDepthPositions[10][i].printBoard();
        std::cout << myGen.inDepthPositions[depth][i].getEval() << '\n';
        
    }

    char lmao;
    std::cin >> lmao;

    return 0;

}