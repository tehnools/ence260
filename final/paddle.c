/** @file paddle.c
 * @author L. Richardson & N. Soong
 * @date October 2016
 * @brief paddle module for pong
 * */

#include "paddle.h"
#include "system.h"
#include "tinygl.h"
#include "led.h"

/** Initialise paddle
 * @param start first y coordinate of paddle
 * @param middle 2nd y coordingate of paddle
 * @param end coordinate of paddle
 * @return paddle*/
paddle_t paddle_init(tinygl_coord_t start, tinygl_coord_t middle, tinygl_coord_t end){
	
	paddle_t paddle;
	
	paddle.startCo = start;
	paddle.midCo = middle;
	paddle.endCo = end;
	
	paddle.start = tinygl_point (4, start);
	paddle.middle = tinygl_point (4, middle);
	paddle.end = tinygl_point (4, end);
	return paddle;
}

/** Draws a line on the screen corresponding to the position the paddle should be in
 * @param paddle current position of paddle*/
void drawPaddle(paddle_t paddle){
	tinygl_clear();
	tinygl_draw_line (tinygl_point (4, paddle.startCo), tinygl_point (4, paddle.endCo), 1);
}


/** Moves paddle up or down depending on navswitch input
 * @param paddle pointer to current state/position of paddle
 * @param dir the direction the paddle needs to be moved in*/
void movePaddle(paddle_t* paddle, paddle_dir_t dir){
	/* Increment coordinates of the paddle to move it up*/ 
	if(dir == DIR_UP){
		paddle->startCo = paddle->startCo+1;
		paddle->midCo = paddle->midCo+1;
		paddle->endCo = paddle->endCo+1;
		
		paddle->start = tinygl_point (4, paddle->startCo);
		paddle->middle = tinygl_point (4, paddle->midCo);
		paddle->end = tinygl_point (4, paddle->endCo);
	}
	/* Decrement coordinates of the paddle to move it down*/
	if(dir == DIR_DOWN){
		paddle->startCo = paddle->startCo-1;
		paddle->midCo = paddle->midCo-1;
		paddle->endCo = paddle->endCo-1;
		
		paddle->start = tinygl_point (4, paddle->startCo);
		paddle->middle = tinygl_point (4, paddle->midCo);
		paddle->end = tinygl_point (4, paddle->endCo);
	}
	drawPaddle(*paddle);  
	
} 



