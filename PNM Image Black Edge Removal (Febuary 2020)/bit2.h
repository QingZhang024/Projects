/* bit2.h
 * by Qing Zhang, Camille Andersen 2/4/20
 * HW 2
 *
 * Interface and Function Contract for Bit2
 */

#include <stdbool.h>
#include "bit.h"
#include "bit2_struct.h"

#ifndef BIT2_H

typedef struct Bit2_T Bit2_T;


/* Creates new Bit2_T which is a Bit_T that stores Bit_T. 
 * It takes the 2 dimension of the 2-D array.
 * The dimensions cannot be negative. It returns the
 * newly created Bit2_T. 
 */
Bit2_T Bit2_new(const int width, const int height);

/* Takes in an Bit2_T and return the width of the 2-D array. 
 * The width represents the length of each Bit_T stored. 
 * It should never return negative. 
 */
int Bit2_width(Bit2_T Bit2);

/* Takes in an Bit2_T and return the height of the 2-D array. 
 * The height represents the number of Bit_T stored which is
 * the number of elements in the main Bit_T. 
 * It should never return negative. 
 */
int Bit2_height(Bit2_T Bit2);

/* Sets the element at the given row and col, and change the 
 * value at the location to the new value given. Returns
 * the old value. The row, col, and value all cannot be negative. 
 * The value given must be either zero or one. 
 * The row and col also cannot exceed the current width and height. 
 * Always return 0 or 1. 
 */
int Bit2_put(Bit2_T Bit2, int col, int row, const int value);

/* Returns the value stored at the row and col specified. 
 * The row and col cannot exceed the current width and height. 
 * Always return 0 or 1. 
 */
int Bit2_get(Bit2_T Bit2, int col, int row);

/* Go through the 2-D array and applied the given function to each element. 
 * Row indices vary more rapidly than Column indices. 
 */
void Bit2_map_col_major(Bit2_T Bit2, 
        void Apply(int col, int row, Bit2_T Bit2, int p1, void* p2), void* p3);

/* Go through the 2-D array and applied the given function to each element. 
 * Column indices vary more rapidly than Row indices. 
 */
void Bit2_map_row_major(Bit2_T Bit2, 
        void Apply(int col, int row, Bit2_T Bit2, int p1, void* p2), void* p3);

/* Free the space allocated by the structure. Cannot pass in NULL. 
 */
void Bit2_free(Bit2_T* Bit2);


#endif