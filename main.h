#include <vector>

const bool SIDE_WHITE = true;
const bool SIDE_BLACK = false;

const int PIECE_PAWN = 0;
const int PIECE_ROOK = 1;
const int PIECE_KNIGHT = 2;
const int PIECE_BISHOP = 3;
const int PIECE_QUEEN = 4;
const int PIECE_KING = 5;

class ChessPiece {
public:
	//type: 
	//	0 = pawn
	//	1 = rook
	//	2 = knight
	//	3 = bishop
	//	4 = queen
	//	5 = king
	int type;
	bool side;
	
	ChessPiece(int t, bool s) : type(t), side(s) {}
};

int drawBoard(std::vector<ChessPiece>);

int inputToIndex();

int evaluateRules();
