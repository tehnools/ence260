#include "system.h"
#include "pacer.h"
#include "navswitch.h"
//#include "ir_uart.h"
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

#define PACER_RATE 500
#define MESSAGE_RATE 15
#define LOOP_RATE 500

/* Determine if the ball has hit the paddle
 * @param myPaddle, the paddle of the user
 * @param ball, the state of the ball
 * @return 1 if ball hits paddle, -1 if not
 * */
static int collision_detect(paddle_t paddle, boing_state_t ball){
	
	if(ball.pos.y == paddle.startCo || ball.pos.y == paddle.midCo || ball.pos.y == paddle.endCo){
		//need to stop the paddle led that is hit from turning off
		
		led_set (LED1, 0);
		return 1;
		//boing_reverse(ball);
	}
	else if((ball.pos.y == paddle.startCo+1 && ball.dir == DIR_NE) || (ball.pos.y == paddle.endCo-1 && ball.dir == DIR_SE)){
		led_set (LED1, 0);
		return 1;
	}
	else{
		//GAME OVER	
		led_set (LED1, 1);
		return -1;
	}
}

static void end_screen(void){
	tinygl_init (LOOP_RATE);
	tinygl_font_set (&font5x7_1);
	tinygl_text_speed_set (MESSAGE_RATE);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    /* TODO: Set the message using tinygl_tlab3-ext().  */
    char string[] = "GAME OVER";
    tinygl_text(string);

    pacer_init (PACER_RATE);
	while(1){
		pacer_wait();
        
        /* TODO: Call the tinygl update function. */
        tinygl_update();
	}
	
}

int main (void)
{
	system_init ();
	
    tinygl_init (PACER_RATE);
    navswitch_init ();
    pacer_init(300);

    ir_uart_init ();
    led_init();
    led_set (LED1, 0);

    boing_state_t ball = boing_init (0, 3, DIR_E);
    paddle_t paddle = paddle_init(2,3,4);
    drawPaddle(paddle);
    
    int game = 1;
    
    int tick;
	led_set (LED1, 0);
    while (1)
    {
		while(game == 1){
		pacer_wait();
		tick++;
		
        if (tick >= 40)
        {
			navswitch_update();
			tick = 0;
			
			//if(ball.pos.x == 0){
		//		ir_uart_putc(character);
		//	}
				
			//erase		
			tinygl_draw_point (ball.pos, 0);
			
			ball = boing_update(ball);
			
			
			if(ball.pos.x == 3){
				 int collision = collision_detect(paddle, ball);
				 game = collision;
				 if(collision > 0){
					 //led_set (LED1, 1);
					 ball = boing_reverse(ball);
					 //boing_update(ball);
				 }
				 else{
					 tinygl_clear();
					 tinygl_draw_point (ball.pos, 0);
				 }
				// tinygl_draw_point (ball.pos, 1);
			}
			
			tinygl_draw_point (ball.pos, 1);
			
			if(navswitch_push_event_p (NAVSWITCH_SOUTH) && paddle.endCo < 6){
				movePaddle(&paddle, DIR_UP);
				
			   tinygl_clear();
			   drawPaddle(paddle);
			   
		   }
		   
		   if(navswitch_push_event_p (NAVSWITCH_NORTH) && paddle.startCo > 0){
				movePaddle(&paddle, DIR_DOWN);
				
			   tinygl_clear();
			   drawPaddle(paddle);
			   
		   }
			
       
		}
	tinygl_update ();
    }
    
    end_screen();
}
}
