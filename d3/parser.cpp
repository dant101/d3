#include "stdafx.h"
#include "parser.h"
#include <iostream>

// Split char* into vector of strings
void parse(char* chars, char delim, std::vector<std::string> *v, int size) {

	std::string s = "";
	for (int i = 0; i < size; i++) {
		if (chars[i] == delim) {
			v->push_back(chop(s));
			s = "";
		}
		else {
			s += chars[i];
		}
	}
	v->push_back(chop(s));

}

// Chop off trailing whitespace
std::string chop(std::string str) {
	int i = str.length() - 1;
	for (i; i >= 0; i--) {
		if (str[i] != ' ' && str[i] != '\0') {
			i++;
			break;
		}
	}

	return str.substr(0,i);
}