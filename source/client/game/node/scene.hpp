#pragma once

#include "../incl.hpp"
#include "../utility.hpp"
#include "basic_objects.hpp"

template <class T> concept obj_allowed_t = std::is_base_of_v<_object, T> || std::is_same_v<_object, T>;

class _scene : _object {
	static uint_least16_t id;
	SDL_Renderer* rend;
public:
	std::map<int_fast64_t, obj_t> objects;

	_scene() = delete;
	_scene(SDL_Renderer* rend) : _object(rend, INT_FAST64_MIN, NULL, NULL, NULL, NULL, NULL, NULL) , rend(rend) {
		id++;
	}
	~_scene() {
		for (decltype(auto) iter : objects) {
			destroy(iter);
		}
	}

	/* Render */
public:
	inline void render(SDL_Renderer* rend, const obj_t& obj) {
		SDL_Texture* texture = NULL;
		SDL_Rect rect = {};
		auto _rend_core = [&](auto tmp) {
			tmp->uniquify_z_order();
			texture = tmp->get_texture();
			auto [h, w] = tmp->get_rect_hw();
			auto [x, y] = tmp->get_position();
			rect.x = x;
			rect.y = y;
			rect.h = h;
			rect.w = w;
		};
		if (obj.type() == typeid(_object*)) {
			_rend_core(std::any_cast<_object*>(obj));
		} else {
			_rend_core(std::any_cast<_button*>(obj));
		}
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
		SDL_RenderCopy(rend, texture, NULL, &rect);
		SDL_RenderPresent(rend);
	}
	void rerender(void) {
		for (decltype(auto) iter : objects) {
			render(rend, iter.second);
		}
	};

	/* Object management */
	template <obj_allowed_t T> void create_object(int x, int y, int_fast64_t z_order = 1Z, const char* path = path::img::null, uint8_t alpha = ((uint8_t)255), uint16_t rot = ((uint16_t)0), float scale = 100.0f) {
		objects.emplace(std::make_pair(z_order, obj_t(new T(rend, z_order, path, x, y, alpha, rot, scale))));
	}
	template <obj_allowed_t T> void create_object(T* obj) {
		objects.emplace(std::make_pair(obj->uniquify_z_order(), obj_t(obj)));
	}
	void destroy(auto obj) {
		if (obj.second.has_value()) {
			if (obj.second.type() == typeid(_object*)) {
				delete std::any_cast<_object*>(obj.second);
			} else {
				delete std::any_cast<_button*>(obj.second);
			}
			objects.find(obj.first);
			obj.second.reset();
		}
	}
	template <obj_allowed_t T> auto get(int_fast64_t z) {
		return std::any_cast<T*>(objects[objects.find(z)->first]);
	}
};

uint_least16_t _scene::id = 0;

int scene_switch() {
	return 0;
}