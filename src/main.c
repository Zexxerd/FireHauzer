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
#include <keypadc.h>
#include <debug.h>

#include "pixelate.h"
#include "entity.h"
#include "print.h"
#include "gfx/images.h"

#define LOGO_WIDTH 251
#define LOGO_HEIGHT 100
/*typedef struct {
    int x;
    int y;
    int xvel;
    int yvel;
    gfx_sprite_t * image;
} entity;*/

/*Flags:
 1<<0: Opening's fade out transition starts.
 1<<1: Opening's fade out transition ended. Start Opening's fade in.
 1<<2: Opening's fade in ended. Menu Screen.
 1<<3: Choice in menu selected.
 1<<4: Whether the user's in another part of the menu or not. Set directly after 1<<3.
 */
//void turnBitOn(void * bItem,unsigned int byte);

void r_swap(int *arr,unsigned int size,int pos) {
    //swaps items in a list randomly
    int i = (pos+random()) % size;
    int temp = arr[i];
    arr[i] = arr[pos];
    arr[pos] = temp;
}

volatile int timer;
uint24_t flags;

uint8_t title_screen(void);
void main(void) {
    int res;
    gfx_Begin();
    gfx_SetDrawBuffer();
    res = title_screen();
    if (res == 1) {
        goto end;
    } else {
        gfx_SetDefaultPalette(gfx_8bpp);
        gfx_SetColor(0xFF);
        gfx_SetTextScale(2,2);
        while(!(kb_Data[6] & kb_Clear)) {
            gfx_ZeroScreen();
            gfx_PrintStringXY("You can quit now",160-gfx_GetStringWidth("You can quit now")/2,112);
            gfx_BlitBuffer();
            kb_Scan();
        }
    }
end:
    /*free(holder);
    free(menu_options);
    free(stars);
    free(temp_arr);*/
    gfx_End();
}

