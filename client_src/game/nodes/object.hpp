#pragma once

#include "../incl.hpp"

class _Object {
	SDL_Texture* texture;
	static uint64_t count; /* 18,446,744,073,709,551,615 objects ought to be enough for anybody */
	uint64_t id;
	uint_least32_t group;
	static std::set<int_fast64_t> z_order_set;
	int_fast64_t z_order;
	int x;
	int y;
	uint8_t alpha;
	uint16_t rot;
	uint8_t scale;
public:
	static int_fast64_t uniquify_z_order(int_fast64_t& z_order) {
		if (z_order >= 0) {
			while (z_order_set.find(next_z_order) != z_order_set.end()) {
				next_z_order++;
				if (z_order == INT_FAST64_MAX) {
					return 0;
				}
			}
		} else {
			while (z_order_set.find(next_z_order) != z_order_set.end())) {
				next_z_order--;
				if (z_order == INT_FAST64_MAX) {
					return 0;
				}
			}
		}
		return next_z_order;
	}
	texture(SDL_Renderer* rend, int_fast64_t z_order, const char* image) {
		if (z_order != 0) {
			if (z_order_set.find(z_order) != z_order_set.end()) {
				stacktrace(module::warning, "z_order (%lld) is already in use. New unique z_order: %lld", z_order, uniquify_z_order(z_order));
				if (z_order == 0) {
					stacktrace(module::error, "No free z_order left. Discarded.");
					~texture();
				}
			}
			this->z_order = z_order;
			z_order_set.insert(z_order);
		} else {
			stacktrace(module::error, "Attempted to use zero as a z_order (reserved for player). Discarded.");
			~texture();
		}
		texture = IMG_LoadTexture(rend, image);
		if (!texture) {
			stacktrace(module::error, "Couldn't load \"%s\". Discarded.", image);
			z_order_set.erase(z_order);
			~texture();
		}
	}
	~texture() {
		SDL_DestroyTexture(texture);
	}
};

uint64_t object::count = 0;
std::set<int_fast64_t> object::z_order_set;
