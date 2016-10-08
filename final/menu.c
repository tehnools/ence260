#include "menu.h"
#include "system.h"
#include "tinygl.h"
#include "led.h"

#define PACER_RATE 500
#define MESSAGE_RATE 15
#define LOOP_RATE 500

/**Show game over once ball has missed the paddle*/
void end_screen(void){
	tinygl_init (LOOP_RATE);
	tinygl_font_set (&font5x7_1);
	tinygl_text_speed_set (MESSAGE_RATE);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    char string[] = "GAME OVER";
    tinygl_text(string);

    pacer_init (PACER_RATE);
	while(1){
		pacer_wait();
        tinygl_update();
	}	
}
