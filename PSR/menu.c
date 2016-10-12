/*menu.c
 * Author: N.Soong
 * Date:10-Oct-2016
 * Module that starts start screen and end screen
 * */

//Included defs
#include "menu.h"
#include "system.h"
#include "tinygl.h"
#include "navswitch.h"


//Magic Numbers
#define PACER_RATE 500
#define MESSAGE_RATE 20
#define LOOP_RATE 500


/**Show game over once three games are played*/
void end_screen(uint8_t player_score){
	/*Checks if Player score is 3 then displays end screen
	 * Message*/
	 
	uint8_t other_score = 3 - player_score;
	
	tinygl_init (LOOP_RATE);
	tinygl_font_set (&font5x7_1);
	tinygl_text_speed_set (MESSAGE_RATE);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
	
	if(player_score > other_score){
		//WINNER
		char string[] = "WINNER";
		tinygl_text(string);
	}
	else{
		//LOSER
		char string[] = "LOSER";
		tinygl_text(string);
	}
    pacer_init (PACER_RATE);
	while(1){  
		pacer_wait();
        tinygl_update();
	}	
}

uint8_t result_screen(uint8_t res){
	/*Takes the result and displays a result message
	 * 
	 * */
	 
	tinygl_init (LOOP_RATE);
	tinygl_font_set (&font5x7_1);
	tinygl_text_speed_set (MESSAGE_RATE);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
	
	uint8_t start_game = 0;
	
	if(res == 1){
		char string[] = "WIN. PRESS SWITCH.";
		tinygl_text(string);
	}
	else if(res == 0){
		char string[] = "LOSS. PRESS SWITCH.";
		tinygl_text(string);
	} else{
		char string[] = "DRAW. PRESS SWITCH.";
		tinygl_text(string);
	}

	pacer_init (PACER_RATE);
	
	while(1){
	
	while(start_game == 0){
		pacer_wait();
		tinygl_update();
		navswitch_update();
		
		if (navswitch_push_event_p (NAVSWITCH_PUSH)){ 
			navswitch_update();
			start_game = 1;
			}
	}
	return 1;
	}

}


uint8_t start_screen(void){
	/*Displays Start Screen
	 * @param void
	 * @ return and unsign 8 bit integer*/
	tinygl_init (LOOP_RATE);
	tinygl_font_set (&font5x7_1);
	tinygl_text_speed_set (MESSAGE_RATE);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
	uint8_t start_game = 0;
	

    char string[] = "PAPER SCISSORS ROCK";
    tinygl_text(string);

    pacer_init (PACER_RATE);
    
	while(1){
		
		while(start_game == 0){
			pacer_wait();
			tinygl_update();
			navswitch_update();
			
			if (navswitch_push_event_p (NAVSWITCH_PUSH)){ 
				navswitch_update();
				start_game = 1;
			}
		}
		return 1;
	}
}
