#pragma once

#include <vector>

// prints a vector to help debugging
// ie: prints "[1 2 3 4 5]" for a vector containing those values
void printVector(std::vector<int> v);

int randSelect(std::vector<int> v, int rankIndex);
