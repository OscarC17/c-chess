#include <vector>
#include <utility>
#include <string>

const char SIDE_WHITE = '1';
const char SIDE_BLACK = '0';
const char SIDE_NONE = ' ';

const char PIECE_PAWN = 'p';
const char PIECE_ROOK = 'r';
const char PIECE_KNIGHT = 'h';
const char PIECE_BISHOP = 'b';
const char PIECE_QUEEN = 'q';
const char PIECE_KING = 'k';

class ChessPiece {
public:
	char type;
	char side;
	bool alive;
	std::string moveset;
	
	ChessPiece(char t, char s, bool a, std::string m);
};


int drawBoard(std::vector<ChessPiece>, int, std::vector<int>);

int inputToIndex();

std::vector<int> genTurn(std::vector<ChessPiece>, std::string, int);
