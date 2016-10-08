/** @file paddle.h
 * @author L. Richardson & N. Soong
 * @date October 2016
 * @brief paddle module for pong
 * */

#ifndef PADDLE_H
#define PADDLE_H

#include "tinygl.h"

/** Paddle movement direction options*/
typedef enum direction {DIR_UP, DIR_DOWN} paddle_dir_t;

/** Structure defining the position of the paddle*/
typedef struct paddle_t{
	tinygl_coord_t startCo;
	tinygl_coord_t midCo;
	tinygl_coord_t endCo;

	tinygl_point_t start;
	tinygl_point_t middle;
	tinygl_point_t end;
}paddle_t;

/** Initialise paddle
 * @param start first y coordinate of paddle
 * @param middle 2nd y coordingate of paddle
 * @param end coordinate of paddle
 * @return paddle*/
paddle_t paddle_init(int8_t start, int8_t middle, int8_t end);

/** Draws a line on the screen corresponding to the position the paddle should be in
 * @param paddle current position of paddle*/
void drawPaddle(paddle_t paddle);

/** Moves paddle up or down depending on navswitch input
 * @param paddle pointer to current state/position of paddle
 * @param dir the direction the paddle needs to be moved in*/
void movePaddle(paddle_t* paddle, paddle_dir_t dir);

#endif
