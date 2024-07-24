#pragma once

#include "incl.hpp"
#include "io.hpp"

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
		stacktrace(module::error, "SDL initialisation failed: %s.", SDL_GetError());
		SDL_Quit(); goto ERR;
	}
	if (IMG_Init(IMG_INIT_PNG) == -1) {
		stacktrace(module::error, "SDL_image initialisation failed: %s.", IMG_GetError());
		IMG_Quit(); goto ERR;
	}
	if (Mix_Init(MIX_INIT_OGG) == -1) {
		stacktrace(module::error, "SDL_mixer initialisation failed: %s.", Mix_GetError());
		Mix_Quit(); goto ERR;
	}
	if (TTF_Init() == -1) {
		stacktrace(module::error, "SDL_ttf initialisation failed: %s.", TTF_GetError());
		TTF_Quit(); goto ERR;
	}
	return SUCCESS;
ERR:
	throw INITIALISATION;
}
