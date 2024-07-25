#pragma once

#include "incl.hpp"
#include "io.hpp"

class _Mus {
public:
};

void _oggplay(const char* path, float dB) {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	auto dB_to_volume = [dB]() {
		float linear_scale = pow(10.0f, dB / 20.0f);
		int SDL_volume = static_cast<int>(linear_scale * MIX_MAX_VOLUME);
		if (SDL_volume > MIX_MAX_VOLUME) SDL_volume = MIX_MAX_VOLUME;
		if (SDL_volume < 0) SDL_volume = 0;
		return SDL_volume;
	};
	Mix_Music* file = Mix_LoadMUS(path);
	Mix_VolumeMusic(dB_to_volume());
	if (Mix_PlayMusic(file, -1) == -1) {
		stacktrace(module::error, "Error playing \"%s\": %s.", path, Mix_GetError());
	} else {
		stacktrace(module::audio, "Playing \"%s\".", path);
	}
}
