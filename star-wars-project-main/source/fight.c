/*
 * fight.c
 *
 *  Created on: Nov 28, 2022
 *      Authors: Alice Guntli, Léane Donzé
 */
#include <nds.h>
#include <stdio.h>
#include <time.h>
#include "sound.h"

// weakness zone bounds
int x_left = 0;
int x_right = 0;
int y_top = 0;
int y_bottom = 0;

int hit = 0;

void init_fight(){
	// choose zone randomly
	srand(time(NULL));
	int zone = (rand()%7);

	switch(zone){

	case 0 :
		// forehead
		x_left = 108;
		y_top = 0;
		x_right = 148;
		y_bottom = 40;
		break;

	case 1 :
		// chin
		x_left = 108;
		y_top = 40;
		x_right = 148;
		y_bottom = 80;
		break;

	case 2 :
		// left arm
		x_left = 85;
		y_top = 80;
		x_right = 114;
		y_bottom = 152;
		break;

	case 3 :
		// belly
		x_left = 114;
		y_top = 80;
		x_right = 143;
		y_bottom = 152;
		break;

	case 4 :
		// right arm
		x_left = 143;
		y_top = 80;
		x_right = 172;
		y_bottom = 152;
		break;

	case 5 :
		// left foot
		x_left = 95;
		y_top = 152;
		x_right = 128;
		y_bottom = 192;
		break;

	case 6 :
		// right foot
		x_left = 128;
		y_top = 152;
		x_right = 162;
		y_bottom = 192;
		break;
	}
}

bool fight(){

	// poll the touchscreen
	scanKeys();
	touchPosition touch;
	touchRead(&touch);
	if(touch.px || touch.py){

		// check if the touch is within the weakness zone
		if (touch.px > x_left && touch.px < x_right && touch.py > y_top && touch.py < y_bottom){
			// count hits and play sound when hit
			hit++;
			play_sound_laser();
		}
	}

	// if the trooper is hit twice return true and reset number of hits
	if (hit > 1){
		hit = 0;
		return true;
	}

	return false;
}

