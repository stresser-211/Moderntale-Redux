#pragma once

#include "incl.hpp"
#include "utility.hpp"

constinit static bool run = true;

static std::vector<Mix_Chunk*> audio_chunks;

enum CHANNEL {
	CH_MUS,
	CH_SND,
	CH_ALL = -1
};

void snd_stop(CHANNEL channel) {
	switch (channel) {
	default:
		run = false;
		Mix_FreeChunk(audio_chunks.back());
		audio_chunks.pop_back();
		break;
	case CH_ALL:
		run = false;
		std::for_each(audio_chunks.begin(), audio_chunks.end(), [](auto chunk) {
			Mix_FreeChunk(chunk);
		});
		audio_chunks.clear();
		break;
	}
}
void snd_play(const char* path, CHANNEL channel, bool log = true) {
	auto cleanup = []() {
		run = false;
		if (!audio_chunks.empty()) {
			Mix_FreeChunk(audio_chunks.back());
			audio_chunks.pop_back();
		}
	};
	int ch = channel;
	if (Mix_Playing(channel)) {
		snd_stop(channel);
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
		if (log) stacktrace(module::audio, "Couldn't open audio device: %s", Mix_GetError());
		cleanup(); return;
	}
	Mix_Chunk* audio = Mix_LoadWAV(path);
	if (!audio) {
		if (log) stacktrace(module::audio, "Couldn't load audio file: %s (%s)", Mix_GetError(), path);
		cleanup(); return;
	}
	audio_chunks.emplace(audio_chunks.begin(), audio);
	int(*dB_to_volume)(void) = [](void) {
		float linear = expf(gl::dB * 0.115129254f); //pow(10.0f, gl::dB / 20.0f);
		int volume = static_cast<int>(linear * MIX_MAX_VOLUME);
		if (volume > MIX_MAX_VOLUME) volume = MIX_MAX_VOLUME;
		if (volume < 0) volume = 0;
		return volume;
	};
	auto play = [&](auto ch) {
		if (Mix_PlayChannel(ch, audio, 0) >= 0) {
			if (log) stacktrace(module::audio, "Playing \"%s\".", path);
		} else {
			if (log) stacktrace(module::audio, "Error playing \"%s\": %s.", path, Mix_GetError());
		}
	};
	Mix_VolumeChunk(audio, dB_to_volume());
	if (ch == CH_MUS) {
		play(CH_MUS);
		goto PLAYING;
	}
	while (1) {
		if (ch == 0x11) {
			if (log) stacktrace(module::audio, "All channels are busy. Audio discarded.");
			break;
		}
		if (Mix_Playing(ch)) {
			ch++; continue;
		}
		play(ch); break;
	}
PLAYING:
	while (Mix_Playing(ch)) {
		FRAMERATE_DELAY();
	}
	cleanup();
}
void snd_loop(const char* path, CHANNEL channel) {
	std::thread([&]() {
		run = true;
		stacktrace(module::audio, "Playing \"%s\".", path);
		do {
			if (Mix_Playing(channel) != 1) {
				snd_play(path, channel, false);
			}
		} while (run);
	}).detach();
}
