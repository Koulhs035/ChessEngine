#include <vector>
#include <iostream>
#include <chrono>


#include "ChessBoard.h"
#include "DepthGen.h"


DepthGen myGen;

int main() {

    std::cout << "Hello there!" << '\n';
    // Create an initial chessboard
    ChessBoard initialBoard;
    // Specify the depth
	//----------------------------------------------------------------



    // Start the timer
    auto start_time = std::chrono::high_resolution_clock::now();

    myGen.loadToDepth(5, initialBoard);





    // Stop the timer
    auto end_time = std::chrono::high_resolution_clock::now();
    // Calculate the duration
   
    
    
    
    
    
    
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
     // Output the duration
    std::cout << "Time taken to generate positions: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}