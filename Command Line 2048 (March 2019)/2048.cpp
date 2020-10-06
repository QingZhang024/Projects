/*
 * 2048.cpp
 * COMP11 Project 1, Spring 2019, Tufts University
 * Modified by: Qing Zhang
 * Date: 3/4/19
 */

#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <sstream>
using namespace std;

// CONSTANTS (IF ANY) GO HERE


// FUNCTION PROTOTYPES GO HERE
int string2int(string s);
string int2string(int num);
void print_padded_string(string s);
void play();
int generate_new();
void place_rand(int board[4]);
int rand4();
void moveright();
bool checkright(int array[4], int n);
bool checkleft(int array[4], int n);
void print(int board[4]);
void moveleft(int board[4]);
void moveright(int board[4]);
void mergeleft(int board[4]);
void mergeright(int board[4]);
bool checkgameover(int board[4]);

int main() {
    play();
    return 0;
}

void play() {
   // START YOUR CODE HERE

int board[4];
int i = 0;
bool game;

string key;

game = true;

srand(time(NULL));

while (i < 4){
    board[i] = 0;
    i++;
}
place_rand(board);
print(board);

while (game == true) {
    cin >> key;
    if ((key == "a") or (key == "A")){
        moveleft(board);
        mergeleft(board);
        place_rand(board);
        print(board);
        game = checkgameover(board);
    }else if ((key == "d") or (key == "D")){
        moveright(board);
        mergeright(board);
        place_rand(board);
        print(board); 
        game = checkgameover(board);
    }else if ((key == "q") or (key == "Q")){
        game = false;
    }else {
 
    }
    }

cout << "Game Over" << endl;

}

// Play Function ends


/* checkgameover
 * First check if there is any empty space
 * if none, then check if any neighboring
 * number can combine. 
 */
bool checkgameover(int board[4]) {
int i = 0;
int t = 0;
while (i <= 3){
    if (board[i] == 0) {
        i++;
        t++;
    }else {
        i++;
    }
}
i = 0;
if (t == 0){
    while (i < 3) {
        if (board[i] == board[i + 1]){
            return true;
        } else {
            i++;
        }}        
    return false;
} else {
    return true;
}}

/* print
 * prints the gameboard
 */
void print(int board[4]) {

int i = 0;
while (i < 4){
    if (board[i] == 0){
        string empty = "-";
        print_padded_string(empty);
        i++;
    }else {
        print_padded_string(int2string (board[i]));
        i++;
    }
}
cout << endl;

}

/* moveleft
 * move all the numbers to the left, 
 * without combining any number.
 */
void moveleft(int board[4]){
    int i = 1;
    while(i <= 3) {
        if (board[i] != 0){
            int t;
            t = i;
            while (t > 0) {
                if (board[t - 1] == 0){
                    board[t - 1] = board[t];
                    board[t] = 0;
                    t--;
                } else{ 
                    t--;
                }           
            }
            i++;
        } else {
            i++;
            }
            }
}
/* mergeleft
 * to use after moveleft
 * check from the left if any number to
 * its right can be combined
 * if so, combine them and change the
 * one combined to zero
 * calls moveleft again
 * but move one space forward
 * so it won't add one number twice
 */
void mergeleft(int board[4]){
    bool mergeornot;
    int i = 0;
    while(i <= 2) {       
        mergeornot = checkright(board, i);
        if (mergeornot == true) {
            board[i] = 2 * board[i];
            board[i + 1] = 0;
            moveleft(board);
            i++;
        } else { 
            i++;
        
        }
    }
}             
/* moveright
 * same as moveleft
 * but move to the right side
 */
void moveright(int board[4]) {
    int i = 2;
    while(i >= 0) {
        if (board[i] != 0){
            int t;
            t = i;
            while (t < 3) {
                if (board[t + 1] == 0){
                    board[t + 1] = board[t];
                    board[t] = 0;
                    t++;
                } else{ 
                    t++;
                }           
            }
            i--;
        } else {
            i--;
            }
            }
}
/* mergeright
 * same as merge left, 
 * but merge to right.
 */
void mergeright(int board[4]) {        
    bool mergeornot;
    int i = 3;
    while(i >= 1) {       
        mergeornot = checkleft(board, i);
        if (mergeornot == true) {
            board[i] = 2 * board[i];
            board[i - 1] = 0;
            moveright(board);
            i--;
        } else { 
            i--;
        
        }
    }
}

/* checkright
 * check if a number to the right can 
 * be combined with the current number
 */
bool checkright(int array[4], int n){
if (n < 3){
    if (array[n + 1] == array[n]){
        return true;
    } else {
        return false;
    }
} else {
    return false;
}
}

/* checkleft
 * same as checkright
 * but check the number to the left
 */
bool checkleft(int array[4], int n){
if (n > 0){ 
    if (array[n - 1] == array[n]){
        return true;
    } else {
        return false;
    }
} else {
    return false;
}
}

    
/* place_rand
 * First call checkgameover to 
 * make sure there is enough space or that
 * the player can still make a move
 * Place the rand # in a random empty location
 */
void place_rand(int board[4]){
int a;
a = rand4();
int g;
g = generate_new();
bool game;
game = checkgameover(board);
if (game == true){
    if (board[a] == 0){
        board[a] = g;
    } else {
        place_rand(board);
    } 
} else{
    
}
}


/* rand4
 * Generate a random number from 0 to 3
 */
int rand4() {
int a;
a = rand() % 4;
return a;
}

/* generate_new
 * First randomly generate a number from 
 * 0 to 9 and if the number is smaller than 9
 * return 2, because it's probability is 90%.
 * If it's 9, then 4 is returned. 
 */
int generate_new() {
int prob;
prob = rand() % 10;
    if (prob < 9){
        return 2;
    } else{
        return 4;
    }
}
/* string2int
 * Convert a string to an int. Returns the int form of the given string.
 * Throw logic error if the string is not numerical. 
 */
int string2int(string s) {
    stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
        throw logic_error("ERROR: " + s + " is not a numerical value");
    return result;
}

/* Converts an int to string.
 * Returns the string form of the given int
 */
string int2string(int num) {
    string result;
    ostringstream oss;
    oss << num;
    result = oss.str();
    return result;
}
/* Print a string (persumably an int in the form of a string) with 
 * right paddings of up to 5 spaces
 */
void print_padded_string(string s) {
    printf("%-6s", s.c_str());
}

