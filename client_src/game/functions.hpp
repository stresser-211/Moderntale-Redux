#pragma once

#include "incl.hpp"
#include "init.hpp"
#include "nodes/object.hpp"
#include "../net_transfer/main.h"

uint32_t get_CRC(_iobuf* file) {
	uint32_t CRC = 0xFFFFFFFF;
	unsigned char buffer[4096];
	size_t bytes_read;
	while ((bytes_read = fread(buffer, 1, 4096, file)) > 0) {
		for (size_t i = 0; i < bytes_read; i++) {
			uint8_t byte = buffer[i];
			CRC = (CRC >> 8) ^ gl::CRC_table[(CRC ^ byte) & 0xFF];
		}
	}
	fclose(file);
	return CRC ^ 0xFFFFFFFF;
}
void _render(SDL_Renderer* rend, _Object* obj) {
	SDL_RenderCopy(rend, obj->get_texture(), NULL, NULL);
	SDL_RenderPresent(rend);
}
_Object* create_object(SDL_Renderer* rend, uint_fast64_t z_order, const char* path, int x, int y) {
	return new _Object(rend, z_order, path, x, y);
}
_Object* create_object(SDL_Renderer* rend, uint_fast64_t z_order, const char* path, int x, int y, uint8_t alpha, uint16_t rot, float scale) {
	return new _Object(rend, z_order, path, x, y, alpha, rot, scale);
}
void destroy(_Object* ptr) {
	if (ptr != nullptr) delete ptr;
}