uint8_t title_screen(void) {
    //currently null values
    bool quittable;
    int i, j, k, l, menu_choice, nOfStars;
    entity stars[30];
    uint16_t temp_arr[255];
    //declared values
    uint8_t fadecolors[10] = {0xFF,0xBF,0x7F,0x3F,0x1E,0x1C,0x1A,0x18,0x10,0x08};
    uint8_t flogo_indexes[47] = {0x94, 0xB5, 0xDE, 0xFF, 0xD6, 0xB4, 0xB6, 0x6B, 0x6C, 0xFE, 0x95, 0xD6, 0x29, 0x4A, 0x4B, 0x49, 0x21, 0x93, 0x8C, 0x00, 0x01, 0x20, 0x41, 0x73, 0x6A, 0x8B, 0x40, 0x69, 0x61, 0x62, 0x82, 0x8A, 0x81, 0x89, 0xAA, 0xAB, 0xA2, 0xC2, 0xC1, 0xCB, 0xAC, 0xE3, 0xC3, 0xE5, 0xE6, 0xCD, 0xC5}; //unique(flogo->data,flogo->width * flogo->height);
    uint8_t transparent_index = 148;
    char menu_options[10][10];
    char str[100];
    int base_x = 25, size_x = 25;
    int base_y = 2, size_y = 2;
    int center_x = (320/2) - (flogo->width/2);
    int center_y = flogo->height/2;
    gfx_sprite_t *holder = gfx_MallocSprite(size_x,size_y),*holder2;
    gfx_SetTransparentColor(transparent_index); // it oddly always defaults to 148 when using convpng...
    //flogo_indexes = unique(flogo->data,5610);
    
intro:
    timer = 0;
    flags = 0x000000;
    //menu_options = (char **) malloc(3 * sizeof(char *));
    //backup the palette
    //gfx_SetPalette(images_pal,sizeof_images_pal,0);
    gfx_SetDefaultPalette(gfx_8bpp);
    for (i = 0;i < 256;i++) temp_arr[i] = gfx_palette[i];
    //stars
    for (i=0;i < 30;i++) {
        stars[i].x = 320;
        stars[i].y = rand()%235;
        stars[i].xvel = ((rand()%21)+5);
        stars[i].yvel = 0;
    }
    i = 0;
    while (size_x < 251 && size_y < 100) {
        gfx_FillScreen(i!=10 ? fadecolors[i++] : 0x00);
        size_x += (LOGO_WIDTH-base_x)/10;
        size_y += (LOGO_HEIGHT-base_y)/10;
        if (size_x > 251) size_x = 255;
        if (size_y > 100) size_y = 100;
        holder->width = size_x;
        holder->height = size_y;
        holder = gfx_ScaleSprite(flogo,holder);
        center_x = (320/2) - (holder->width/2);
        center_y = 120 - size_y;
        gfx_TransparentSprite_NoClip(holder,center_x,center_y);
        gfx_BlitBuffer();
        //delay((LOGO_WIDTH-size_x)/5);
    }
    quittable = 1, nOfStars = 0, i = 0, j = 255, k = 5, l = 0,menu_choice = 0;
    while (true) {
        //if (flags & 1<<1) goto menu;
        kb_Scan();
        if (j < 255 && !(flags & 1<<1)) {
            gfx_FillScreen(0x00);
            gfx_TransparentSprite_NoClip(holder,center_x,center_y);
        } else {
            gfx_FillScreen(0x00);
        }
        if (flags & 1<<2) {
            //the sprite's original dimensions will be (80,30).
            holder->width = (uint8_t) (sin(((double)timer)/40) * 45) + 80;
            if (holder->width == 0) holder->width = 1; //Displayed sprites can't have a width of 0.
            holder->height = 30;
            holder = gfx_ScaleSprite(flogo,holder);
            //pixelate(holder,rtc_Time() % 2);
            gfx_TransparentSprite_NoClip(holder,1,210);
            //free(holder); //holder = NULL;
        }
        for (i = 0;i < 30; i++) {
            gfx_SetColor(i % 2 ? 0x4A : 0xB5);
            gfx_FillCircle(stars[i].x,stars[i].y,5);
            if (i > nOfStars) { nOfStars++; break; }
            stars[i].x -= stars[i].xvel;
            if (stars[i].x < -5) {
                stars[i].x = 320;
                stars[i].y = stars[i].y = rand()%235;
                stars[i].xvel = ((rand()%21)+5);
            }
        }
        //gfx_SetTextXY(0,0);
        //gfx_SetColor(0xFF);
        //gfx_FillRectangle(0,0,24,8);
        //gfx_PrintUInt(transparent_index,3);
        if (j && !(flags & 1<<1))
            gfx_TransparentSprite_NoClip(holder,center_x,center_y);
        
        //set transition flag if [2nd] or [Enter] is pressed.
        if ((kb_Data[1] & kb_2nd || kb_Data[6] & kb_Enter) && !(flags & 1<<0)) {
            flags |= 1<<0;
        }
        //fade out transition, cuts off once j is 0
        if (flags & 1<<0 && !(flags & 1<<1) && j) {
            j -= 255/k; // 255/5 == 51, 255/10 == 25[.5]
            if (j < 0) j = 0;
            for (i = 0;i < 256;i++) {
                gfx_palette[i] = gfx_Darken(temp_arr[i],j);
            }
        }
        //activated once j is zeroed.
        if (!j && !(flags & 1<<1)) {
            flags |= 1<<1;
            gfx_FillScreen(0x00);
            gfx_BlitBuffer();
            holder->width = 80;
            holder->height = 30;
            delay(200);
        }
        //fade in transition, var j should have a value of 0 here.
        if (flags & 1<<1 && !(flags & 1<<2)) {
            j += 255/k;
            if (j > 255) j = 255;
            for (i = 0;i < 256;i++)
                gfx_palette[i] = gfx_Darken(temp_arr[i],j);
            if (j == 255) {
                for (i = 0;i < 255;i++) gfx_palette[i] = temp_arr[i];
                flags |= 1<<2;
                sprintf(menu_options[0],"Main Menu");
                sprintf(menu_options[1],"Play");
                sprintf(menu_options[2],"Help");
                sprintf(menu_options[3],"Info");
                j = (temp_arr[0xED]-temp_arr[0xA8])/10;
            }
        }
        if (flags & 1<<1 || flags & 1<<2) {
            //j is used for the color fade of the text.
            // use k to interrupt the key presses, and use menu_choice for the cursor position
            // use l for the scrolling text menus.
            gfx_SetTextTransparentColor(transparent_index);
            gfx_SetTextFGColor(0xE8);
            gfx_SetTextBGColor(transparent_index);
            gfx_SetTextScale(2,2);
            gfx_SetColor(0x40);
            //outer rectangle
            gfx_FillRectangle(40,40,240,160);
            /*Text stuff here*/
            //Shows menu title if nothing's selected, otherwise the selected menu option.
            gfx_PrintStringXY((!(flags & 1<<4) ? menu_options[0] : menu_options[menu_choice+1]),40,40);
            gfx_SetColor(0xA8);
            //inner rectangle
            gfx_FillRectangle(56,56,208,128);
            gfx_SetTextScale(3,2);
            if (flags & 1<<2) // For some reason palette index 0xFF is acting weird with gfx_Darken
                if (gfx_palette[0xFF] != 0xFFFF) gfx_palette[0xFF] = 0xFFFF;
            gfx_SetTextFGColor(0xED);
            gfx_SetTextScale(2,2);
            if (!(flags & 1<<3)) {
                //So that the cursor immediately moves after being pressed again.
                if (!(kb_Data[7] & kb_Up || kb_Data[7] & kb_Down)) k = 5;
                
                if (kb_Data[7] & kb_Up) {
                    if (k > 5) {
                        k = 0;
                        if (menu_choice - 1 < 0) menu_choice = 2;
                        else             menu_choice--;
                    }
                }
                if (kb_Data[7] & kb_Down) {
                    if (k > 5) {
                        k = 0;
                        if (menu_choice + 1 > 2) menu_choice = 0;
                        else             menu_choice++;
                    }
                }
                if (kb_Data[1] & kb_2nd || kb_Data[6] & kb_Enter) {
                    flags |= 1<<3;
                }
                k++;
            }
            if (!(flags & 1<<4)) {
                for (i = 1;i <= 3;i++) {
                    if ((flags & 1<<3 && gfx_palette[0xED] > gfx_palette[0xA8])) {
                        gfx_palette[0xED] -= j;
                        if (gfx_palette[0xED] < gfx_palette[0xA8])
                            gfx_palette[0xED] = gfx_palette[0xA8];
                    }
                    //Print the menu options, but first set the color if highlighted.
                    gfx_SetTextFGColor(i == (menu_choice + 1) && timer % 3 ? 0xFF : 0xED);
                    gfx_PrintStringXY(menu_options[i],80,56 + ((i-1) * 16));
                    if (gfx_palette[0xED] == gfx_palette[0xA8])
                        flags |= 1<<4;
                    
                }
                quittable = true;
            }
            //
            if (flags & 1<<4) {
                quittable = 0;
                gfx_palette[0xED] = temp_arr[0xED];
                if (menu_choice == 0) {
                    //Note: Use Gfx_ScaleSprite here
                    //holder = gfx_MallocSprite(160,240);
                    //holder2 = gfx_MallocSprite(160,240);
                    gfx_SetColor(0x00);
                    for (i = 240;i > 16;i -= 16) {
                        //side 1
                        holder = gfx_MallocSprite(160,i+(i==0));
                        holder2 = gfx_MallocSprite(160,i-16+(i==0));
                        holder = gfx_GetSprite(holder,0,0);
                        holder2 = gfx_ScaleSprite(holder,holder2);
                        gfx_Sprite_NoClip(holder2,0,0);
                        //side 2
                        holder = gfx_GetSprite(holder,160,0);
                        holder2 = gfx_ScaleSprite(holder,holder2);
                        gfx_Sprite_NoClip(holder2,160,0);
                        //gfx_Sprite_NoClip(holder2,160,0);
                        gfx_FillRectangle_NoClip(0,i-16,320,240-(i-16));
                        gfx_BlitBuffer();
                        free(holder);
                        free(holder2);
                    }
                    return 0; //go to game?
                }
                //Help menu
                if (menu_choice == 1) { // Help
                    if (kb_Data[7] & kb_Up) l+=3;
                    else if (kb_Data[7] & kb_Down) l-=3;
                    gfx_SetTextBGColor(0x00);
                    gfx_SetTextFGColor(0xFF);
                    gfx_SetClipRegion(56,56,264,184);
                    gfx_SetTextScale(1,1);
                    gfx_SetTextConfig(gfx_text_clip);
                    gfx_PrintStringXY("Use the arrow keys to move",56,56+l);
                    gfx_PrintStringXY("and navigate menus.",56,64+l);
                    gfx_PrintStringXY("You will find yourself using",56,72+l);
                    
                    gfx_SetTextBGColor(transparent_index);
                    
                    //every button is divided by x intervals of 36 and y intervals of 14.
                    //2nd
                    //i = gfx_GetStringWidth("2nd") + 12;
                    gfx_SetColor(0x7F);
                    gfx_FillRectangle(56,80+l,36,8 + 6);
                    gfx_PrintStringXY("2nd",56 + ((36/2) - (gfx_GetStringWidth("2nd")/2)),80 + 3 + l);
                    
                    //mode
                    gfx_SetColor(0x11);
                    gfx_FillRectangle(56+36,80+l,i,8 + 6);
                    gfx_PrintStringXY("mode",92 + ((36/2) - (gfx_GetStringWidth("mode")/2)),80 + 3 + l);
                    
                    // alpha
                    gfx_SetColor(0xCF);
                    gfx_FillRectangle(56,94+l,36,8 + 6);
                    gfx_PrintStringXY("alpha",56 + ((36/2) - (gfx_GetStringWidth("alpha")/2)),94 + 3 + l);
                    
                    //xt0n
                    gfx_SetColor(0x11);
                    gfx_FillRectangle(56+36,94+l,i,8 + 6);
                    gfx_PrintStringXY("XT0n",92 + ((36/2) - (gfx_GetStringWidth("XT0n")/2)),94 + 3 + l);
                    
                    gfx_SetTextBGColor(0x00);
                    gfx_PrintStringXY("alot. F1-F5 are used for the ",56,108+l);
                    gfx_PrintStringXY("menu and special commands.",56,116+l);
                    gfx_SetTextConfig(gfx_text_noclip);
                    gfx_SetClipRegion(0,0,320,240);
                }
                while (kb_Data[6] & kb_Clear || kb_Data[2] & kb_Alpha) {
                    l = 0;
                    flags &= ~(1<<4 | 1<<3);
                    kb_Scan();
                }
            }
        }
        gfx_BlitBuffer();
        timer++;
        if (kb_Data[6] & kb_Clear && quittable) {
            return 1; //quit
        }
    }
}

