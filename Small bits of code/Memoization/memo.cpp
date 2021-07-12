#include <unordered_map>
#include "memo.h"
#include <iostream>

 
using namespace std;


int rob(const vector<int> &houses, int i) {
    if (i < 0) {
        return 0;
    } else if (i == 0) {
        return houses[0];
    } else {
        return max(rob(houses, i - 1), houses[i] + rob(houses, i - 2));
    }
}

//Helper function for memo_rob. 
int _memo_rob(const vector<int> &houses, int i, unordered_map<int, int> &memoizer){
    if (memoizer.find(i) != memoizer.end()){
        return memoizer[i];
    }
    if (i < 0){
        memoizer[i] = 0;
    }
    else if (i == 0){
        memoizer[i] = houses[i];
    }
    else {
        memoizer[i] = max(_memo_rob(houses, i-1, memoizer),
                             _memo_rob(houses, i-2, memoizer) + houses[i]);
    }

    return memoizer[i];
}

int memo_rob(const vector<int> &houses, int i) {
    unordered_map<int, int> memoizer;
    return _memo_rob(houses, i, memoizer);
}


bool SBS(const vector<int> &A, int target, int i) {
    if (target == 0) {
        return true;
    } else if (i < 0 and target != 0) {
        return false;
    } else if (A[i] > target) {
        return SBS(A, target, i - 1);
    } else {
        return SBS(A, target, i - 1) or SBS(A, target - A[i], i - 1);
    }
}

//Helper funtion for memo_SBS
//Bottom Up
bool _memo_SBS(const vector<int> &A, int target, int i, 
                    unordered_map<int, unordered_map<int, bool>> memoizer){
    for (int x = 0; x <= i+1; x++){
        memoizer[x][0] = true;
    }
    for (int y = 1; y <= target; y++){
        memoizer[0][y] = false;
    } 
    for (int x = 1; x <= i+1; x++){
        for(int y = 1; y <= target; y++){
            if (y < A[x-1]){
                memoizer[x][y] = memoizer[x-1][y];
            } else {
                memoizer[x][y] = memoizer[x-1][y] || memoizer[x-1][y - A[x-1]];
            }
        }
    }
    return memoizer[i+1][target];

bool memo_SBS(const vector<int> &A, int target, int i) {
    unordered_map<int, unordered_map<int, bool>> memoizer;
    return _memo_SBS(A, target, i, memoizer);
}
