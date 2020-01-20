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

//#include <assert.h>

#include <graphx.h>
#include <keypadc.h>
//#include <debug.h>

enum State {
    Moving = 1,
    Faster = 2,
    Hurt = 4,
    Invincible = 8,
    Immune = 16,
    Dead = 32,
};

typedef struct {
    int x;
    int y;
    int xvel;
    int yvel;
    uint8_t image; // pointer to image.
} basic_entity;

typedef struct {
    int x;
    int y;
    int xvel; //possibly use this for directions
    int yvel;
    int power;
    int health;
    char ID;
    uint8_t current_frame;
    entity_frame_set frames;
} entity;

typedef struct {
    uint8_t * frames;
} frame_set;

typedef struct { //probably going for 30fps here...
    frame_set idle;
    frame_set walking;
    frame_set running;
    frame_set hurt;
    frame_set dying;
} enitiy_frame_set;

entity * entity_list; //used for NPCs, enemies, projectiles, and the player.

void moveEntity(entity *e,uint8_t frames,int x,int y);
void renderEntity(entity *e);
