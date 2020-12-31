
#include <iostream>
#include <fstream>
#include <sstream>
#include "Board.h"
#include "Tree.h"

using namespace std;

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



void testConstructor(Tree *myTree)
{
    cout << "*** Testing Constructor***\n";
    myTree -> Print();
       
    cout << "*** Testing Copy Constructor ***\n";
    Tree myTree2(*myTree);
    myTree2.Print();

    cout << "*** Testing Assignment Operator ***\n";
    Tree myTree3;
    myTree3 = myTree2;
    myTree3.Print();

    cout << "*** Testing Destructor ***\n";
//test by running valgrind
    cout << "Passed";
    
}

void testInteractive(Tree *myTree)
{
    
    cout << "*** Testing Interactive Mode Commands ***\n";
    myTree -> Print();

    cout << "Move North\n";
    myTree -> Move_North();
    myTree -> Print();

    cout << "Move West\n";
    myTree -> Move_West(); 
    myTree -> Print();

    cout << "Move South\n";
    myTree -> Move_South(); 
    myTree -> Print();

    cout << "Move East\n";
    myTree -> Move_East(); 
    myTree -> Print();

}

void testAuto(Tree *myTree)
{
    cout << "*** Testing Auto Mode ***\n";
    myTree -> AutoMode();

    cout << "*** Testing Complicated Copy Constructor ***\n";
    Tree myTree2(*myTree);
    cout << "Passed\n";
    cout << "*** Testing Complicated Assignment Operator ***\n";
    Tree myTree3;
    cout << "Passed\n";
    myTree3 = myTree2;

}

int main(int argc, char *argv[])
{
    if (argc == 2){
        Tree myTree('@', 5, 5);
        read_board(argv[1], &myTree);
        testConstructor(&myTree);
        testInteractive(&myTree);
        testAuto(&myTree);
    }
    return 0;

}
