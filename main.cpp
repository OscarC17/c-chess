#include <iostream>
#include <string>
#include <unordered_map>
#include "main.h"

std::string boardfillp = 
	"rhbqkbhr"
	"pppppppp"
	"        "
	"     q  "
	"        "
	"        "
	"pppppppp"
	"rhbqkbhr";

std::string boardfills =
	"00000000"
	"00000000"
	"        "
	"     1  "
	"        "
	"        "
	"11111111"
	"11111111";

std::unordered_map<char, std::string> rulesencoded = {
    {'P', "*s0001as-101bs0101cs0002"},
    {'r', "*r0001*r00-1*r0100*r-100"},
    {'h', "*s0102*s0201*s02-1*s01-2*s-102*s-201*s-2-1*s-1-2"},
    {'b', "*r0101*r01-1*r-101*r-1-1"},
    {'q', "*r0101*r01-1*r-101*r-1-1*r0001*r00-1*r0100*r-100"},
    {'k', "*s0101*s01-1*s-101*s-1-1*s0001*s00-1*s0100*s-100"},
    {'p', "*s00-1ds-1-1es01-1fs00-2"},
    {'R', "*r0001*r00-1*r0100*r-100"},
    {'H', "*s0102*s0201*s02-1*s01-2*s-102*s-201*s-2-1*s-1-2"},
    {'B', "*r0101*r01-1*r-101*r-1-1"},
    {'Q', "*r0101*r01-1*r-101*r-1-1*r0001*r00-1*r0100*r-100"},
    {'K', "*s0101*s01-1*s-101*s-1-1*s0001*s00-1*s0100*s-100"},
};


ChessPiece::ChessPiece(char t, char s, bool a, std::string m) {
	type = t; side = s; alive = a; moveset = m;

}


int main(int argc, char * argv[]) {
	std::vector<ChessPiece> chessboard;

	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chessboard.push_back(
						ChessPiece(boardfillp.at(j * 8 + i), 
						boardfills.at(j * 8 + i), 
						(boardfillp.at(j * 8 + i) != ' ')?true:false,
						rulesencoded[boardfillp.at(j*8+i)]
						));
		}
	}


	char turn = SIDE_WHITE;
	while (true) {
		drawBoard(chessboard, -1, {});
		std::cout << (turn=='1'?"White":"Black") << "'s turn\n" << "Select a piece\n";
		int srcIndex = inputToIndex();
		ChessPiece selectedpiece = chessboard.at(srcIndex);
		if (turn != selectedpiece.side) {
			std::cout << "You do not own that piece\n";
		} else {
			std::vector<int> moves = genTurn(chessboard, "f", srcIndex);
			drawBoard(chessboard, srcIndex, moves);
			std::cout << (turn=='1'?"White":"Black") << "'s turn\n" << "Select a destination\n";
			int destIndex = inputToIndex();
			turn = turn=='0'?'1':'0';
		}
	}


	return 0;
}
