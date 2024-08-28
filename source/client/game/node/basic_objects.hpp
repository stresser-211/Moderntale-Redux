#pragma once

#include "../incl.hpp"
#include "../utility.hpp"

class _object {
	void _constructor(SDL_Renderer* rend, int_fast64_t z_order, const char* image_path) {
		this->z_order = insert_z_order(z_order);
		if (image_path) {
			this->image_path = image_path;
			texture = IMG_LoadTexture(rend, image_path);
		} else {
			this->image_path = path::img::null;
			texture = NULL;
		}
		if (!texture) {
			stacktrace(module::warning, "Couldn't load \"%s\". Object discarded.", image_path);
			obj_count.erase(z_order);
		} else {
			SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
		}
		//todo: exception handler
	}
protected:
	SDL_Texture* texture;
	SDL_Rect rect;
	const char* image_path;
	uint_least32_t group;
	int_fast64_t z_order; /* 18,446,744,073,709,551,615 objects ought to be enough for anybody */
	static std::set<int_fast64_t> obj_count; //to fix std::any reset
	int64_t x;
	int64_t y;
	uint8_t alpha;
	uint16_t rot;
	float scale;

	static int_fast64_t insert_z_order(int_fast64_t z_order) {
		if (z_order != 0) {
			if (obj_count.find(z_order) != obj_count.end()) {
				stacktrace(module::warning, "z_order (%lld) is already in use. New unique z_order: %lld", z_order, uniquify_z_order(z_order));
				if (z_order == 0) {
					stacktrace(module::warning, "No free z_order left. Object discarded.");
					obj_count.erase(z_order);
					throw OUT_OF_Z_ORDER;
				}
			}
			obj_count.insert(z_order);
			return z_order;
		} else {
			stacktrace(module::warning, "Attempted to use zero as a z_order (reserved for player). Object discarded.");
			throw OUT_OF_Z_ORDER;
		}
	}
	static int_fast64_t uniquify_z_order(int_fast64_t& z_order) {
		if (z_order >= 0) {
			while (obj_count.find(z_order) != obj_count.end()) {
				++z_order;
				if (z_order == INT_FAST64_MAX) {
					goto EXCEPTION;
				}
			}
		} else {
			while (obj_count.find(z_order) != obj_count.end()) {
				--z_order;
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
	void uniquify_z_order() {
		uniquify_z_order(this->z_order);
	}
	_object(void) = delete;
	_object(SDL_Renderer* rend, int_fast64_t z_order, const char* image, int64_t x, int64_t y, uint8_t alpha, uint16_t rot, float scale)
		: x(x), y(y), alpha(alpha), rot(rot), scale(scale) {
			_constructor(rend, z_order, image);
	}
	_object(SDL_Renderer* rend, _object* obj)
		: x(obj->x), y(obj->y), alpha(obj->alpha), rot(obj->rot), scale(obj->scale) {
			_constructor(rend, uniquify_z_order(obj->z_order), obj->image_path);
	}
	virtual ~_object(void) {
		SDL_DestroyTexture(texture);
		obj_count.erase(z_order);
	}

	/* Get */
	auto get_texture(void) const {
		return texture;
	}
	auto get_position(void) const {
		return std::make_pair(x, y);
	}
	auto get_z_order(void) const {
		return z_order;
	}
	virtual const char* get_image_path(void) const {
		return image_path;
	}
	virtual std::pair<int, int> get_rect_hw(void) const {
		return std::make_pair(rect.h, rect.w);
	}

	/* Position */
	void center(void) {
		x = static_cast<decltype(x)>((SCR_WIDTH - rect.w) >> 1);
		y = static_cast<decltype(y)>((SCR_HEIGHT - rect.h) >> 1);
	}
	template <is_positive Int> void move_to(Int x, Int y) {
		this->x = x;
		this->y = y;
	}
	template <is_positive Int> void move_from(Int x, Int y) {
		this->x += x;
		this->y += y;
	}
};

class _button : public _object {
	TTF_Font* font;
public:
	_button() = delete;
	_button(SDL_Renderer* rend, int_fast64_t z_order, const char* image, int64_t x, int64_t y, uint8_t alpha, uint16_t rot, float scale)
		: _object(rend, z_order, image, x, y, alpha, rot, scale) {
	}
	bool was_clicked(int& mouse_x, int& mouse_y) {
		int txtrw, txtrh;
		if (texture) {
			SDL_QueryTexture(texture, NULL, NULL, &txtrw, &txtrh);
		} else {
			return false;
		}
		auto [xpos, ypos] = get_position();
		return (mouse_x >= xpos && mouse_x <= xpos + txtrw && mouse_y >= ypos && mouse_y <= ypos + txtrh);
	}
};

class _sequence : _object {
public:
};

std::set<int_fast64_t> _object::obj_count {
};