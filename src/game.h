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

#include "entity.h"
#include "items.h"

typedef struct {
    int health;
    int money;
    uint8_t cur_item;
    uint8_t cur_weapon;
    uint16_t amm;
    entity * objects;
} game;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} block;

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
} bound_block; //boundaries instead of a width and height.

typedef struct {
    char ID;
    int room;
    block dim;
} passage;
typedef struct {
    uint24_t flags;
    int width,height; //independent of camera.
    boundary_block camera_bounds; //typically independant of room boundaries
    block * floor;
    block * hazards;
    passage * exits;
} room;
typedef struct {
    uint24_t flags;
    room * rooms;
} level;

block bounds_to_block(boundary_block * b);
boundary_block block_to_bounds(boundary_block * b);
