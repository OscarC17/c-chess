#include <math.h>
#include <unordered_map>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

const bool WHITE = true;

const bool BLACK = false;

std::string top = "        A     B     C     D     E     F     G     H\n";
std::string vert_line = "     -------------------------------------------------\n";
std::string w_line = "     ######      ######      ######      ######       \n";
std::string b_line = "           ######      ######      ######      ###### \n";

bool turn = WHITE;

std::string board_state_string = "RHBQKBHRPPPPPPPP                                pppppppprhbqkbhr";

std::vector<std::vector<char>> board_state;


std::unordered_map<char, std::string> art_assoc = {
    {'p', "()"},
    {'r', "uu"},
    {'h', "|>"},
    {'b', "{}"},
    {'q', "vv"},
    {'k', "++"},
    {'P', "()"},
    {'R', "nn"},
    {'H', "<|"},
    {'B', "{}"},
    {'Q', "^^"},
    {'K', "++"},
    {' ', ""},
};

bool white_or_black(char x) {
    return x > (char)96;
}

int letter_to_num(char letter) {
    if (letter > (char)96) {
        return (int)letter - 97;
    } else {
        return (int)letter - 65;
    }
}

std::unordered_map<char, std::string> rules_encoded = {
    {'p', "*s0001as-101bs0101cs0002"},
    {'r', "*r0001*r00-1*r0100*r-100"},
    {'h', "*s0102*s0201*s02-1*s01-2*s-102*s-201*s-2-1*s-1-2"},
    {'b', "*r0101*r01-1*r-101*r-1-1"},
    {'q', "*r0101*r01-1*r-101*r-1-1*r0001*r00-1*r0100*r-100"},
    {'k', "*s0101*s01-1*s-101*s-1-1*s0001*s00-1*s0100*s-100"},
    {'P', "*s00-1as-1-1bs01-1cs00-2"},
    {'R', "*r0001*r00-1*r0100*r-100"},
    {'H', "*s0102*s0201*s02-1*s01-2*s-102*s-201*s-2-1*s-1-2"},
    {'B', "*r0101*r01-1*r-101*r-1-1"},
    {'Q', "*r0101*r01-1*r-101*r-1-1*r0001*r00-1*r0100*r-100"},
    {'K', "*s0101*s01-1*s-101*s-1-1*s0001*s00-1*s0100*s-100"},
};

std::vector<std::pair<int, int>> generate_list_of_valid_moves(std::unordered_map<char, std::string> input_rules_encoded, char * input_board_state, char special_case, int from_x, int from_y, int to_x, int to_y) {
    char piece = input_board_state[from_x + 8 * from_y];
    std::string ruleset = rules_encoded[piece];
    std::vector<std::pair<int, int>> valid_moves;

    std::cout << "| " << piece << " |";
    std::cout << "1\n";
        std::cout << "ruleset len: " << ruleset.length() <<std::endl;
    for (int i = 0; i < ruleset.length() / 6; i++) {
        if (ruleset[i * 6] == '*' || ruleset[i*6] == special_case) {
            int rep = (ruleset[i*6+1] == 'r')?10:1;
            int rule_x = std::stoi(std::string({ruleset[i*6+2], ruleset[i*6+3]}));
            int rule_y = std::stoi(std::string({ruleset[i*6+4], ruleset[i*6+5]}));
            std::cout << rule_x << rule_y << "\n";
            for (int j = 0; j < rep; j++) {
                int bs_index = (from_x + rule_x * j) + 8 + (from_y + rule_y * j) * 8;
                if (bs_index >= 64) {
                
                } else if (input_board_state[bs_index] != ' ') {
                
                } else {
                    valid_moves.push_back(std::pair<int, int> (from_x + rule_x * j, from_y + rule_y * j));
                }
            }
        }
    }
    std::cout << "2\n";
    std::cout << "you have " << valid_moves.size() << " moves\n";
    for (auto move : valid_moves) {
        std::cout << "(" << move.first << ", " << move.second << ")\n";
    }
    std::cout << "3\n";
    return valid_moves;
}


int main() {

    for (int i = 0; i < 8; i++) {
        std::vector<char> line;
        for (int j = 0; j < 8; j++) {
            line.push_back(board_state_string[i * 8 + j]);
        }
        board_state.push_back(line);
    }

    for (auto line : board_state) {
        for (auto piece : line) {
            std::cout << piece;
        }
        std::cout << std::endl;
    }

    for(;;) {

        // Board printing
        /*
        std::string board_printable = "\n";
        board_printable += top;
        board_printable += "\n";
        for (int i = 0; i < 8; i++) {
            std::string active_line = "";
            if (i % 2 == 0) {
                active_line = w_line;
            } else {
                active_line = b_line;
            }
            std::string active_line_num = active_line;
            std::string active_line_top = active_line;
            std::string active_line_bottom = active_line;

            char numberchar[8];
            sprintf(numberchar, "%d", 8 - i);
            std::string number(numberchar);
            active_line_num.replace(2, 1, number);
            for (int j = 0; j < 8; j++) {
                int x = (j * 6) + 7;
                if (board_state[i * 8 + j] != ' ') {
                    active_line_num.replace(x, 2, art_assoc[board_state[i*8+j]]);
                }
                if (board_state[i * 8 + j] > (char)96) {
                    active_line_bottom.replace(x, 2, "][");
                } else if (board_state[i * 8 + j] != (char)32) {
                    active_line_top.replace(x, 2, "][");
                }
            }
            board_printable += active_line_top;
            board_printable += active_line_num;
            board_printable += active_line_bottom;
        }
        std::cout << board_printable;

        // Turn handling
        std::cout << "\n" << (turn?"White":"Black") << "'s turn.\n";
        std::cout << "Select piece to move: ";
        std::string user_input;
        
        std::cin >> user_input;
        int from_x_in = letter_to_num(user_input[0]);
        int from_y_in = 8 - ((int)user_input[1]-48);
        int from_index = letter_to_num(from_x_in + 8 * from_y_in);
        
        std::cout << (int)user_input[1] -49 << "\n";
        std::cout << "Select destination: ";
        
        std::cin >> user_input;
        int to_x_in = letter_to_num(user_input[0]);
        int to_y_in = 8 - ((int)user_input[1]-48);
        int to_index = letter_to_num(to_x_in + 8 * to_y_in);

        if (board_state[from_index] != ' ' && white_or_black(board_state[from_index]) == turn) {
            board_state[to_index] = board_state[from_index];
            board_state[from_index] = ' ';
        } else {
            std::cout << "You (" << (turn?"White":"Black") << ") cannot move that piece\n";  
            turn = !turn;
        }

        generate_list_of_valid_moves(rules_encoded, board_state, ' ',  from_x_in,  from_y_in,  to_x_in,  to_y_in);

        turn = !turn;
        */


    }
}

