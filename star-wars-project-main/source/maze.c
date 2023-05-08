/*
 * maze.c
 *
 *  Created on: Nov 28, 2022
 *      Authors: Alice Guntli, Léane Donzé
 */

#include <nds.h>
#include <stdio.h>
#include <time.h>
#include "graphics_main.h"
#include "sound.h"


void set_trooper_position(){

	// random seed
	srand(time(NULL));

	// trooper can pop in any visible row/column regardless of walls
	x_trooper = (rand()%31)*8;
	y_trooper = (rand()%23)*8;

}

void update_yoda_position(){

	// poll keys for direction of motion
	scanKeys();
	u16 keys = keysHeld();

	// for each direction, check there is no wall, play sound if wall
	// 12 = center of yoda, 8 = distance of displacement
	if (keys & KEY_DOWN) {
		if (((y_yoda+16) < 184) && (is_wall(x_yoda+12, y_yoda+12+8) == false)){
			y_yoda += 8;
		}
		else {
			play_sound_thunk();
		}
	}

	if (keys & KEY_UP) {
		if (((y_yoda+16) > 8) && (is_wall(x_yoda+12, y_yoda+12-8) == false)){
			y_yoda -= 8;
		}
		else {
			play_sound_thunk();
		}
	}

	if (keys & KEY_LEFT) {
		if (((x_yoda+16) > 8) && (is_wall(x_yoda+12-8, y_yoda+12) == false)){
			x_yoda -= 8;
		}
		else {
			play_sound_thunk();
		}
	}

	if (keys & KEY_RIGHT) {
		if (((x_yoda+16) < 248) && (is_wall(x_yoda+12+8, y_yoda+12) == false)){
			x_yoda += 8;
		}
		else {
			play_sound_thunk();
		}
	}

	// update the graphics
	update_sprite_positions();

}

bool reached_trooper(){

	// check if yoda is close to the trooper
	if (x_trooper-16 < x_yoda && x_trooper + 16 > x_yoda){
		if (y_trooper-16 < y_yoda && y_trooper + 16 > y_yoda){
			return true;
		}
	}
	return false;
}

void set_yoda_position(){
	// random seed
	srand(time(NULL)+10);

	// pop yoda in a free space
	x_yoda = (rand()%32)*8 -12;
	y_yoda = (rand()%24)*8 -12;
	while (is_wall(x_yoda+12,y_yoda+12) == true && reached_trooper() == false){
		x_yoda = (rand()%32)*8 -12;
		y_yoda = (rand()%24)*8 -12;
	}
}







