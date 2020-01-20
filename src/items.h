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

#include "entity.h"

typedef struct {
    gfx_sprite_t * image;
    int flag;
    char * description;
} item;
