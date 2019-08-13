// QueenSolver.cpp : Defines the entry point for the console application.
//

#include "RecursionList.h"
#include <iostream>
#include <string>


int main()
{
	ChessBoard chessBoard;

	std::string output = chessBoard.Solve;

	std::cout << output << std::endl;

    return 0;
}

