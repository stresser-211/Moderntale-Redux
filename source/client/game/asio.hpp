#pragma once

#include "incl.hpp"
#include "utility.hpp"

constinit static std::atomic<bool> run = true;

enum CHANNEL {
	CH_MUS,
	CH_SND,
	CH_ALL = -1
};

void snd_play(const char* path, CHANNEL channel, bool log = true) {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
		if (log) stacktrace(module::audio, "Couldn't open audio device: %s", Mix_GetError());
		run = false; return;
	}
	Mix_AllocateChannels(0x10);
	Mix_Chunk* audio = Mix_LoadWAV(path);
	if (!audio) {
		if (log) stacktrace(module::audio, "Couldn't load audio file: %s", path);
		run = false; return;
	}
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
	if (channel == CH_MUS) {
		play(CH_MUS);
		return;
	}
	int ch = CH_MUS;
	while (1) {
		if (ch == 0x11) {
			if (log) stacktrace(module::audio, "All the channels are busy. Audio discarded.");
			break;
		}
		if (Mix_Playing(ch)) {
			ch++; continue;
		}
		play(ch); break;
	}
	Mix_FreeChunk(audio);
}
auto snd_loop(const char* path, CHANNEL channel) {
	run = true;
	stacktrace(module::audio, "Playing \"%s\".", path);
	return std::thread([&]() {
		do {
			if (Mix_Playing(channel) != 1) {
				snd_play(path, channel, false);
			}
		} while (run);
	}).detach();
}
void snd_stop(CHANNEL channel) {
	if (channel == CH_MUS || channel == CH_ALL) {
		run = false;
	}
	Mix_HaltChannel(channel);
}