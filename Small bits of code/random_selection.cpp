#include <iostream>
#include <cstdlib>
#include <vector>

#include "random_selection.h"


void printVector(std::vector<int> v) {
    std::cout << "[ ";
    for (int i : v)
        std::cout << i << " ";
    std::cout << "]\n";
}


// partition
// Given a pivot location, split the vector into 
// values smaller than the pivot value, pivot value,
// and values larger than pivot value. 
// Change the given vector in place, 
// and return the rank of the pivot
int partition(std::vector<int> &v, int pivot){
	int s = 0, l = 0;
	int size = v.size();
	int value = v[pivot];
	int temp;

	v[pivot] = v[0];
	v[0] = value;

	//Partition in place
	for (int i = 1; i < size; i++){
		if (v[i] < value) {
			temp = v[i];
			v[i] = v[1 + s];
			v[1 + s] = temp;
			s++;
		} else if (v[i] > value) {
			l++;
		}
	}

	//Put the pivot in its location. 
	v[0] = v[s];
	v[s] = value;

	return s;
}

// randSelect
// Choose a random number from 0 to size of vector to be pivot
// Run partition on that pivot. 
// Recurse or return value depending on the result of partition. 

int randSelect(std::vector<int> v, int rankIndex) {
	if ((rankIndex < 0) || (rankIndex >= (int)v.size())){
		std::cerr << "Invalid index!\n";
		return -1;
	}
	std::cout << "Looking for value with rank " << rankIndex << " in the array:\n";
	printVector(v);
	srand(time(NULL));
	int pivot = rand() % (int)v.size();
	int pRank = partition(v, pivot);

	if (rankIndex == pRank){
		std::cout << "Selected " << v[pRank] << " as the pivot; its rank is " << pRank << "; Thus, we recurse on nothing. We are done.\n";
		return v[pRank];
	} else if (rankIndex < pRank){
		std::cout << "Selected " << v[pRank] << " as the pivot; its rank is " << pRank << "; Thus, we recurse on left.\n";
		return randSelect(std::vector<int>(v.begin(), v.begin() + pRank), rankIndex);
	} else {
		std::cout << "Selected " << v[pRank] << " as the pivot; its rank is " << pRank << "; Thus, we recurse on right.\n";
		return randSelect(std::vector<int>(v.begin() + pRank + 1, v.end()), rankIndex - pRank - 1);
	}
	
    return 0;
}
