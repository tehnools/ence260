/*game.c
 * Author: N.Soong
 * Date:10-Oct-2016
 * Simple Paper Sissors Rock Game
 * Main module Version 2
 * */

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "menu.h"
#include "button.h"

//Magic Numbers
#define PACER_RATE 500

void display_character (char character)
{
	/*Takes a character adds a null character and 
	 * displays it via tiny_gl
	 * @param char
	 * @return void*/
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


static uint8_t rpsCmp(char character, char in_character){
	/*Checks current character with input character
	 * @Param a char and another char to compare
	 * @return A boolean */
	if (character == 'S' && in_character == 'P'){
		return 1;
	} else if (character == 'R' && in_character == 'S'){
		return 1;
	} else if(character == 'P' && in_character == 'R'){
		return 1;
	} else if(character == in_character) {
		return 2;
	}
	return 0;
}

int main (void)
{
	/*Main Function that runs the game
	 * @param void
	 * @return 0 to close*/
	
	system_init ();
	/*Initialisation of LEDS,SWITCH and IR SENDER/RECEIVER*/
    navswitch_init ();
    ir_uart_init ();

	char PSR[3] = {'P','R','S'};
	char character = PSR[0];
	char in_character;

	uint8_t score = 0;
	int i = 0; //PSR index

	int bool_sent=0;
	int bool_rec= 0; 

    pacer_init (PACER_RATE); 

	start_screen();
    int game = 1; // Bool Checks game progress 
    
    while (1)
    {
		while(game <= 3){
			pacer_wait ();
			
			navswitch_update ();

		   
			if (navswitch_push_event_p (NAVSWITCH_NORTH)){
				i += 1;
				if(i > 2){
					i = 0;
				}
			}

			if (navswitch_push_event_p (NAVSWITCH_SOUTH)){
				i-=1;
				if(i < 0){
					i = 2;
				}
			} 
			character = PSR[i];

			
			if (ir_uart_read_ready_p ())
		   {
			   in_character = ir_uart_getc ();
			   bool_rec = 1;
		   }
		   
		   //this will be replaced with game stuff
			if (navswitch_push_event_p (NAVSWITCH_PUSH)){
				ir_uart_putc(character);
				bool_sent = 1;
			}
		   
			if(bool_sent == 1 && bool_rec == 1){
				uint8_t result = rpsCmp(character, in_character);
				if(result < 2){
					score += result;
					game += 1;
				}
				result_screen(result);
					
				
				bool_sent = 0;
				bool_rec = 0;
				character = 'P';
			}
		
			display_character(character);
			tinygl_update ();
			
			
	
		}
    end_screen(score); //End Screen Displays
}

}
