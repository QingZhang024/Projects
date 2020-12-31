
#include <iostream>
#include <stringstream>
#include "Board.h"
#include "Tree.h"


using namespace std;

/* Constructor 
 * Parameters: None
 * Return: None
 * Description: Creates a Tree with empty Start.
 */
Tree::Tree()
{
    Start = createNode();
    Finished = false;
}

/* Parametered Constructor
 * Parameters: char n, int row, int col
 * Return: None
 * Description: Creates a Tree with given robot symbol and location.
 */
Tree::Tree(char n, int row, int col)
{
    myBoard.Set_Robot(n);
    myBoard.change_R(2 * (row - 1), 2 * (col - 1));
    Start = createNode();
    Finished = false;
    Start -> row = 2 * (row - 1);
    Start -> col = 2 * (col - 1);
}

/* Copy Constructor 
 * Parameters: const Tree &copy
 * Return: None
 * Description: Creates a deep copy of a given tree. 
 */
Tree::Tree(const Tree &copy)
{
    myBoard = copy.myBoard;
    Finished = copy.Finished;
    Start = createNode();
    Copy(Start, copy.Start);   
} 


/* Assignment Operator
 * Parameters: const Tree &copy
 * Return: None
 * Description: Change a tree by deep copying a given tree. 
 */
Tree &Tree::operator=(const Tree &copy)
{
    
    myBoard = copy.myBoard;
    Finished = copy.Finished;
    Copy(Start, copy.Start);  
    return *this;

}

/* Destructor
 * Parameters: None
 * Return: None
 * Description: Deletes all the Nodes in the tree, calls a recursive helper. 
 */
Tree::~Tree()
{
    Delete(Start);
}

/* Function: Add_to_Board
 * Parameters: string line, int row
 * Return: None
 * Description: Given a line and row number, store the line in the 2D char
 * array of myBoard. 
 */
void Tree::Add_to_Board(string line, int row)
{
    stringstream ss;
    ss.str(line);
    for (int i = 0; i < myBoard.get_width(); i++){
        char n;
        ss >> n;
        myBoard.Read_In(n, row, i);
    }
}

/* Function: height
 * Parameters: None
 * Return: int
 * Description: Return the const height of the board. 
 */
int Tree::height()
{
    return myBoard.get_height();
}

/* Function: AutoMode
 * Parameters: None
 * Return: None
 * Description: Starts Auto Mode, call the recursive Tree_Run function to 
 * build the Node Tree. Print No Solution if after the build, no solution 
 * was found.  
 */   
void Tree::AutoMode()
{
    Start -> path = "";
    Tree_Run(Start, 0);
    if (Finished == false)
        cout << "No solution\n";
}

/* Function: Tree_Run
 * Parameters: Node *current, int move
 * Return: None
 * Description: Recursively add nodes to the four node direction pointers, 
 * stop when a solution is found. 
 */
void Tree::Tree_Run(Node *current, int move)
{
    if ((move == MAX_MOVE) or (current == nullptr))
        return;
    if (Finished == true){
        return;
    } else {
        North_Auto(current);
        Tree_Run(current -> north, move + 1);
        if (Finished == false){
            East_Auto(current);
            Tree_Run(current -> east, move + 1);
        }
        if (Finished == false){
            South_Auto(current);
            Tree_Run(current -> south, move + 1);
        }
        if (Finished == false){
            West_Auto(current);
            Tree_Run(current -> west, move + 1);
        }
    }
}        
/* Function: createNode
 * Parameters: None
 * Return: Node *
 * Description: Create an initialized Node, with nullptr for all directions.
 */

Node *Tree::createNode()
{
    Node *temp = new Node;
    temp -> north = nullptr;
    temp -> south = nullptr;
    temp -> east = nullptr;
    temp -> west = nullptr;
    temp -> row = 0;
    temp -> col = 0;
    temp -> path = "";
    return temp;

}

/* Function: Move_North
 * Parameters: None
 * Return: bool
 * Description: Function for Interactive Mode, moves the robot north. Return
 * true if found target. 
 */
