/** @file game.c
 * @author L. Richardson & N. Soong
 * @date October 2016
 * @brief game of pong
 * */

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "boing.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "ir_uart.h"
#include "paddle.h"
#include "led.h"
#include "ledmat.h"
#include "ball.h"
#include "menu.h"
#include "networking.h"

//MAGIC NUMBERS
#define PACER_RATE 500
#define MESSAGE_RATE 15
#define LOOP_RATE 500

/** Determine if the ball has hit the paddle
 * @param myPaddle, the paddle of the user
 * @param ball, the state of the ball
 * @return 1 if ball hits paddle, -1 if not
 * */
static int collision_detect(paddle_t paddle, boing_state_t ball){

	if(ball.pos.y == paddle.startCo || ball.pos.y == paddle.midCo || ball.pos.y == paddle.endCo){
		led_set (LED1, 0);
		return 1;
	}
	else if((ball.pos.y == paddle.startCo+1 && ball.dir == DIR_NE) || (ball.pos.y == paddle.endCo-1 && ball.dir == DIR_SE)){
		led_set (LED1, 0);
		return 1;
	}
	else{
		//GAME OVER
		//led_set (LED1, 1);
		return -1;
	}
}


int main (void)
{

	system_init ();
    tinygl_init (PACER_RATE);
    navswitch_init ();
    pacer_init(300);
    ir_uart_init ();
    
    //led init
    led_init();
    led_set (LED1, 0);

    boing_state_t ball_state = boing_init (0, 3, DIR_E);
    ball_state_t ball = ball_init(ball_state, 1);
    paddle_t paddle = paddle_init(2,3,4);
    drawPaddle(paddle);

    uint8_t inPlay = 1;
    uint8_t ballInCourt = 1;
    
	char c;
    int tick;

		while (1)
    {
		while(inPlay == 1){
		pacer_wait();
		tick++;

        if (tick >= 40)
        {
			navswitch_update();
			tick = 0;
			tinygl_draw_point(ball.state.pos, 0);

			ball.state = boing_update(ball.state);


			if(ball.state.pos.x == 3){
				 int collision = collision_detect(paddle, ball.state);
				 inPlay = collision;
				 if(collision > 0){
					 ball.state = hit_paddle(ball.state, paddle);
				 }
				 else{ //GAME OVER
					 tinygl_clear();
					 tinygl_draw_point (ball.state.pos, 0);
				 }
			}

			tinygl_draw_point (ball.state.pos, 1);

			if(navswitch_push_event_p (NAVSWITCH_SOUTH) && paddle.endCo < 6){
				movePaddle(&paddle, DIR_UP);
				}
			if(navswitch_push_event_p (NAVSWITCH_NORTH) && paddle.startCo > 0){
				movePaddle(&paddle, DIR_DOWN);
				}
				//check that ball is not in play
			if(ir_uart_read_ready_p()){//&& ballInCourt == 0){ //receiving
				ball = receiving(c);
				//inPlay = ball.game_state;
				//ballInCourt = 1;
			}
			if(ball.state.pos.x == 0){ //ballInCourt == 1  && 
				sending(inPlay,ball.state.dir,ball.state.pos.y); //sending
				tinygl_draw_point (ball.state.pos, 0);
				//ballInCourt = 0;
				//led_set (LED1, 1);
			}
		}
		tinygl_update ();
    }
    end_screen();
}
}
