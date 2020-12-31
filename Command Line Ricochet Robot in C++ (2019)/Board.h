/* Qing Zhang
 * Comp 15
 * Proj 1
 * Board.h
 */


#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>

using namespace std;

const int width = 15;
const int height = 15;

class Board
{
public:
    Board();
    Board(char n, int row, int col);
    void Read_In(char n, int row, int col);
    void Set_Robot(char n);
    int get_height();
    int get_width();
    void Print();
    char get_char(int row, int col);
    int get_row();
    int get_col();
    void change_R(int row, int col);
private:
    char cells[height][width];
    int R_row;
    int R_col;
    char Robot;
};

#endif
