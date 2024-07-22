#pragma once

#include "incl.hpp"

void CRC_init(void) {
	uint32_t CRC;
	for (uint32_t i = 0; i < 256; i++) {
		CRC = i;
		for (uint32_t j = 8; j > 0; j--) {
			if (CRC & 1) {
				CRC = (CRC >> 1) ^ 0xEDB88320;
			} else {
				CRC >>= 1;
			}
		}
		gl::CRC_table[i] = CRC;
	}
}

int init(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		SDL_Quit(); goto ERR;
	}
	if (IMG_Init(IMG_INIT_PNG) == -1) {
		IMG_Quit(); goto ERR;
	}
	if (TTF_Init() == -1) {
		TTF_Quit(); goto ERR;
	}
	if (Mix_Init(MIX_INIT_OGG) == -1) {
		Mix_Quit(); goto ERR;
	}
	return SUCCESS;
ERR:
	throw INITIALISATION;
}
