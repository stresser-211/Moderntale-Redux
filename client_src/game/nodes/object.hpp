#pragma once

#include "../incl.hpp"

class object {
	SDL_Texture* texture;
	static uint64_t count; /* 18,446,744,073,709,551,615 objects ought to be enough for anybody */
	int_fast64_t z_order;
public:
	texture(SDL_Renderer* rend, int_fast64_t z_order, const char* image) {
		if (z_order != 0) {
			this->z_order = z_order;
		} else {
			stacktrace(module::error, "Attempted to use zero as a z order (reserved for player). Discarded.");
			~texture();
		}
		texture = IMG_LoadTexture(rend, image);
		if (!texture) {
			stacktrace(module::error, "Couldn't load \"%s\". Discarded.", image);
			~texture();
		}
	}
	~texture() {
		SDL_DestroyTexture(texture);
	}
};

uint64_t object::count = 0;
