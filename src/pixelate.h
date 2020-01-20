#include <stdio.h>
#include <stdlib.h>

#include <graphx.h>

//Pixelates a sprite in place.
void pixelate(gfx_sprite_t * sprite,size_t pixel_size) {
    //column per row
    int row,col,sect_row,sect_col;
    //gfx_sprite_t * temp = gfx_MallocSprite(sprite->width,sprite->height);
    //if (temp == NULL) exit(1); //fatal error //return NULL;
    if (pixel_size == 0) return;
    for (row = 0;row < sprite->height;row += pixel_size + 1)
        for (col = 0;col < sprite->width;col += pixel_size + 1)
            for (sect_row = 0;sect_row <= pixel_size;sect_row++)
                for (sect_col = 0;sect_col <= pixel_size;sect_col++)
                    if (!(row + sect_row > sprite->height || col + sect_col > sprite->width))
                        sprite->data[(sprite->width * (row + sect_row)) + col + sect_col] = sprite->data[(sprite->width * row) + col];
    //return temp;
}
//Returns a pixelated version of the sprite.
//This function creates new memory, so use pixelate() if you think your sprite is too big.
gfx_sprite_t * pixelated(gfx_sprite_t * sprite,size_t pixel_size) {
    //column per row
    int row,col,sect_row,sect_col;
    gfx_sprite_t * temp = gfx_MallocSprite(sprite->width,sprite->height);
    if (temp == NULL) exit(1); //fatal error //return NULL;
    if (pixel_size == 0) return sprite;
    for (row = 0;row < sprite->height;row += pixel_size + 1)
        for (col = 0;col < sprite->width;col += pixel_size + 1)
            for (sect_row = 0;sect_row <= pixel_size;sect_row++)
                for (sect_col = 0;sect_col <= pixel_size;sect_col++)
                    if (!(row + sect_row > sprite->height || col + sect_col > sprite->width))
                        sprite->data[(sprite->width * (row + sect_row)) + col + sect_col] = sprite->data[(sprite->width * row) + col];
    return temp;
}
