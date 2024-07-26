#pragma once

#include "../incl.hpp"
#include "../io.hpp"

void stacktrace(const char* module, const char* msg, ...); /* idk compiler doesn't see it while it is actually present also i'm a cute little femboy and i love my ass being fucked uwu */

class _Object {
	SDL_Texture* texture;
	static uint64_t count; /* 18,446,744,073,709,551,615 objects ought to be enough for anybody */
	static uint64_t id;
	uint_least32_t group;
	static std::set<int_fast64_t> z_order_set;
	int_fast64_t z_order;
	int x;
	int y;
	uint8_t alpha;
	uint16_t rot;
	float scale;

	static int_fast64_t uniquify_z_order(int_fast64_t& z_order) {
		if (z_order >= 0) {
			while (z_order_set.find(z_order) != z_order_set.end()) {
				z_order++;
				if (z_order == INT_FAST64_MAX) {
					goto EXCEPTION;
				}
			}
		} else {
			while (z_order_set.find(z_order) != z_order_set.end()) {
				z_order--;
				if (z_order == INT_FAST64_MAX) {
					goto EXCEPTION;
				}
			}
		}
		return z_order;
EXCEPTION:
		z_order = 0;
		return 0;
	}
public:
	_Object() = delete;
	_Object(SDL_Renderer* rend, int_fast64_t z_order, const char* image, int x, int y, uint8_t alpha, uint16_t rot, float scale) {
		_constructor(rend, z_order, image, x, y, alpha, rot, scale);
	}
	_Object(SDL_Renderer* rend, int_fast64_t z_order, const char* image, int x, int y) {
		_constructor(rend, z_order, image, x, y, (uint8_t)255, uint16_t(0), 100.0f);
	}
	~_Object() {
		SDL_DestroyTexture(this->texture);
	}
	void _constructor(SDL_Renderer* rend, int_fast64_t z_order, const char* image, int x, int y, uint8_t alpha, uint16_t rot, float scale) {
		id++;
		if (id == 0) throw OUT_OF_IDS;
		if (z_order != 0) {
			if (z_order_set.find(z_order) != z_order_set.end()) {
				stacktrace(module::warning, "z_order (%lld) is already in use. New unique z_order: %lld", z_order, uniquify_z_order(z_order));
				if (z_order == 0) {
					stacktrace(module::error, "No free z_order left. Discarded.");
					this->z_order_set.erase(z_order);
					throw OUT_OF_Z_ORDER;
				}
			}
			this->z_order_set.insert(z_order);
			this->z_order = z_order;
		} else {
			stacktrace(module::error, "Attempted to use zero as a z_order (reserved for player). Discarded.");
			throw OUT_OF_Z_ORDER;
		}
		this->texture = IMG_LoadTexture(rend, image);
		if (!this->texture) {
			stacktrace(module::error, "Couldn't load \"%s\". Discarded.", image);
			this->z_order_set.erase(z_order);
			throw OUT_OF_Z_ORDER;
		}
		this->x = x;
		this->y = y;
		this->alpha = alpha;
		this->rot = rot;
		this->scale = scale;
	}
	SDL_Texture* get_texture(void) const {
		return this->texture;
	}
	std::pair<int, int> get_position(void) const {
		return {this->x, this->y};
	}
};

uint64_t _Object::count = 0;
uint64_t _Object::id = 0;
std::set<int_fast64_t> _Object::z_order_set;

class _Sequence : _Object {
public:
};

