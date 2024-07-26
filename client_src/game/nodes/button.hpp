#pragma once

#include "../incl.hpp"
#include "../functions.hpp"
#include "object.hpp"

class _Button : _Object {
public:
	_Button(SDL_Renderer* rend, int_fast64_t z_order, const char* image, int x, int y) : _Object(rend, z_order, image, x, y) {
		int i;
	}
};
