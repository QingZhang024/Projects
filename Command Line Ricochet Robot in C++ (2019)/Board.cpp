#include <iostream>
#include "Board.h"

using namespace std;

Board::Board()
{
    R_row = 0;
    R_col = 0;
    Robot = ' ';
}

Board::Board(char n, int row, int col)
{
    
    R_row = 2 * (row - 1);
    R_col = 2 * (col - 1);
    Robot = n;
}

void Board::Read_In(char n, int row, int col)
{
    cells[row][col] = n;
}

void Board::Set_Robot(char n)
{
    Robot = n;
}

int Board::get_height()
{
    return height;
}

int Board::get_width()
{
    return width;
}

void Board::Print()
{
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (cells[i][j] == 'O'){
                cout << ' ';
            } else if ((i == R_row) and (j == R_col)){
                cout << Robot;
            } else {
                cout << cells[i][j];
            }
        }
        cout << "\n";
    }
}

char Board::get_char(int row, int col)
{
    return cells[row][col];
}

int Board::get_row()
{
    return R_row;
}       

int Board::get_col()
{
    return R_col;
}
void Board::change_R(int row, int col)
{
    R_row = row;
    R_col = col;
}

