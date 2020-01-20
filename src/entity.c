//Subprogram!

/* Keep these headers */
#include <tice.h>

/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#include <graphx.h>
#include <keypadc.h>

void moveEntity(entity *e,uint8_t advance_frames,int x,int y) {
    e.current_frames += 1;
}
