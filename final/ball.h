/** @file ball.h
 * @author L. Richardson & N. Soong
 * @date October 2016
 * @brief personalized bouncing ball module, building on M.P Hayes' boing.h/boing.c
 * */
#ifndef BALL_H
#define BALL_H

#include "tinygl.h"
#include "boing.h"
#include "paddle.h"

typedef struct ball_state_t{ 
	boing_state_t state;
	uint8_t game_state;
	}ball_state_t;

/** Update the direction of the ball when it hits paddle
 * @param ball the state of the current ball
 * @param paddle, the state of the current paddle
 * @return new state of the ball
 * */
boing_state_t hit_paddle(boing_state_t ball, paddle_t paddle);

/** Initialise state of ball
 * @param state the state of the ball to be created as a boing_state_t
 * @return ball */
ball_state_t ball_init(boing_state_t ball_state, uint8_t game);

#endif
