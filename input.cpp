#include <cctype>
#include <iostream>
#include <string>
#include "main.h"

int inputToIndex() {
	
	char first;
	char second;

	for (bool breakvar = false; !breakvar;) {
		std::string sin = "  ";
		std::cin >> sin;
		if (sin.length() == 3) {
			std::cout << "Invalid input!\n";
		} else {
			first = std::tolower(sin.at(0));
			second = sin.at(1);
			breakvar = true;
		}
		if (first < 97 || first > 104 || second < 49 || second > 56) {
			std::cout << "Invalid input!\n";
			breakvar = false;
		} else {
			first = first - 97;
			second = 7 - (second - 49);
		}
	}
	return first * 8 + second;
} 
