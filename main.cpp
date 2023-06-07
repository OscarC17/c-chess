#include <iostream>
#include "main.h"

int main(int argc, char * argv[]) {
	std::vector<ChessPiece> chessboard;
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chessboard.push_back(ChessPiece(PIECE_PAWN, SIDE_WHITE));
		}
	}

	chessboard[4 * 8 + 4].type = PIECE_KING;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << chessboard[i * 8 + j].type;

		}
		std::cout << std::endl;
	}

	drawBoard(chessboard);

	inputToIndex();


	return 0;
}
