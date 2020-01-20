#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include <graphx.h>


struct menu_branch {
    char * title;                  //Title
    uint8_t flags;                 //8 bits used for flags.
    unsigned int position;         //Probably for menu cursor?
    struct menu_branch ** options; //Options. Can be NULL.
    /*Flags:
     1<<0: Menu (opens another menu when selected)
     1<<1: Item (Does something when selected)
     1<<2: Selectable?
     1<<3: Selected?
     */
};
struct item {
    char * title;
    bool selected;
};
typedef struct menu_branch * Menu; //This should technically work...
typedef struct menu_branch * Item; //Same as above

int menu_choice;
char ** menu_options;

//Usage: initMenu(title,option_list,default_option_number,number_of_options);
Menu initMenu(char * title,uint8_t flags,Item * options,unsigned int default_option,size_t number_of_items) {
    Menu temp;
    temp->title = title;
    temp->options = (Item *) malloc(number_of_items * sizeof(Menu *));
    temp->position = default_option;
    return temp;
}
