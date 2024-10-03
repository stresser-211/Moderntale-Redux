#pragma once

#include "../incl.hpp"
#include "../utility.hpp"
#include "basic_objects.hpp"

template <class T> concept obj_allowed_t = std::is_base_of_v<object, T> || std::is_same_v<object, T>;

class scene : private object {
	static uint_least16_t id;
	SDL_Renderer* rend;
	/* TODO: make this work
	using type_info = std::reference_wrapper<const std::type_info>;
	struct type_info_hash {
		std::size_t operator()(type_info const& info) const {
			return info.get().hash_code();
		}
	};
	struct type_info_equal {
		bool operator()(type_info const& lhs, type_info const& rhs) const {
			return lhs.get() == rhs.get();
		}
	};
	std::unordered_map<type_info, std::function<void*(const std::any&)>, type_info_hash, type_info_equal> types = {
		std::make_pair(std::cref(typeid(object*)),
			[](const std::any& obj) {
				return std::any_cast<object*>(obj);
			}),
		std::make_pair(std::cref(typeid(button*)),
			[](const std::any& obj) {
				return std::any_cast<button*>(obj);
			}),
		std::make_pair(std::cref(typeid(sequence*)),
			[](const std::any& obj) {
				return std::any_cast<sequence*>(obj);
			})
	};*/
public:
	std::map<int_fast64_t, std::any> objects;
	scene(void) = delete;
	scene(SDL_Renderer* rend) : object(rend, INT_FAST64_MIN, NULL, NULL, NULL, NULL, NULL, NULL) , rend(rend) {
		id++;
	}
	~scene(void) {
		std::for_each(objects.begin(), objects.end(), [&](auto obj) {
			destroy(obj.second);
		});
		objects.clear();
	}

	/* Render */
public:
	inline void render(SDL_Renderer* rend, const std::any& obj) {
		if (obj.has_value()) {
			SDL_Texture* texture = NULL;
			SDL_Rect rect = {};
			auto prepare = [&](auto tmp) {
				tmp->uniquify_z_order();
				texture = tmp->get_texture();
				auto [h, w] = tmp->get_rect_hw();
				auto [x, y] = tmp->get_position();
				rect.x = x; rect.y = y; rect.h = h; rect.w = w;
			};
			if (obj.type() == typeid(object*)) {
				prepare(std::any_cast<object*>(obj));
			} else if (obj.type() == typeid(button*)) {
				prepare(std::any_cast<button*>(obj));
			} else if (obj.type() == typeid(sequence*)) {
				prepare(std::any_cast<sequence*>(obj));
			}
			SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
			SDL_RenderCopy(rend, texture, NULL, &rect);
			SDL_RenderPresent(rend);
		}
	}
	void rerender(void) {
		for (decltype(auto) iter : objects) {
			render(rend, iter.second);
		}
	};

	/* Object management */
public:
	template <obj_allowed_t T> void create_object(int x, int y, int_fast64_t z_order = 1Z, const char* path = path::img::null, uint8_t alpha = ((uint8_t)255), uint16_t rot = ((uint16_t)0), float scale = 100.0f) {
		objects.emplace(std::make_pair(z_order, std::any(new T(rend, z_order, path, x, y, alpha, rot, scale))));
	}
	template <obj_allowed_t T> void create_object(T* obj) {
		objects.emplace(std::make_pair(obj->uniquify_z_order(), obj_t(obj)));
	}
private:
	void destroy(std::any obj) {
		if (obj.has_value()) {
			if (obj.type() == typeid(object*)) {
				delete std::any_cast<object*>(obj);
			} else if (obj.type() == typeid(button*)) {
				delete std::any_cast<button*>(obj);
			} else if (obj.type() == typeid(sequence*)) {
				delete std::any_cast<sequence*>(obj);
			}
		}
	}
	void destroy(int_fast64_t key) {
		decltype(auto) obj = objects.find(key);
		destroy(obj->second);
	}
public:
	void remove(int_fast64_t key) {
		destroy(key);
		objects.erase(key);
	}
	template <obj_allowed_t T> auto get(int_fast64_t z) {
		return std::any_cast<T*>(objects[objects.find(z)->first]);
	}
};

class actor {
	object player;
public:
	actor(void) = delete;
	actor(SDL_Renderer* rend, const char* skin, int64_t x, int64_t y, uint8_t alpha)
		: player(rend, skin, x, y, alpha)
	{
	}
};

uint_least16_t scene::id = 0;

int scene_switch() {
	return 0;
}