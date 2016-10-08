#include <stdio.h>
#include "ir_uart.h"
#include "boing.h"
#include "led.h"
#include "ball.h"

void sending(uint8_t inPlay, boing_dir_t direction, uint8_t location){
	uint8_t data[6];// last 2 bits not used xx00 0000
	/* 128  64  32  16  8   4   2   1
 	 *  0 | 0 | 0 | 0 | 0 | 0 | 0 |   0   |
 	 *  x   x  dir dir loc loc loc inplay  */
	uint8_t sum; //sums the bits for receiving
	int i ,j; // counters

		if(inPlay == 1){  
			data[0] = 1;
		} else {
			data[0] = 0;
		}

		if(direction == DIR_SW){ //48
			data[4] = 1;
			data[5] = 1;
		} else if(direction == DIR_W){ //32
			data[4] = 0;
			data[5] = 1;
		} else if(direction == DIR_NW){ //16
			data[4] = 1;
			data[5] = 0;
		}


		switch(location){
			case 0: //2
			data[1] = 1;
			data[2] = 0;
			data[3] = 0;
			break;
			case 1: //4
			data[1] = 0;
			data[2] = 1;
			data[3] = 0;
			break;
			case 2: //6
			data[1] = 1;
			data[2] = 1;
			data[3] = 0;
			break;
			case 3: //8
			data[1] = 0;
			data[2] = 0;
			data[3] = 1;
			break;
			case 4: //10
			data[1] = 1;
			data[2] = 0;
			data[3] = 1;
			break;
			case 5: //12
			data[1] = 0;
			data[2] = 1;
			data[3] = 1;
			break;
			case 6: //14
			data[1] = 1;
			data[2] = 1;
			data[3] = 1;
			break;
		}


	for(j=0; j<6;j+=1){ //sums everything in 
		sum += data[j];
	}
	ir_uart_putc(sum); 
}

boing_dir_t select_dir(uint8_t direction_sum){
	uint8_t direction;
	
	switch(direction_sum){
		case 48:
		direction = DIR_NE;
		break;
		case 32:
		direction = DIR_E;
		break;
		case 16:
		direction = DIR_SE;
		break;
	}
	
	return direction;
}


uint8_t select_loc(uint8_t location_sum){
	uint8_t location;

	switch(location_sum){
		case 14:
		location = 0;
		break;
		case 12:
		location = 1;
		break;
		case 10:
		location = 2;
		break;
		case 8:
		location = 3;
		break;
		case 6:
		location = 4;
		break;
		case 4:
		location = 5;
		break;
		case 2:
		location = 6;
		break;
	}
	return location;
}



ball_state_t receiving(char c){
	uint8_t character[6];
	uint8_t location;
	uint8_t inPlay;
	boing_dir_t direction;

	uint8_t location_sum; // sums of location and direction 
	uint8_t direction_sum;

	int i,j;

	/* convert each bit in the array to a 1 or a 0 */
	for(i=0; i<6; i+=1){
			character[i] = (c >> i) & 1;
	}

	/* Check if the first bit (inPlay is 1 or 0*/
	if (character[0] == 1){
		inPlay = 1;
	} else{
		inPlay = 0;
	}


	for(j=5; j>=0; j-=1){

		if(character[j] == 1){
			switch(j){
				case 5:
				location_sum += 32;
				break;
				case 4:
				direction_sum += 16;
				break;
				case 3:
				direction_sum += 8;
				break;
				case 2:
				location_sum += 4;
				break;
				case 1:
				location_sum += 2;
				break;
				}
			}
		}

	direction = select_dir(direction_sum);
	location = select_loc(location_sum);

	boing_state_t ball_state = boing_init (location, 0, direction);
	ball_state_t ball;

	if(inPlay == 0){ //stop game if other side has stopped
		ball = ball_init(ball_state, 0);
	}
	else{
		ball = ball_init(ball_state, 1);
		}
	return ball;
}
