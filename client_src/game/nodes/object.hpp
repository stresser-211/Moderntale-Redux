#pragma once

#include "../incl.hpp"
#include "../io.hpp"

extern void stacktrace(const char* module, const char* msg, ...); /* Reason: ying yang of includes */

class _object {
	void _constructor(SDL_Renderer* rend, int_fast64_t z_order, const char* image_path, int64_t& x, int64_t& y, uint8_t& alpha, uint16_t& rot, float& scale) {
		if (z_order != 0) {
			if (z_order_set.find(z_order) != z_order_set.end()) {
				stacktrace(module::warning, "z_order (%lld) is already in use. New unique z_order: %lld", z_order, uniquify_z_order(z_order));
				if (z_order == 0) {
					stacktrace(module::warning, "No free z_order left. Object discarded.");
					z_order_set.erase(z_order);
					throw OUT_OF_Z_ORDER;
				}
			}
			z_order_set.insert(z_order);
			this->z_order = z_order;
		} else {
			stacktrace(module::warning, "Attempted to use zero as a z_order (reserved for player). Object discarded.");
			throw OUT_OF_Z_ORDER;
		}
		this->image_path = image_path;
		texture = IMG_LoadTexture(rend, image_path);
		if (!texture) {
			stacktrace(module::warning, "Couldn't load \"%s\". Object discarded.", image_path);
			z_order_set.erase(z_order);
		} //todo: exception handler
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
		this->x = x;
		this->y = y;
		this->alpha = alpha;
		this->rot = rot;
		this->scale = scale;
	}
protected:
	SDL_Texture* texture;
	SDL_Rect rect;
	const char* image_path;
	static uint64_t count; /* 18,446,744,073,709,551,615 objects ought to be enough for anybody */
	uint_least32_t group;
	static std::set<int_fast64_t> z_order_set;
	int_fast64_t z_order;
	int64_t x;
	int64_t y;
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
				if (z_order == INT_FAST64_MIN) {
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
	_object(void) = delete;
	_object(SDL_Renderer* rend, int_fast64_t z_order, const char* image, int64_t x, int64_t y, uint8_t alpha, uint16_t rot, float scale) {
		_constructor(rend, z_order, image, x, y, alpha, rot, scale);
	}
	_object(SDL_Renderer* rend, _object* obj) {
		_constructor(rend, uniquify_z_order(obj->z_order), obj->image_path, obj->x, obj->y, obj->alpha, obj->rot, obj->scale);
	}
	virtual ~_object(void) {
		SDL_DestroyTexture(texture);
		z_order_set.erase(z_order);
	}
	/* Get */
	auto get_texture(void) const {
		return texture;
	}
	std::pair<int64_t, int64_t> get_position(void) const {
		return { x, y };
	}
	virtual const char* get_image_path(void) const {
		return image_path;
	}
	auto get_z_order(void) const {
		return z_order;
	}
	virtual std::pair<int, int> get_rect_hw(void) {
		return { rect.h, rect.w };
	}
	/* Other */
	void center(void) {
		x = static_cast<decltype(x)>((SCR_WIDTH - rect.w) >> 1);
		y = static_cast<decltype(y)>((SCR_HEIGHT - rect.h) >> 1);
	}
	void move_to(int64_t x, int64_t y) {
		this->x = x;
		this->y = y;
	}
	void move_from(int x, int y) {
		this->x += x;
		this->y += y;
	}
};

uint64_t _object::count = 0;
std::set<int_fast64_t> _object::z_order_set;

class _sequence : _object {
public:
};

