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
    char ID;
    int room;
    block dim;
} passage;
typedef struct {
    uint24_t flags;
    int width,height;
    int camera_bound_width,camera_bound_height;
    block * floor;
    block * hazards;
    passage * exits;
} room;
typedef struct {
    uint24_t flags;
    room * rooms;
} level;



