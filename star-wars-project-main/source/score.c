/*
 * score.c
 *
 *  Created on: Jan 20, 2023
 *      Authors: Alice Guntli, Léane Donzé
 */

#include <nds.h>
#include <stdio.h>
#include <fat.h>
#include "score.h"

struct time read_max_score(){

	// initialize if scores.txt does not exist
	int min_best = 9;
	int sec_best = 99;

	//Open the file in read mode
	FILE* file = fopen("/scores.txt","r");
	if(file != NULL){

		//Read the value and put it into the variables min_best and sec_best
		fscanf(file,"%i %i", &min_best, &sec_best);
		// close the file
		fclose(file);
	}

	// return read score
	struct time best_score = {.min = min_best, .sec = sec_best, .msec = 0};
	return best_score;
}


struct time write_max_score(struct time current_score, struct time best_score){

	// check if current score is lower, if yes record it
	if ((current_score.min <= best_score.min) && (current_score.sec < best_score.sec)) {
		best_score.min = current_score.min;
		best_score.sec = current_score.sec;

		//Open the file in write mode to overwrite
		FILE* file = fopen("/scores.txt","w+");
		if(file != NULL)
		{
			//Print the value in the file
			fprintf(file,"%i %i\n", current_score.min, current_score.sec);
			//Close the file
			fclose(file);
		}
	}

	return best_score;
}
