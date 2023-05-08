/*
 * graphics_sub.h
 *
 *  Created on: Nov 28, 2022
 *      Authors: Alice Guntli, Léane Donzé
 */

#ifndef GRAPHICS_SUB_H_
#define GRAPHICS_SUB_H_

#include "score.h"

void configure_sub_backgrounds();
void activate_menu_sub();
void activate_maze_sub();
void shift_menu_sub();
void activate_fight_sub();
void activate_end_sub();
void display_my_score(struct time current_score);
void display_max_score(struct time best_score);


#endif /* GRAPHICS_SUB_H_ */
