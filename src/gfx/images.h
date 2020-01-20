// convpng v7.1
// this file contains all the graphics sources for easy inclusion in a project
#ifndef __images__
#define __images__
#include <stdint.h>

#define images_transparent_color_index 148

#define flogo_width 255
#define flogo_height 22
#define flogo_size 5612
extern uint8_t flogo_data[5612];
#define flogo ((gfx_sprite_t*)flogo_data)
#define sizeof_images_pal 512
extern uint16_t images_pal[256];

#endif