/*Other Functions*/

//These functions were modified to accomodate uint8_t variables
int search(uint8_t * array,unsigned int size,uint8_t value) {
    /*Returns position of item in array. Returns -1 on failure*/
    int counter;
    for (counter = 0;counter < size;counter++) {
        if (array[counter] == value) {
            return counter;
        }
    }
    return -1;
}
/*int * unique(int array[],unsigned int size){
 //Returns the unique values in an array.
 //I decided to directly adjust the temp pointer instead of
 //using a variable to store the current position of the next value in temp.
 int i;
 int * temp = (int *) malloc(sizeof(int) * (size + 1));
 for (i = 0;i < size; i++) {
 if (search(temp,sizeof(temp),array[i]) == -1) {
 temp[size]++;
 *temp = array[i];
 temp += sizeof(int);
 }
 }
 temp -= temp[size] * sizeof(int);
 temp = realloc(temp,sizeof(int) * temp[size]);
 return temp;
 }*/
uint8_t * unique(uint8_t * array,unsigned int size) {
    int i, new_size = 0;
    uint8_t * temp = (uint8_t *) malloc(size * sizeof(uint8_t));
    for (i = 0;i < size;i++) {
        if (search(temp,sizeof(temp)/sizeof(uint8_t),array[i]) == -1) {
            temp[new_size++] = array[i]; //set the current index of temp to the next unique value, then move right.
        }
    }
    temp = realloc(temp,new_size * sizeof(uint8_t));
    return temp;
}
