#pragma once

#include "../incl.hpp"
#include "../functions.hpp"
#include "object.hpp"

class _button : public _object {
	TTF_Font* font;
public:
	_button() = delete;
	_button(SDL_Renderer* rend, int_fast64_t z_order, const char* image, int64_t x, int64_t y, uint8_t alpha, uint16_t rot, float scale)
		: _object(rend, z_order, image, x, y, alpha, rot, scale) {}
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
