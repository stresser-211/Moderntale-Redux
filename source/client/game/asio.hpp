#pragma once

#include "incl.hpp"
#include "utility.hpp"

enum CHANNEL {
	CH_MUS,
	CH_SND
};

class audio {
	bool corrupted;
	const char* path;
	Mix_Chunk* chunk;
	CHANNEL current_channel;
	bool cycle;
public:
	audio(void) = delete;
	audio(const char* path) : path(path), cycle(false), corrupted(false) {
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
			stacktrace(module::audio, "Couldn't open audio device: %s", Mix_GetError());
			corrupted = true;  return;
		}
		chunk = Mix_LoadWAV(path);
		if (!chunk) {
			stacktrace(module::audio, "Couldn't load audio file: %s (%s)", Mix_GetError(), path);
			corrupted = true; return;
		}
		Mix_VolumeChunk(chunk, [](void) {
			float linear = expf(gl::dB * 0.115129254f); //pow(10.0f, gl::dB / 20.0f);
			int volume = static_cast<int>(linear * MIX_MAX_VOLUME);
			if (volume > MIX_MAX_VOLUME) volume = MIX_MAX_VOLUME;
			if (volume < 0) volume = 0;
			return volume;
		}.operator()());
	}
	~audio(void) {
		Mix_FreeChunk(chunk);
	}
	void play(CHANNEL channel = CH_SND) {
		if (corrupted) {
			stacktrace(module::audio, "Error playing \"%s\": audio chunk corrupted.", path);
			return;
		}
		auto play = [&](void) {
			if (Mix_PlayChannel(channel, chunk, 0) >= 0) {
				stacktrace(module::audio, "Playing \"%s\".", path);
			} else {
				stacktrace(module::audio, "Error playing \"%s\": %s.", path, Mix_GetError());
			}
		};
		int ch = channel;
		if (channel == CH_MUS) {
			play(); return;
		}
		while (1) {
			if (ch == 0x11) {
				stacktrace(module::audio, "All channels are busy. Audio discarded.");
				break;
			}
			if (Mix_Playing(channel)) {
				ch++; continue;
			}
			play(); break;
		}
	}
	void stop(void) {
		cycle = false;
		Mix_HaltChannel(current_channel);
	}
	void loop(CHANNEL channel = CH_SND) {
		if (corrupted) {
			stacktrace(module::audio, "Error playing \"%s\": audio chunk corrupted.", path);
			return;
		}
		cycle = true;
		do {
			if (Mix_Playing(channel) != 1) {
				play(current_channel);
			}
		} while (cycle);
	}
};
