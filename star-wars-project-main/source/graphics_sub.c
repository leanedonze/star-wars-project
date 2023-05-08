/*
 * graphics_sub.c
 *
 *  Created on: Nov 28, 2022
 *      Authors: Alice Guntli, Léane Donzé
 */
#include <nds.h>
#include "submenu.h"
#include "YvsD.h"
#include "stormtrooper_fight.h"
#include "numbers.h"
#include "score.h"

void configure_sub_backgrounds() {

	// Enable the VRAM
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

	// Choose the mode
	REG_DISPCNT_SUB = MODE_0_2D;

	// Setup the menu sub
	BGCTRL_SUB[0] = BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_32x64;
	swiCopy(submenuTiles, BG_TILE_RAM_SUB(1), submenuTilesLen/2);
	swiCopy(submenuMap, BG_MAP_RAM_SUB(0), submenuMapLen/2);

	// Setup Yoda vs Darth Vader background
	BGCTRL_SUB[1] = BG_COLOR_256 | BG_MAP_BASE(4) | BG_TILE_BASE(4) | BG_32x32;
	swiCopy(YvsDTiles, BG_TILE_RAM_SUB(4), YvsDTilesLen/2);
	swiCopy(YvsDMap, BG_MAP_RAM_SUB(4), YvsDMapLen/2);

	// Setup the fight
	BGCTRL_SUB[2] = BG_COLOR_256 | BG_MAP_BASE(5) | BG_TILE_BASE(3) | BG_32x32;
	swiCopy(stormtrooper_fightTiles, BG_TILE_RAM_SUB(3), stormtrooper_fightTilesLen/2);
	swiCopy(stormtrooper_fightMap, BG_MAP_RAM_SUB(5), stormtrooper_fightMapLen/2);

	//Setup the end screen
	BGCTRL_SUB[3] = BG_32x32 | BG_COLOR_16 | BG_MAP_BASE(3) | BG_TILE_BASE(7);
	swiCopy(numbersTiles, BG_TILE_RAM_SUB(7), numbersTilesLen/2);

	int i = 32*32;
	while(i--)
		BG_MAP_RAM_SUB(3)[i] = 0;

}

void activate_menu_sub(){

	swiCopy(submenuPal, BG_PALETTE_SUB, submenuPalLen/2);

	REG_DISPCNT_SUB &= (~DISPLAY_BG1_ACTIVE);
	REG_DISPCNT_SUB &= (~DISPLAY_BG2_ACTIVE);
	REG_DISPCNT_SUB &= (~DISPLAY_BG3_ACTIVE);
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;

}

void shift_menu_sub(){
	//shifting vertically from up to down
	int i = 190;
	for(i=190; i<=310; i++){
		swiWaitForVBlank();
		REG_BG0VOFS_SUB = i;
	}
}

void activate_maze_sub(){

	swiCopy(YvsDPal, BG_PALETTE_SUB, YvsDPalLen/2);

	REG_DISPCNT_SUB &= (~DISPLAY_BG0_ACTIVE);
	REG_DISPCNT_SUB &= (~DISPLAY_BG2_ACTIVE);
	REG_DISPCNT_SUB &= (~DISPLAY_BG3_ACTIVE);
	REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;

}

void activate_fight_sub(){

	swiCopy(stormtrooper_fightPal, BG_PALETTE_SUB, stormtrooper_fightPalLen/2);

	REG_DISPCNT_SUB &= (~DISPLAY_BG0_ACTIVE);
	REG_DISPCNT_SUB &= (~DISPLAY_BG1_ACTIVE);
	REG_DISPCNT_SUB &= (~DISPLAY_BG3_ACTIVE);
	REG_DISPCNT_SUB |= DISPLAY_BG2_ACTIVE;

}

void activate_end_sub(){

	swiCopy(numbersPal, BG_PALETTE_SUB, numbersPalLen/2);

	REG_DISPCNT_SUB &= (~DISPLAY_BG0_ACTIVE);
	REG_DISPCNT_SUB &= (~DISPLAY_BG1_ACTIVE);
	REG_DISPCNT_SUB &= (~DISPLAY_BG2_ACTIVE);
	REG_DISPCNT_SUB |= DISPLAY_BG3_ACTIVE;

}

void display_max_score(struct time best_score)
{
	int row = 16;
	int col = 14;

	// write High
	int i = 0;
	for (i=0; i<4; i++){
		BG_MAP_RAM_SUB(3)[(row-2)*32+col-3+i] = numbersMap[40+2*i];
		BG_MAP_RAM_SUB(3)[(row-1)*32+col-3+i] = numbersMap[41+2*i];
	}

	// write Score
	for (i=0; i<5; i++){
		BG_MAP_RAM_SUB(3)[(row-2)*32+col+2+i] = numbersMap[22+2*i];
		BG_MAP_RAM_SUB(3)[(row-1)*32+col+2+i] = numbersMap[23+2*i];
	}

	// write time
	BG_MAP_RAM_SUB(3)[row*32+col] = numbersMap[(best_score.min)*2];
	BG_MAP_RAM_SUB(3)[(row+1)*32+col] = numbersMap[(best_score.min)*2+1];

	BG_MAP_RAM_SUB(3)[row*32+1+col] = numbersMap[20];
	BG_MAP_RAM_SUB(3)[(row+1)*32+1+col] = numbersMap[21];

	BG_MAP_RAM_SUB(3)[row*32+2+col] = numbersMap[(best_score.sec/10)*2];
	BG_MAP_RAM_SUB(3)[(row+1)*32+2+col] = numbersMap[(best_score.sec/10)*2+1];

	BG_MAP_RAM_SUB(3)[row*32+3+col] = numbersMap[(best_score.sec%10)*2];
	BG_MAP_RAM_SUB(3)[(row+1)*32+3+col] = numbersMap[(best_score.sec%10)*2+1];


}

void display_my_score(struct time current_score)
{
	int row = 8;
	int col = 14;

	// write Your
	int i = 0;
	for (i=0; i<4; i++){
		BG_MAP_RAM_SUB(3)[(row-2)*32+col-3+i] = numbersMap[32+2*i];
		BG_MAP_RAM_SUB(3)[(row-1)*32+col-3+i] = numbersMap[33+2*i];
	}

	// write Score
	for (i=0; i<5; i++){
		BG_MAP_RAM_SUB(3)[(row-2)*32+col+2+i] = numbersMap[22+2*i];
		BG_MAP_RAM_SUB(3)[(row-1)*32+col+2+i] = numbersMap[23+2*i];
	}

	// write time
	BG_MAP_RAM_SUB(3)[row*32+col] = numbersMap[(current_score.min)*2];
	BG_MAP_RAM_SUB(3)[(row+1)*32+col] = numbersMap[(current_score.min)*2+1];

	BG_MAP_RAM_SUB(3)[row*32+1+col] = numbersMap[20];
	BG_MAP_RAM_SUB(3)[(row+1)*32+1+col] = numbersMap[21];

	BG_MAP_RAM_SUB(3)[row*32+2+col] = numbersMap[(current_score.sec/10)*2];
	BG_MAP_RAM_SUB(3)[(row+1)*32+2+col] = numbersMap[(current_score.sec/10)*2+1];

	BG_MAP_RAM_SUB(3)[row*32+3+col] = numbersMap[(current_score.sec%10)*2];
	BG_MAP_RAM_SUB(3)[(row+1)*32+3+col] = numbersMap[(current_score.sec%10)*2+1];


}
