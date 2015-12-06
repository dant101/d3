#include <vector>
#include <string>

#ifndef PARSER
#define PARSER

void parse(char* chars, char delim, std::vector<std::string> *v, int size);
std::string chop(std::string str);

#endif 

