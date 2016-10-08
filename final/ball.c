/** @file ball.c
 * @author L. Richardson & N. Soong
 * @date October 2016
 * @brief personalized bouncing ball module, building on M.P Hayes' boing.c/boing.h
 * */

#include "ball.h"
#include "system.h"
#include "tinygl.h"
#include "led.h"
#include "boing.h"

/** Update the direction of the ball when it hits paddle
 * @param ball the state of the current ball
 * @param paddle, the state of the current paddle
 * @return new state of the ball
 * */
boing_state_t hit_paddle(boing_state_t ball, paddle_t paddle){
	//led_set (LED1, 1);
	
	uint8_t start = paddle.startCo;
	uint8_t middle = paddle.midCo;
	uint8_t end = paddle.endCo;
	
	uint8_t ballCo = ball.pos.y;
	
	//if(ball.dir == DIR_NE){
		if(ballCo == start){
			ball.dir = DIR_SW;
		}else if(ballCo == middle){
			ball.dir = DIR_W;
		}else{
			ball.dir = DIR_NW;
		}
	/*}else if(ball.dir == DIR_E){
		if(ballCo == start){
			ball.dir = DIR_SW;
		}else if(ballCo == middle){
			ball.dir = DIR_W;
		}else{
			ball.dir = DIR_NW;
		}
	}else{
		if(ballCo == start){
			ball.dir = DIR_SW;
		}else if(ballCo == middle){
			ball.dir = DIR_W;
		}else{
			ball.dir = DIR_NW;
		}
	}*/

	/*
	if(ball.dir == DIR_NE && ballCo == start){
		ball.dir = DIR_W;
	}
	else if(ball.dir == DIR_NE){
		ball.dir = DIR_W;
	}
	else if(ball.dir == DIR_SE){
		ball.dir = DIR_SW;
	}
	else{
		if(ballCo == start){
			ball.dir = DIR_SW;
		}
		else if(ballCo == middle){
			ball.dir = DIR_W;
		}
		else if(ballCo == end){
			ball.dir = DIR_NW;
		}
	}*/
	return ball;
}
/** Initialise state of ball
 * @param state the state of the ball to be created as a boing_state_t
 * @return ball */
ball_state_t ball_init(boing_state_t ball_state, uint8_t game){
	ball_state_t ball;
	ball.state = ball_state;
	ball.game_state = game;
	return ball;
}
