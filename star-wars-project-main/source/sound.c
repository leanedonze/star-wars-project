/*
 * sound.c
 *
 *  Created on: Nov 28, 2022
 *      Authors: Alice Guntli, Léane Donzé
 */
#include <nds.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

void init_sound(){
	// load sound effects
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoad(MOD_INTRO_STARWARS);
	mmLoadEffect(SFX_LASER);
	mmLoadEffect(SFX_THUNK);
	mmLoadEffect(SFX_GONG);
	mmLoadEffect(SFX_WHAH_WHAH);

	// start sound
	mmStart(MOD_INTRO_STARWARS,MM_PLAY_LOOP);
}

void play_sound_laser(){
	mmEffect(SFX_LASER);
}

void play_sound_thunk(){
	mmEffect(SFX_THUNK);
}

void play_sound_gong(){
	mmEffect(SFX_GONG);
}

void play_sound_wah_wah(){
	mmEffect(SFX_WHAH_WHAH);
}