bool Tree::Move_North()
{
    int row = myBoard.get_row();
    int col = myBoard.get_col();
    if (row != 0){
        char n = myBoard.get_char(row - 1, col);
        if (n == '-'){
            return false;
        }else if (n == '*'){
            myBoard.change_R(row - 1, col);
            return true;
        }
        for (int i = row; i > 0; i--){
            char t = myBoard.get_char(i - 1, col);
            if (t == '-'){
                myBoard.change_R(i, col);
                return false;
            }else if (t == '*'){
                myBoard.change_R(i - 1, col);
                return true;
            }
        }
        myBoard.change_R(0, col);
        return false;            
    } else {
        return false;
    }
}

/* Function: North_Auto
 * Parameters: Node *prev
 * Return: None
 * Description: Checks the north direction of the robot, create a node with 
 * information according to the situation. If target is found, update Finished.
 */
void Tree::North_Auto(Node *prev)
{
    int row = prev -> row;
    int col = prev -> col;
    if (row == 0){
    }else {
        if (myBoard.get_char(row - 1, col) == '-'){
        }else {
            Node *north = createNode();
            north -> col = col;
            north -> path = prev -> path + " N -> ";
            for (int i = row; i > 0; i--){
                char t = myBoard.get_char(i - 1, col);
                if (t == '-'){
                    north -> row = i;
                    prev -> north = north;
                    return;
                }else if (t == '*'){
                    cout << north -> path + " Found the target!\n";
                    delete north;
                    Finished = true;
                    return;
                }
            }
            north -> row = 0;
            prev -> north = north;
        }   
    }       
}

/* Function: Move_South
 * Parameters: None
 * Return: bool
 * Description: Function for Interactive Mode, moves the robot south. Return
 * true if found target. 
 */
bool Tree::Move_South()
{
    int row = myBoard.get_row();
    int col = myBoard.get_col();
    if (row != myBoard.get_height() - 1){
        char n = myBoard.get_char(row + 1, col);
        if (n == '-'){
            return false;
        }else if (n == '*'){
            myBoard.change_R(row + 1, col);
            return true;
        }
        for (int i = row; i < myBoard.get_height() - 1; i++){
            char t = myBoard.get_char(i + 1, col);
            if (t == '-'){
                myBoard.change_R(i, col);
                return false;
            }else if (t == '*'){
                myBoard.change_R(i + 1, col);
                return true;
            }
        }
        myBoard.change_R(myBoard.get_height() - 1, col);
        return false;            
    } else {
        return false;
    }   
}
/* Function: South_Auto
 * Parameters: Node *prev
 * Return: None
 * Description: Checks the south direction of the robot, create a node with 
 * information according to the situation. If target is found, update Finished.
 */
void Tree::South_Auto(Node *prev)
{
    int row = prev -> row;
    int col = prev -> col;
    if (row == myBoard.get_height() - 1){
    }else {
        char n = myBoard.get_char(row + 1, col);
        if (n == '-'){
        }else{ 
            Node *south = createNode();
            south -> col = col;
            south -> path = prev -> path + " S -> ";
            for (int i = row; i < myBoard.get_height() - 1; i++){
                char t = myBoard.get_char(i + 1, col);
                if (t == '-'){
                    south -> row = i;
                    prev -> south = south;
                    return;
                }else if (t == '*'){
                    cout << south -> path + " Found the target!\n";
                    delete south;
                    Finished = true;
                    return;
                }
            }
            south -> row = myBoard.get_height() - 1;
            prev -> south = south;
        }   
    }       
}

/* Function: Move_West
 * Parameters: None
 * Return: bool
 * Description: Function for Interactive Mode, moves the robot west. Return
 * true if found target. 
 */
bool Tree::Move_West()
{
    int row = myBoard.get_row();
    int col = myBoard.get_col();
    if (col != 0){
        char n = myBoard.get_char(row, col - 1);
        if (n == '|'){
            return false;
        }else if (n == '*'){
            myBoard.change_R(row, col - 1);
            return true;
        }
        for (int i = col; i > 0; i--){
            char t = myBoard.get_char(row, i - 1);
            if (t == '|'){
                myBoard.change_R(row, i);
                return false;
            }else if (t == '*'){
                myBoard.change_R(row, i - 1);
                return true;
            }
        }
        myBoard.change_R(row, 0);
        return false;            
    } else {
        return false;
    }    
}
/* Function: West_Auto
 * Parameters: Node *prev
 * Return: None
 * Description: Checks the west direction of the robot, create a node with 
 * information according to the situation. If target is found, update Finished.
 */
