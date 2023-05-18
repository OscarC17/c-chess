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

std::unordered_map<char, std::string> rules_encoded = {
    {'P', "*s0001as-101bs0101cs0002"},
    {'R', "*r0001*r00-1*r0100*r-100"},
    {'H', "*s0102*s0201*s02-1*s01-2*s-102*s-201*s-2-1*s-1-2"},
    {'B', "*r0101*r01-1*r-101*r-1-1"},
    {'Q', "*r0101*r01-1*r-101*r-1-1*r0001*r00-1*r0100*r-100"},
    {'K', "*s0101*s01-1*s-101*s-1-1*s0001*s00-1*s0100*s-100"},
    {'p', "*s00-1as-1-1bs01-1cs00-2"},
    {'r', "*r0001*r00-1*r0100*r-100"},
    {'h', "*s0102*s0201*s02-1*s01-2*s-102*s-201*s-2-1*s-1-2"},
    {'b', "*r0101*r01-1*r-101*r-1-1"},
    {'q', "*r0101*r01-1*r-101*r-1-1*r0001*r00-1*r0100*r-100"},
    {'k', "*s0101*s01-1*s-101*s-1-1*s0001*s00-1*s0100*s-100"},
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

bool valid_move(std::string rule, char special_case, char * board_state, int from_x, int from_y, int to_x, int to_y) {
    bool passes = false;
    int dx = from_x - to_x;
    int dy = from_y - to_y;
    std::vector<std::pair<int, int>> rules_generated;
    std::vector<std::pair<int, int>> rules_generated_normal;

    for (int i = 0; i < (int)rule.length() / 6; i++) {
        if (rule[i * 6] == '*' || rule[i * 6] == special_case) {
            std::string x_rule_str;
            std::string y_rule_str;
            x_rule_str += rule[i * 6 + 2];
            x_rule_str += rule[i * 6 + 3];
            y_rule_str += rule[i * 6 + 4];
            y_rule_str += rule[i * 6 + 5];
            std::pair<int, int> rule_generated_single;
            int x_rec = std::stoi(x_rule_str);
            int y_rec = std::stoi(y_rule_str);
            rule_generated_single.first = x_rec;
            rule_generated_single.second = y_rec;
            rules_generated.push_back(rule_generated_single);
            if (rule[i * 6 + 1] == 'r') {
                for (int j = 0; j < 10; j++) {
                    rule_generated_single.first = rule_generated_single.first + x_rec;
                    rule_generated_single.second = rule_generated_single.second + y_rec;
                    rules_generated.push_back(rule_generated_single);
                }
            }
        }
    }


    for (auto i : rules_generated) {
        rules_generated_normal.push_back(i);
    }



    std::cout << "\nsize: " << rules_generated.size() << "\n";
    for (size_t i = 0; i < rules_generated_normal.size(); i++) {
        double magnitude = sqrt(pow(rules_generated[i].first, 2) + pow(rules_generated[i].second, 2));
        rules_generated_normal[i].first = (static_cast<double>(rules_generated_normal[i].first) / magnitude) * sqrt(2);
        rules_generated_normal[i].second = (static_cast<double>(rules_generated_normal[i].second) / magnitude) * sqrt(2);
        std::cout << "(" << rules_generated[i].first << ", " << rules_generated[i].second << ") ";
        std::cout << "(" << rules_generated_normal[i].first << ", " << rules_generated_normal[i].second << ")\n";
    }

    int x_co = to_x;
    int y_co = to_y;
    size_t savei = 0;
    for (size_t i = 0; i < rules_generated.size(); i++) {
        if (to_x == from_x + rules_generated[i].first && to_y == from_y + rules_generated[i].second) {
            passes = true;
            savei = i;
            i = rules_generated.size() + 1;
        }
    }
    for (int i = 0; i < 1000; i++) {
        if (board_state[y_co * 8 + x_co] != ' ') {
            passes = false;
            i = 1001;
        } else if (x_co == from_x && y_co == from_y) {
            i = 1001;
        }
        std::cout << "Moments before\n";
        std::cout << x_co << ", " << rules_generated_normal[savei].first << "\n";
        x_co += rules_generated_normal[savei].first;
        std::cout << "within\n";
        y_co += rules_generated_normal[savei].second;
        std::cout << "disaster\n";
    }
    std::cout << "oopa\n";
    return passes;
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
        std::cout << valid_move(rules_encoded[board_state[from_index]], ' ', board_state, from_x_in, from_y_in, to_x_in, to_y_in);
        
    std::cout << "oopa1\n";


    }
}

