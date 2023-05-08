/*
 * graphics_main.h
 *
 *  Created on: Nov 28, 2022
 *      Authors: Alice Guntli, Léane Donzé
 */

#ifndef GRAPHICS_MAIN_H_
#define GRAPHICS_MAIN_H_


int x_yoda, y_yoda, x_trooper, y_trooper;

void configure_main_backgrounds();
void activate_menu_main();
void activate_maze_main();
void activate_fight_main();
void activate_end_main();
void update_sprite_positions();
void hide_sprites();
bool is_wall(int x, int y);


#endif /* GRAPHICS_MAIN_H_ */