void Tree::West_Auto(Node *prev)
{
    int row = prev -> row;
    int col = prev -> col;
    if (col == 0){
    }else {
        char n = myBoard.get_char(row, col - 1);
        if (n == '|'){
        }else {
            Node *west = createNode();
            west -> row = row;
            west -> path = prev -> path + " W -> ";
            for (int i = col; i > 0; i--){
                char t = myBoard.get_char(row, i - 1);
                if (t == '|'){
                    west -> col = i;
                    prev -> west = west;
                    return;
                }else if (t == '*'){
                    cout << west -> path + " Found the target!\n";
                    delete west;
                    return;
                }
            }
            west -> col = 0;
            prev -> west = west; 
        }
    }       
}

/* Function: Move_East
 * Parameters: None
 * Return: bool
 * Description: Function for Interactive Mode, moves the robot east. Return
 * true if found target. 
 */
bool Tree::Move_East()
{
    int row = myBoard.get_row();
    int col = myBoard.get_col();
    if (col != myBoard.get_width() - 1){
        char n = myBoard.get_char(row, col + 1);
        if (n == '|'){
            return false;
        }else if (n == '*'){
            myBoard.change_R(row, col + 1);
            return true;
        }
        for (int i = col; i < myBoard.get_width() - 1; i++){
            char t = myBoard.get_char(row, i + 1);
            if (t == '|'){
                myBoard.change_R(row, i);
                return false;
            }else if (t == '*'){
                myBoard.change_R(row, i + 1);
                return true;
            }
        }
        myBoard.change_R(row, myBoard.get_width() - 1);
        return false;            
    } else {
        return false;
    }  
}
/* Function: East_Auto
 * Parameters: Node *prev
 * Return: None
 * Description: Checks the east direction of the robot, create a node with 
 * information according to the situation. If target is found, update Finished.
 */
void Tree::East_Auto(Node *prev)
{
    int row = prev -> row;
    int col = prev -> col;
    if (col == myBoard.get_width() - 1){
    }else {
        char n = myBoard.get_char(row, col + 1);
        if (n == '|'){
        }else {
            Node *east = createNode();
            east -> row = row;
            east -> path = prev -> path + " E -> ";
            for (int i = col; i < myBoard.get_width() - 1; i++){
                char t = myBoard.get_char(row, i + 1);
                if (t == '|'){
                    east -> col = i;
                    prev -> east = east;
                    return;
                }else if (t == '*'){
                    cout << east -> path + " Found the target!\n";
                    delete east;
                    Finished = true;
                    return;
                }
            }
            east -> col = myBoard.get_width() - 1;
            prev -> east = east;
        }
    }       
}

/* Function: Print
 * Parameters: None
 * Return: None
 * Description: Prints the board.
 */
void Tree::Print()
{
    cout << endl;
    myBoard.Print();
    cout << endl;
}

/* Function: Copy
 * Parameters: Node *current, Node *copy
 * Return: None
 * Description: Recursive helper function to create deep copy of nodes. 
 */
void Tree::Copy(Node *current, Node *copy)
{
    current -> row = copy -> row;
    current -> col = copy -> col;
    current -> path = copy -> path;
    if (copy -> north != nullptr){
        current -> north = createNode();
        Copy(current -> north, copy -> north);
    }
    if (copy -> south != nullptr){
        current -> south = createNode();
        Copy(current -> south, copy -> south);
    }
    if (copy -> west != nullptr){
        current -> west = createNode();
        Copy(current -> west, copy -> west);
    }
    if (copy -> east != nullptr){
        current -> east = createNode();
        Copy(current -> east, copy -> east);
    }
}

/* Function: Delete
 * Parameters: Node *current
 * Return: None
 * Description: Recursive helper function to delete the nodes from the leaves.
 */
void Tree::Delete(Node *current)
{ 
    if (current == nullptr){
    }else {
        if (current -> north != nullptr){
            Delete(current -> north);
        }
        if (current -> south != nullptr){
            Delete(current -> south);
        }
        if (current -> west != nullptr){
            Delete(current -> west);
        }
        if (current -> east != nullptr){
            Delete(current -> east);
        }
        delete current;
    }
}


