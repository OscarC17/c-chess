#include <iostream>
#include "main.h"

int main(int argc, char * argv[]) {
	std::vector<ChessPiece> chessboard;
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chessboard.push_back(ChessPiece(0));
		}
	}

	chessboard[4 * 8 + 4] = 5;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << chessboard[i * 8 + j].type;

		}
		std::cout << std::endl;
	}

	inputToIndex();

	return 0;
}
