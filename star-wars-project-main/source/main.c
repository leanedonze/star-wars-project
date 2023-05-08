/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include <time.h>
#include <fat.h>
#include "graphics_main.h"
#include "graphics_sub.h"
#include "maze.h"
#include "fight.h"
#include "sound.h"
#include "score.h"



typedef enum {MENU, MAZE, FIGHT, ENDGAME} stateMachine;

stateMachine state;

int body_count = 0;
struct time current_time = {.min = 0, .sec = 0, .msec = 0};
struct time best_score = {.min = 9, .sec = 99, .msec = 0};


//Timer ISR
void chronometer(){

	current_time.msec = (current_time.msec + 1) % 1000;

	if(!current_time.msec){

		current_time.sec = (current_time.sec + 1) % 60;

		if(!current_time.sec)
			current_time.min++;
	}
}

//Restart ISR
void restart(){

	u16 keys = ~(REG_KEYINPUT);

	if (keys & KEY_START){

		// change state
		state = MENU;

		// change graphics
		activate_menu_main();
		activate_menu_sub();

		// reset values
		current_time.min = 0;
		current_time.sec = 0;
		current_time.msec = 0;
		body_count = 0;
	}
}


// initializations
void init_game(){

	// Secondary Storage
	fatInitDefault();

	// Graphics
	configure_main_backgrounds();
	activate_menu_main();
	configure_sub_backgrounds();
	activate_menu_sub();

	// Sound
	init_sound();

	// Timer IRQ
	irqSet(IRQ_TIMER0, &chronometer);
	irqEnable(IRQ_TIMER0);
	TIMER0_DATA = TIMER_FREQ_256(1000);
	TIMER0_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;

	// Restart IRQ
	REG_KEYCNT = (1<<14) | KEY_START;
	irqSet(IRQ_KEYS, &restart);
	irqEnable(IRQ_KEYS);

}



int main(void) {

	init_game();

	// initial conditions
	int init = 0;
	state = MENU;

    while(1) {

    	switch(state){
    	case MENU:

    		// hide sprite when restarting
    		hide_sprites();

    		// animation of sub screen
        	if (init++ == 0)
        		shift_menu_sub();

        	// Switch to game when pressing A or touching the screen
        	scanKeys();
        	swiWaitForVBlank();
            u16 keys = keysDown();
            if((keys & KEY_A) | (keys & KEY_TOUCH)) {

            	// change graphics for maze
            	activate_maze_sub();
            	activate_maze_main();

            	// start counting time
            	TIMER0_CR |= TIMER_ENABLE;

            	// change state and play sound effect
            	state = MAZE;
            	play_sound_laser();
            }

            break;

    	case MAZE:

    		// delay for smooth motion of Yoda
    		swiDelay(800000);
    		update_yoda_position();

    		// switch state when close to Trooper
    		if (reached_trooper()){
    			// play sound effect
    			play_sound_gong();

    			// change graphics
    			activate_fight_main();
    			activate_fight_sub();

    			// start the fight
    			init_fight();
    			state = FIGHT;

    		}
    		break;

    	case FIGHT:
    		// Change state when a Trooper is defeated
    		if (fight()) {

    			// count number of defeated troopers
    			body_count++;

    			// stop the game after 2 troopers defeated
    			if (body_count == 2) {
    				// stop counting time
    				TIMER0_CR &= ~(TIMER_ENABLE);

    				// activate end game graphics
    	    		activate_end_main();
    	    		activate_end_sub();

    	    		// read and display score (time)
    	    		best_score = read_max_score();
    	    		best_score = write_max_score(current_time, best_score);
    	    		display_my_score(current_time);
    	    		display_max_score(best_score);

    	    		// change state
    				state = ENDGAME;
    			}
    			// still one Trooper to defeat
    			else {

					// change graphics for maze
					activate_maze_sub();
					activate_maze_main();

					// change state and play sound
					state = MAZE;
					play_sound_laser();
    			}

    		}

    		break;

    	case ENDGAME:
        	// pressing a restarts the game
        	scanKeys();
        	swiWaitForVBlank();
        	keys = keysDown();
        	if(keys & KEY_A) {
        		// reactivate menu graphics
        		activate_menu_main();
        		activate_menu_sub();

        		// reset all values and change state
        		current_time.min = 0;
        		current_time.sec = 0;
        		current_time.msec = 0;
        		body_count = 0;
        		state = MENU;

        	}

    		break;

    	default:
    		break;

    	}
    }
}

