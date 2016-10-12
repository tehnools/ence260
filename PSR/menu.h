/*menu.h
 * Author: N.Soong
 * Date:10-Oct-2016
 * Header File for menu.c
 * */

//Guard
#ifndef MENU_H
#define MENU_H

//Included modules
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "pacer.h"
#include "navswitch.h"
#include "task.h"


//Magic Numbers
#define PACER_RATE 500
#define MESSAGE_RATE 20
#define LOOP_RATE 500


//will change this to recieve 1 or 2 so winning player can be displayed
void end_screen(uint8_t);

uint8_t start_screen(void);

uint8_t result_screen(uint8_t win);

#endif
