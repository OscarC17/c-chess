#include <vector>

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
	
	ChessPiece(int i) : type(i) {}
};

int drawBoard(std::vector<ChessPiece>);

int inputToIndex();
