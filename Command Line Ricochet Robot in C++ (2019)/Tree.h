
#ifndef _TREE_H_
#define _TREE_H_

#include <string>
#include "Board.h"

using namespace std;

const int MAX_MOVE = 7;

struct Node
{
    int row;
    int col;
    string path;
    Node *north;
    Node *south;
    Node *east;
    Node *west;
};

class Tree
{
public:
    Tree();
    Tree(char n, int row, int col);
    Tree(const Tree &copy);
    Tree &operator=(const Tree &copy);
    ~Tree();
    int height();
    void Add_to_Board(string line, int row);
    void AutoMode();
    bool Move_North();
    bool Move_South();
    bool Move_East();
    bool Move_West();
    void Print();
private:
    Board myBoard;
    Node *Start;
    bool Finished;

    void Tree_Run(Node *current, int move);
    Node *createNode();
    void North_Auto(Node *prev);
    void South_Auto(Node *prev);
    void East_Auto(Node *prev);
    void West_Auto(Node *prev);
    void Copy(Node *current, Node *copy);
    void Delete(Node *current);
 

};

#endif
