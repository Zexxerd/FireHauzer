// convpng v7.1
// this file contains all the graphics sources for easy inclusion in a project
#ifndef __rletimages__
#define __rletimages__
#include <stdint.h>

#define flogo_width 255
#define flogo_height 22
#define flogo_size 5276
extern uint8_t flogo_data[5276];
#define flogo ((gfx_rletsprite_t*)flogo_data)
#define sizeof_rletimages_pal 512
extern uint16_t rletimages_pal[256];

#endif
