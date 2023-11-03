#pragma once
#include <iostream>
#include <vector>
#include <sstream>

std::string getBitsOfDouble(double);

std::string getBitsOfChar(char);

char invertCharBits(char, const std::vector<int>&);

std::string invertDoubleBits(std::string, const std::string&);

void fromBinaryToDouble(std::string);
