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

char board_state[] = "RHBQKBHRPPPPPPPP                                pppppppprhbqkbhr";


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


int main() {
    for(;;) {

        // Board printing
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
        int from_index = letter_to_num(user_input[0]) + 8 * (8 - ((int)user_input[1] - 48));
        int from_x_in = letter_to_num(user_input[0]);
        int from_y_in = (int)user_input[1]-48;
        std::cout << (int)user_input[1] -49 << "\n";
        std::cout << "Select destination: ";
        std::cin >> user_input;
        int to_index = letter_to_num(user_input[0]) + 8 * (8 - ((int)user_input[1] - 48));
        int to_x_in = letter_to_num(user_input[0]);
        int to_y_in = (int)user_input[1]-48;
        if (board_state[from_index] != ' ' && white_or_black(board_state[from_index]) == turn) {
            board_state[to_index] = board_state[from_index];
            board_state[from_index] = ' ';
        } else {
            std::cout << "You (" << (turn?"White":"Black") << ") cannot move that piece\n";  
            turn = !turn;
        }
        turn = !turn;
        


    }
}

