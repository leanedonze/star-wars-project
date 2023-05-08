/*
 * graphics_main.c
 *
 *  Created on: Nov 28, 2022
 *      Authors: Alice Guntli, Léane Donzé
 */
#include <nds.h>
#include <stdio.h>
#include "title.h"
#include "maze.h"
#include "yoda.h"
#include "trooper.h"
#include "graphics_main.h"
#include "instructions.h"
#include "endyoda.h"


// sprite memory
u16* gfx;
u16* gfx1;


// maze definition
u8 maze[] = {
0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1,
0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1,
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1,
0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1,
0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1,
0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0,
0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1,
0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1,
0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1,
0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1,
0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1,
0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

// tiles for wall and path
u8 FreeTile[64] =
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

u8 WallTile[64] =
{
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1
};

void configure_main_backgrounds() {

	// Enable the VRAM
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	// Choose the mode
	REG_DISPCNT = MODE_0_2D;

	// Setup title
	BGCTRL[1] = BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(2) | BG_32x32;
	swiCopy(titleTiles, BG_TILE_RAM(2), titleTilesLen/2);
	swiCopy(titleMap, BG_MAP_RAM(1), titleMapLen/2);

	// Setup the maze
	BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);
	dmaCopy(WallTile, (u8*)BG_TILE_RAM(1), 64);
	dmaCopy(FreeTile, (u8*)BG_TILE_RAM(1) + 64, 64);

	u8 i = 0;
	u8 j = 0;

	for (i = 0; i < 24; ++i) {
		for (j = 0; j < 32; ++j) {
			BG_MAP_RAM(0)[32*i+j] = maze[32*i+j];
		}
	}

	// Setup fight instructions
	BGCTRL[2] = BG_COLOR_256 | BG_MAP_BASE(5) | BG_TILE_BASE(4) | BG_32x32;
	swiCopy(instructionsTiles, BG_TILE_RAM(4), instructionsTilesLen/2);
	swiCopy(instructionsMap, BG_MAP_RAM(5), instructionsMapLen/2);

	// Setup end yoda
	BGCTRL[3] = BG_COLOR_256 | BG_MAP_BASE(3) | BG_TILE_BASE(6) | BG_32x32;
	swiCopy(endyodaTiles, BG_TILE_RAM(6), endyodaTilesLen/2);
	swiCopy(endyodaMap, BG_MAP_RAM(3), endyodaMapLen/2);


	// sprites
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;

	oamInit(&oamMain, SpriteMapping_1D_32, false);
	gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color );
	gfx1 = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color );
	dmaCopy(yodaPal,SPRITE_PALETTE,yodaPalLen);
	dmaCopy(trooperPal,&SPRITE_PALETTE[yodaPalLen/2],trooperPalLen);
	dmaCopy(yodaTiles,gfx,yodaTilesLen);
	dmaCopy(trooperTiles,gfx1,trooperTilesLen);

}


void activate_menu_main() {

	swiCopy(titlePal, BG_PALETTE, titlePalLen/2);

	hide_sprites();
	REG_DISPCNT &= (~DISPLAY_BG0_ACTIVE);
	REG_DISPCNT &= (~DISPLAY_BG2_ACTIVE);
	REG_DISPCNT &= (~DISPLAY_BG3_ACTIVE);
	REG_DISPCNT |=  DISPLAY_BG1_ACTIVE;

}

void activate_maze_main(){

	swiCopy(titlePal, BG_PALETTE, titlePalLen/2);

	REG_DISPCNT &= (~DISPLAY_BG1_ACTIVE);
	REG_DISPCNT &= (~DISPLAY_BG2_ACTIVE);
	REG_DISPCNT &= (~DISPLAY_BG3_ACTIVE);
	REG_DISPCNT |=  DISPLAY_BG0_ACTIVE;

	set_trooper_position();
	set_yoda_position();
	update_sprite_positions();

}

void activate_fight_main(){

	swiCopy(instructionsPal, BG_PALETTE, instructionsPalLen/2);

	hide_sprites();
	REG_DISPCNT &= (~DISPLAY_BG0_ACTIVE);
	REG_DISPCNT &= (~DISPLAY_BG1_ACTIVE);
	REG_DISPCNT &= (~DISPLAY_BG3_ACTIVE);
	REG_DISPCNT |=  DISPLAY_BG2_ACTIVE;

}

void activate_end_main(){

	swiCopy(endyodaPal, BG_PALETTE, endyodaPalLen/2);

	hide_sprites();
	REG_DISPCNT &= (~DISPLAY_BG0_ACTIVE);
	REG_DISPCNT &= (~DISPLAY_BG1_ACTIVE);
	REG_DISPCNT &= (~DISPLAY_BG2_ACTIVE);
	REG_DISPCNT |=  DISPLAY_BG3_ACTIVE;

}

void update_sprite_positions(){
	oamSet(&oamMain, 						// oam handler
				0,							// Number of sprite
				x_yoda, y_yoda,				// Coordinates
				0,							// Priority
				0,							// Palette to use
				SpriteSize_32x32,			// Sprite size
				SpriteColorFormat_16Color,	// Color format
				gfx,						// Loaded graphic to display
				-1,							// Affine rotation to use (-1 none)
				false,						// Double size if rotating
				false,						// Hide this sprite
				false, false,				// Horizontal or vertical flip
				false						// Mosaic
				);

	oamSet(&oamMain, 						// oam handler
				1,							// Number of sprite
				x_trooper, y_trooper,		// Coordinates
				0,							// Priority
				1,							// Palette to use
				SpriteSize_32x32,			// Sprite size
				SpriteColorFormat_16Color,	// Color format
				gfx1,						// Loaded graphic to display
				-1,							// Affine rotation to use (-1 none)
				false,						// Double size if rotating
				false,						// Hide this sprite
				false, false,				// Horizontal or vertical flip
				false						// Mosaic
				);
	oamUpdate(&oamMain);
}

void hide_sprites(){
	oamSet(&oamMain, 						// oam handler
				0,							// Number of sprite
				x_yoda, y_yoda,				// Coordinates
				0,							// Priority
				0,							// Palette to use
				SpriteSize_32x32,			// Sprite size
				SpriteColorFormat_16Color,	// Color format
				gfx,						// Loaded graphic to display
				-1,							// Affine rotation to use (-1 none)
				false,						// Double size if rotating
				true,						// Hide this sprite
				false, false,				// Horizontal or vertical flip
				false						// Mosaic
				);

	oamSet(&oamMain, 						// oam handler
				1,							// Number of sprite
				x_trooper, y_trooper,		// Coordinates
				0,							// Priority
				1,							// Palette to use
				SpriteSize_32x32,			// Sprite size
				SpriteColorFormat_16Color,	// Color format
				gfx1,						// Loaded graphic to display
				-1,							// Affine rotation to use (-1 none)
				false,						// Double size if rotating
				true,						// Hide this sprite
				false, false,				// Horizontal or vertical flip
				false						// Mosaic
				);
	oamUpdate(&oamMain);
}


bool is_wall(int x, int y){
	// get tile number
	int x_tile = x/8;
	int y_tile = y/8;

	// check if the tile is a wall
	if (BG_MAP_RAM(0)[32*y_tile+x_tile] == 1) {
		return true;
	}
	else {
		return false;
	}
}




