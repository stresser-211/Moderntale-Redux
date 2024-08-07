#pragma once

#include "incl.hpp"
#include "init.hpp"
#include "global.hpp"
#include "io.hpp"
#include "nodes/object.hpp"
#include "nodes/button.hpp"
#include "../net_transfer/main.h"

template <class T> concept obj_allowed_t = std::is_base_of<_object, T>::value || std::is_same<_object, T>::value;

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
template <obj_allowed_t T> static SDL_Texture* _render_core(const std::any& obj, SDL_Rect& rect) {
	SDL_Texture* texture = std::any_cast<T*>(obj)->get_texture();
	auto [h, w] = std::any_cast<T*>(obj)->get_rect_hw();
	auto [x, y] = std::any_cast<T*>(obj)->get_position();
	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = w;
	return texture;
}
void _render(SDL_Renderer* rend, const std::any obj) {
	SDL_Texture* texture = nullptr;
	SDL_Rect rect = {};
	if (obj.type() == typeid(_object*)) {
		texture = _render_core<_object>(obj, rect);
	} else {
		texture = _render_core<_button>(obj, rect);
	}
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(rend, texture, NULL, &rect);
	SDL_RenderPresent(rend);
}
template <obj_allowed_t T> auto create_object(SDL_Renderer* rend, int_fast64_t z_order, int x, int y, const char* path = path::img::null, uint8_t alpha = ((uint8_t)255), uint16_t rot = ((uint16_t)0), float scale = 100.0f) {
	gl::objects.emplace_back(std::make_pair(std::any(new T(rend, z_order, path, x, y, alpha, rot, scale)), z_order));
	return std::any_cast<T*>(gl::objects.back().first);
}
template <obj_allowed_t T> auto create_object(SDL_Renderer* rend, T* obj) {
	gl::objects.emplace_back(std::make_pair(std::any(obj), obj->get_z_order()));
	return std::any_cast<T*>(gl::objects.back().first);
}
void _destroy(std::any& ptr) {
	if (ptr.has_value()) {
		gl::objects.erase(std::find_if(gl::objects.begin(), gl::objects.end(), [&ptr](auto& a) {
			return a.first.type() == ptr.type() && a.first.has_value() && std::any_cast<void*>(&a.first) == std::any_cast<void*>(&ptr);
		}));
		ptr.reset();
	}
}
