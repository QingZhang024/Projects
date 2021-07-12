/* bit2.c
 * by Qing Zhang, Camille Andersen 2/4/20
 * HW 2
 *
 * Function Definitions for Bit2
 */
#include <stdio.h>
#include <stdlib.h>
#include "bit2.h"
#include "bit.h"
#include "assert.h"

Bit2_T Bit2_new(const int width, const int height)
{
    if ((height < 0) || (width < 0)){
        fprintf(stderr, "Row or Col is negative!");
        exit(EXIT_FAILURE);
    }
    Bit2_T TwoD;
    TwoD.mainBit = Bit_new(width * height);
    TwoD.height = height;
    TwoD.width = width;

    return TwoD;
}

int Bit2_width(Bit2_T Bit2)
{
    return Bit2.width;
}

int Bit2_height(Bit2_T Bit2)
{
    return Bit2.height;
}

int Bit2_put(Bit2_T Bit2, int col, int row, const int value)
{
    return Bit_put(Bit2.mainBit, row * Bit2.width + col, value);
}

int Bit2_get(Bit2_T Bit2, int col, int row)
{
    return Bit_get(Bit2.mainBit, row * Bit2.width + col);
}

void Bit2_map_col_major(Bit2_T Bit2, 
        void Apply(int col, int row, Bit2_T array, int p1, void* p2), 
                                                            void* p3)
{
    int w, h;
    for (w = 0; w < Bit2.width; w++){
        for (h = 0; h < Bit2.height; h++){
            Apply(w, h, Bit2, Bit2_get(Bit2, w, h), p3);
        }
    }
}

void Bit2_map_row_major(Bit2_T Bit2, 
        void Apply(int col, int row, Bit2_T array, int p1, void* p2), 
                                                            void* p3)
{
    int w, h;
    for (h = 0; h < Bit2.height; h++){
        for (w = 0; w < Bit2.width; w++){
            Apply(w, h, Bit2, Bit2_get(Bit2, w, h), p3);
        }
    }
}

void Bit2_free(Bit2_T* Bit2)
{
    assert(Bit2);
    Bit_free(&(Bit2 -> mainBit));
}
