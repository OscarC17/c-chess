#include <iostream>
#include <vector>
#include "main.h"

std::vector<int> genTurn(std::vector<ChessPiece> pieces, std::string special_case, int src) {
    //char piece = input_board_state[from_y][from_x];
    //std::string ruleset = rules_encoded[piece];
	
	ChessPiece piece = pieces.at(src);
	std::string ruleset = pieces.at(src).moveset;
    std::vector<int> valid_moves;
	int from_x = src % 8;
	int from_y = (int)src / 8;

    std::cout << "| " << piece.type << " |";
    //std::cout << "1\n";
    std::cout << "ruleset len: " << ruleset.length() <<std::endl;
	std::cout << ruleset << "\n";
    for (int i = 0; i < ruleset.length() / 6; i++) {
		std::cout << special_case << ": " << (special_case.find(ruleset[i*6]) != std::string::npos) << std::endl;
        if (ruleset[i * 6] == '*' || special_case.find(ruleset[i*6]) != std::string::npos) {
            int rep = (ruleset[i*6+1] == 'r')?10:1;
            std::cout << "WHAT THE: " << i << " :EHT TAHW\n";
            int rule_x = std::stoi(std::string({ruleset[i*6+2], ruleset[i*6+3]}));
            int rule_y = std::stoi(std::string({ruleset[i*6+4], ruleset[i*6+5]}));
			if (piece.side == SIDE_BLACK) {
				rule_x = -rule_x;
			}
            std::cout << "x:" << rule_x << " y:" << rule_y << "\n";
            for (int j = 1; j < rep + 1; j++) {
                int x_index = from_x + rule_x * j;
                int y_index = from_y + rule_y * j;

				std::cout << "DESPACITO\n" << from_y << "\nOTICAPSED\n";
                std::cout << "THE MOVE IS AS FOLLOWS: " << x_index << ", " << y_index << "\n";

            	std::cout << "[" << x_index << ", " << y_index << "]\n";
				//std::cout << "**" << pieces.at(y_index * 8 + x_index).type << "**\n";
				//std::cout << "y_index = " << (long)y_index << "y_index < 8 = " << (y_index < 8) << "\n";
                if (x_index >= 8 || y_index >= 8 || x_index < 0 || y_index < 0) {
                	
                } else if (pieces.at(y_index * 8 + x_index).type != ' ') {
					std::cout << "numa ye";
                    if (pieces.at(y_index * 8 + x_index).side != piece.side) {
						std::cout << "[" << x_index << ", " << y_index << "]\n";
                        valid_moves.push_back(y_index * 8 + x_index);
                    }
                    j = rep + 1;
                } else {
                    valid_moves.push_back(y_index * 8 + x_index);
                }
            }
        }
    }
    //std::cout << "2\n";
    std::cout << "you have " << valid_moves.size() << " moves\n";
    for (int i = 0; i < valid_moves.size(); i++) {
        std::cout << "(" << valid_moves[i] <<  ")\n";
    }
    //std::cout << "3\n";
    return valid_moves;
}


