
#include <iostream>
#include <fstream>
#include <stringstream>
#include "Board.h"
#include "Tree.h"


using namespace std;

void runInteractive(Tree *myTree);
bool Move(bool found, char d, Tree *myTree);
void read_board(char *argv, Tree *myTree);

int main(int argc, char *argv[])
{
    if (argc != 2){
        cerr << "Usage: Rico_Robot BoardFile\n";
        return -1;
    }
    cout << "Welcome to Ricocheting Robots!\n";
    cout << "Enter Robot symbol (1 Char): ";
    char R;
    cin >> R;
    int row, col;
    cout << "Enter starting row: ";
    cin >> row;
    cout << "Enter starting col: ";
    cin >> col;
    string mode;
    cout << "Please enter AUTO for automatic solver and ";
    cout << "INTER for an interactive game mode!\n";
    cin >> mode;
    if ((col < 1) or (col > 8) or (row < 1) or (row > 8)){
        cout << "Invalid Index";
        return -1;
    }
    Tree myTree(R, row, col);
    read_board(argv[1], &myTree);
    if (mode == "INTER")
        runInteractive(&myTree);
    else if (mode == "AUTO")
        myTree.AutoMode();
    return 0;
}

/* Function: runInteractive
 * Parameters: Tree *myTree
 * Return: None
 * Description: Interactive mode of the game. Moves the robot according to
 * the command given. 
 */
void runInteractive(Tree *myTree){    
    myTree -> Print();
    char d;
    cin >> d;
    cout << "move: " << d;
    bool found = false;
    while ((d != 'q') and (found != true)){
        if ((d == 'w') or (d == 'a') or (d == 's') or (d == 'd') or (d == 'q'))
            found = Move(found, d, myTree);
        else {
            cout << "INVALID MOVE\n";
            break;
        }
        myTree -> Print();
        if (found != true){
            cin >> d;
            cout << "move: " << d;
        }
    }
    if (found == true){
        cout << "Congratulations!! You Win!!!!\n";
    }else {
        cout << " -> Quitting...";
    }           
}

/* Function: Move
 * Parameters: bool found, char d, Tree *myTree
 * Return: bool
 * Description: Helper function for Interactive mode, move robot with command. 
 */
bool Move(bool found, char d, Tree *myTree)
{
    if (d == 'w'){
        cout << " -> moving north\n";
        found = myTree -> Move_North();
    }else if (d == 'a'){
        cout << " -> moving west\n";
        found = myTree -> Move_West();
    }else if (d == 's'){
        cout << " -> moving south\n";
        found = myTree -> Move_South();
    }else if (d == 'd'){
        cout << " -> moving east\n";
        found = myTree -> Move_East();
    }
    return found;
 
}

/* Function: read_board
 * Parameters: char *argv, Tree *myTree
 * Return: None
 * Description: Reads in the file given and store the data in the board. 
 */   
void read_board(char *argv, Tree *myTree){
    string boardfile = argv;
    ifstream infile;
    infile.open(boardfile);
    if (!infile){
        cerr << "Error: could not open file " << boardfile;
        return;
    }
    string this_row;
    for (int i = 0; i < myTree -> height(); i++){   
        getline(infile, this_row);
        myTree -> Add_to_Board(this_row, i);
    }
    infile.close();
}         

