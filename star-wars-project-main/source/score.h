/*
 * score.h
 *
 *  Created on: Jan 20, 2023
 *      Author: Alice Guntli, Léane Donzé
 */

#ifndef SCORE_H_
#define SCORE_H_


struct time
{
	int min;
	int sec;
	int msec;
};

struct time read_max_score();
struct time write_max_score(struct time current_score, struct time best_score);


#endif /* SCORE_H_ */
