#include <iostream>
#include <vector>
#include <string>
#include "main.h"

const std::string canvastemplate = 
	"     a   b   c   d   e   f   g   h  \n"
	"   |---|---|---|---|---|---|---|---|\n"
	" 8 |   |   |   |   |   |   |   |   |\n"
	"   |---|---|---|---|---|---|---|---|\n"
	" 7 |   |   |   |   |   |   |   |   |\n"
	"   |---|---|---|---|---|---|---|---|\n"
	" 6 |   |   |   |   |   |   |   |   |\n"
	"   |---|---|---|---|---|---|---|---|\n"
	" 5 |   |   |   |   |   |   |   |   |\n"
	"   |---|---|---|---|---|---|---|---|\n"
	" 4 |   |   |   |   |   |   |   |   |\n"
	"   |---|---|---|---|---|---|---|---|\n"
	" 3 |   |   |   |   |   |   |   |   |\n"
	"   |---|---|---|---|---|---|---|---|\n"
	" 2 |   |   |   |   |   |   |   |   |\n"
	"   |---|---|---|---|---|---|---|---|\n"
	" 1 |   |   |   |   |   |   |   |   |\n"
	"   |---|---|---|---|---|---|---|---|\n";

int cellwidth = 4;
int cellheight = 2;
int leftoffset = 5;
int topoffset = 2;
int canvaswidth = 37;

int getCanvasIndex(int x, int y) {
	return cellheight * canvaswidth * y + topoffset * canvaswidth + leftoffset + cellwidth * x;
}

int drawBoard(std::vector<ChessPiece> chessboard, int selection, std::vector<int> moves) {

	std::string canvas = canvastemplate;
	for (size_t i = 0; i < chessboard.size(); i++) {
		char side = ' ';
		if (chessboard.at(i).side == '0') {
			side = '+';
		} else if (chessboard.at(i).side == '1') {
			side = '-';
		}

		
		int canvasindex = getCanvasIndex((int) i / 8, i % 8);

		canvas.at(canvasindex - 1) = side;

		canvas.at(canvasindex) = chessboard.at(i).type;	

	}
	if (selection >= 0) {
		canvas.at(getCanvasIndex((int) selection / 8, selection % 8) + 1) = '*';
	}
	if (moves.size() <= 0) {
		std::cout << canvas;
		return 0;
	}

	for (int i = 0; i < moves.size(); i++) {
		canvas.at(getCanvasIndex((int) moves.at(i) / 8, moves.at(i) % 8) + 1) = '.';
		std::cout << canvas;
	}
	return 0;	
}


