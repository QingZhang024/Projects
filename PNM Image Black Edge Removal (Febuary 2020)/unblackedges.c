/* unblackedges.c
 * by Qing Zhang, Camille Andersen 2/4/20
 * HW 2
 *
 * Remove the black borders in pbm files.
 * Removes any black areas that touches the border. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <pnmrdr.h>
#include <stdbool.h>
#include "assert.h"
#include "seq.h"
#include "bit2.h"
#define T Pnmrdr_T

typedef struct Coordinates Coordinates;


void Read_in_image(T, Bit2_T *);
void Remove_black_edges(Bit2_T *);
void Check_neighbors(Seq_T *, Bit2_T *, int, int);
void Create_coordinates(Seq_T *, Bit2_T *, int, int);
void Dequeue(Seq_T *, Bit2_T *);
void Print(Bit2_T *);
void Print_index(int, int, Bit2_T, int, void*);


const int BLACK = 1;
const int WHITE = 0;

/* Coordinate information of pixels. */
struct Coordinates{
    int col;
    int row;
};

int main(int argc, char *argv[])
{

    FILE *fp;

    assert(argc <= 2);

    if (argc == 1) {
        fp = stdin;
    }
    else {
        fp = fopen(argv[1], "r");
        assert(fp);
        
    }

    T image = Pnmrdr_new(fp);  
    Pnmrdr_mapdata image_info = Pnmrdr_data(image);


    Bit2_T board = Bit2_new(image_info.width, image_info.height);

    Read_in_image(image, &board);
    Remove_black_edges(&board);
    Print(&board);
    Pnmrdr_free(&image);
    Bit2_free(&board);
    fclose(fp);

    return EXIT_SUCCESS;

}

/* Function: Read_in_image
 * Parameters: Pnmrdr_T image, Bit2_T *board
 * Return: None
 * Description: Read in the image with pnmrdr and import the pixels 
 *              into our Bit2_T board.
 */

void Read_in_image(T image, Bit2_T *board)
{
    Pnmrdr_mapdata image_info = Pnmrdr_data(image);
    assert(image_info.type == Pnmrdr_bit);
    int h, w;
    unsigned temp;

    for (h = 0; h < Bit2_height(*board); h++){
        for (w = 0; w < Bit2_width(*board); w++){
            temp = Pnmrdr_get(image);
            Bit2_put(*board, w, h, temp);
        }
    }
}

/* Function: Remove_black_edges
 * Parameters: Bit2_T *board
 * Return: None
 * Description: Go through all four borders and check if a pixel is black,
 *              if it is, call the Check_current function by giving information
 *              of the current pixel. 
 */

void Remove_black_edges(Bit2_T *board)
{
    int w, h;
    Seq_T Queue = Seq_new(500);

    for (w = 0; w < Bit2_width(*board); w++){
        Create_coordinates(&Queue, board, w, 0);
    }
    for (w = 0; w < Bit2_width(*board); w++){
        Create_coordinates(&Queue, board, w, Bit2_height(*board) - 1);
    }
    for (h = 0; h < Bit2_height(*board); h++){
        Create_coordinates(&Queue, board, 0, h);
    }
    for (h = 0; h < Bit2_height(*board); h++){
        Create_coordinates(&Queue, board, Bit2_width(*board) - 1, h);

    }
    Dequeue(&Queue, board);

    Seq_free(&Queue);

}


/* Function: Check_neighbors
 * Parameters: Seq_T *Queue, Bit2_T *board, int col, int row
 * Return: None
 * Description: Checks the direct neighbors on all four sides of
 *              the given pixel. If any neighbor is black, create
 *              a coordinate struct of the variable and store
 *              in Queue. Call Dequeue which dequeue from the queue
 *              and add further neighbors in Queue, Dequeue stop when
 *              Queue is empty. 
 */

void Check_neighbors(Seq_T *Queue, Bit2_T *board, int col, int row)
{
    if (col - 1 >= 0){
        Create_coordinates(Queue, board, col - 1, row);
    }
    if (col + 1 < Bit2_width(*board)){
        Create_coordinates(Queue, board, col + 1, row);
    }
    if (row - 1 >= 0){
        Create_coordinates(Queue, board, col, row - 1);
    }
    if (row + 1 < Bit2_height(*board)){
        Create_coordinates(Queue, board, col, row + 1);
    }
}

/* Function: Create_coordinates
 * Parameters: Seq_T *Queue, Bit2_T *board, int col, int row
 * Return: None
 * Description: Store the location in a coordinate object. Add
 *              the struct in the Queue. 
 */
void Create_coordinates(Seq_T *Queue, Bit2_T *board, int col, int row)
{
    if (Bit2_get(*board, col, row) == BLACK){
        Bit2_put(*board, col, row, WHITE);
        Coordinates *temp = (Coordinates *)malloc(sizeof(Coordinates));
        assert(temp);
        temp -> col = col;
        temp -> row = row;
        Seq_addhi(*Queue, temp);
    }

}

/* Function: Dequeue
 * Parameters: Seq_T *Queue, Bit2_T *board
 * Return: void
 * Description: Dequeue the first Coordinate from the Queue and check its
 *              neighbors, stop until the Queue is empty. 
 */

void Dequeue(Seq_T *Queue, Bit2_T *board)
{
    while (Seq_length(*Queue) != 0){
        Coordinates *temp = Seq_remlo(*Queue);
        Check_neighbors(Queue, board, temp -> col, temp -> row);
        free(temp);
    }
}

/* Function: Print
 * Parameters: Bit2_T *board
 * Return: None
 * Description: Print out the new file by calling Bit2_map_row_major. 
 */
void Print(Bit2_T *board)
{
    int count = 0;
    printf("P1\n");
    printf("%d %d\n", Bit2_width(*board), Bit2_height(*board));
    Bit2_map_row_major(*board, Print_index, &count);
}

/* Function: Print_index
 * Parameters: int col, int row, Bit2_T array, int p1, void* p2
 * Return: None
 * Description: Print the current pixel. p2 keeps tract of the number
 *              of character printed per line to keep the requirement
 *              that each line in pbm is 70 characters. 
 */
void Print_index(int col, int row, Bit2_T array, int p1, void* p2)
{
    int *count = p2;
    printf("%d", p1);
    (*count)++;
    if ((col == Bit2_width(array) - 1) || ((*count) == 70)){
        printf("\n");
        *count = 0;
    }
    (void)row;
}