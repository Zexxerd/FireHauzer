// Program Name: FIREHAUZ
// Author(s): SomeCoolGuy
// Description: FireHauzer: Shooter RPG.

/* Keep these headers */
#include <tice.h>

/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#include <graphx.h>
#include <debug.h>

void print_CharWrappedString(const char *string,int xmin,int xmax) {
    /*string: string to be printed
     xmin: leftmost x boundary.
     xmax: rightmost x boundary. Does not function like "width".
     
     Note: assumes text height is 8.
     */
    int x = gfx_GetTextX(), y = gfx_GetTextY();
    int curRowLen = 0;
    //unsigned int length = gfx_GetStringWidth(string);
    char * c = string;
    while (*c != '\0') {
        gfx_PrintChar(*(c++));
        x += curRowLen += gfx_GetCharWidth(*c);
        if (curRowLen > xmax) {
            x = xmin;
            curRowLen = 0;
            y += 8;
        }
        gfx_SetTextXY(x,y);
        gfx_BlitBuffer();
    }
}

#define print_CharWrappedStringXY(string,xmin,xmax,x,y) \
gfx_SetTextXY(x,y) \
print_WordWrappedString(string,xmin,xmax)
