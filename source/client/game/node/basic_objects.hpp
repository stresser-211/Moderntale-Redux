#pragma once

#include "../incl.hpp"
#include "../utility.hpp"

class object {
	void _constructor(SDL_Renderer* rend, int_fast64_t z, const char* image_path) {
		this->z = insert_z_order(z);
		if (image_path) {
			this->image_path = image_path;
			texture = IMG_LoadTexture(rend, image_path);
		} else {
			this->image_path = path::img::null;
			texture = NULL;
		}
		if (!texture) {
			stacktrace(module::warn, "Couldn't load \"%s\". Object discarded.", image_path);
			obj_count.erase(z);
		} else {
			SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
		}
		//todo: proper exception handler
	}
	friend class actor;
	object(SDL_Renderer* rend, const char* skin, int64_t x, int64_t y, uint8_t alpha)
		: x(x), y(y), alpha(alpha)
	{
		//todo: implementation
	}
protected:
	SDL_Texture* texture;
	SDL_Rect rect;
	const char* image_path;
	uint_least32_t group;
	int_fast64_t z; /* 18,446,744,073,709,551,615 objects ought to be enough for anybody */
	static std::set<int_fast64_t> obj_count;
	int64_t x;
	int64_t y;
	uint8_t alpha;
	uint16_t rot;
	float scale;

	static int_fast64_t insert_z_order(int_fast64_t z) {
		if (z != 0) {
			if (obj_count.find(z) != obj_count.end()) {
				stacktrace(module::warn, "z_order (%lld) is already in use. New unique z_order: %lld", z, uniquify_z_order(z));
				if (z == 0) {
					stacktrace(module::core, "Object limit reached.");
					obj_count.erase(z);
					throw OBJECT_LIMIT_REACHED;
				}
			}
			obj_count.insert(z);
			return z;
		}
		stacktrace(module::warn, "Attempted to use zero as a z_order (reserved for player). Object discarded.");
		throw OBJECT_LIMIT_REACHED;
	}
	static int_fast64_t uniquify_z_order(int_fast64_t& z) {
		if (z >= 0) {
			while (obj_count.find(z) != obj_count.end()) {
				++z;
				if (z == INT_FAST64_MAX) {
					goto EXCEPTION;
				}
			}
		} else {
			while (obj_count.find(z) != obj_count.end()) {
				--z;
				if (z == INT_FAST64_MIN) {
					goto EXCEPTION;
				}
			}
		}
		return z;
	EXCEPTION:
		z = 0;
		return 0;
	}
public:
	void uniquify_z_order(void) {
		uniquify_z_order(this->z);
	}
	object(void) = delete;
	object(SDL_Renderer* rend, int_fast64_t z, const char* image, int64_t x, int64_t y, uint8_t alpha, uint16_t rot, float scale)
		: x(x), y(y), alpha(alpha), rot(rot), scale(scale)
	{
			_constructor(rend, z, image); //rewrite
	}
	object(SDL_Renderer* rend, object* obj)
		: x(obj->x), y(obj->y), alpha(obj->alpha), rot(obj->rot), scale(obj->scale)
	{
			_constructor(rend, uniquify_z_order(obj->z), obj->image_path);
	}
	virtual ~object(void) {
		SDL_DestroyTexture(texture);
		obj_count.erase(z);
	}

	/* Get */
	virtual SDL_Texture* get_texture(void) const {
		return texture;
	}
	auto get_position(void) const {
		return std::make_pair(x, y);
	}
	auto get_z_order(void) const {
		return z;
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
class button : public object {
	TTF_Font* font;
public:
	button(void) = delete;
	button(SDL_Renderer* rend, int_fast64_t z, const char* image, int64_t x, int64_t y, uint8_t alpha, uint16_t rot, float scale)
		: object(rend, z, image, x, y, alpha, rot, scale)
	{
	}
	button(SDL_Renderer* rend, button* button)
		: object(rend, uniquify_z_order(button->z), button->image_path, button->x, button->y, button->alpha, button->rot, button->scale)
	{
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
class sequence : public object {
	struct frame_t {
		SDL_Texture* texture;
		const char* path;
	};
	std::array<frame_t, 60> frames;
	uint8_t current_frame;
public:
	sequence(void) = delete;
	sequence(SDL_Renderer* rend, int_fast64_t z, int x, int y, const char* animlist, uint8_t alpha, uint16_t rot, float scale)
		: object(rend, z, "", x, y, alpha, rot, scale)
	{
	}
	sequence(SDL_Renderer* rend, sequence* seq)
		: object(rend, uniquify_z_order(seq->z), seq->image_path, seq->x, seq->y, seq->alpha, seq->rot, seq->scale)
	{
	}
	~sequence(void) {
		std::for_each(frames.begin(), frames.end(), [](auto frame) {
			SDL_DestroyTexture(frame.texture);
		});
		obj_count.erase(z);
	}
	virtual SDL_Texture* get_texture(void) const override {
		return frames[current_frame].texture;
	}
	virtual const char* get_image_path(void) const override {
		return frames[current_frame].path;
	}
	virtual std::pair<int, int> get_rect_hw(void) const override {
		return std::make_pair(rect.h, rect.w);
	}
};

std::set<int_fast64_t> object::obj_count {
};