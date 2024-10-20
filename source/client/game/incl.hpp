﻿#pragma once

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

#include "../../api"
#include "../../net_transfer/main.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cstdarg>
#include <cmath>

#include <utility>
#include <algorithm>
#include <functional>
#include <random>

#include <vector>
#include <array>
#include <set>
#include <map>
#include <any>

#include <type_traits>
#include <typeinfo>

#include <thread>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#define cxstr_t constexpr const char*

enum ERROR {
	SUCCESS,
	INITIALISATION,
	INTEGRITY_VIOLATED,
	MISSING_ENGINE_FILE,
	OBJECT_LIMIT_REACHED
};
namespace module {
	cxstr_t core = "CORE";
	cxstr_t warn = "WARNING";
	cxstr_t ios = "IOSTREAM";
	cxstr_t audio = "AUDIO";
	cxstr_t render = "RENDER";
	cxstr_t net = "NET";
}
namespace gl {
	/*namespace font {
		TTF_Font* noto = TTF_OpenFont(".. /font/noto.ttf", 14);
	}*/
	static constexpr std::array<uint32_t, 256>(*CRC_init)(void) = [](void) {
		uint32_t CRC;
		std::array<uint32_t, 256> table = {};
		for (uint32_t i = 0; i < 256; i++) {
			CRC = i;
			for (uint32_t j = 8; j > 0; j--) {
				if (CRC & 1) {
					CRC = (CRC >> 1) ^ 0xEDB88320;
				} else {
					CRC >>= 1;
				}
			}
			table[i] = CRC;
		}
		return table;
	};
	constexpr std::array<uint32_t, 256> CRC_table = CRC_init();
	_iobuf* logfile;
	constinit float dB = -16.0f; //default
	unsigned delay;
	struct {
		uint16_t framerate = 60; //default
		void operator()(void) {
			delay = 1000 / this->framerate;
		}
	} config;
}
namespace path {
	constexpr std::array<std::pair<const char*, const uint32_t>, 10> engine { /* path | CRC */
		std::make_pair("_internal/base_library.zip", 0xD6CDE4E4),
		std::make_pair("_internal/python310.dll",0xD2698ACC),
		std::make_pair("skin_manager.exe",0xC714932),
		std::make_pair("net_transfer.dll",0x3C29C5C0),
		std::make_pair("SDL2.dll",0xADC3F513),
		std::make_pair("SDL2_image.dll",0x9AE4833C),
		std::make_pair("SDL2_mixer.dll",0x8FF78E0B),
		std::make_pair("SDL2_net.dll",0x3C0883EB),
		std::make_pair("SDL2_ttf.dll",0xE34AC27F),
		std::make_pair("x_input.exe",0x21DF94C7)
	};
	namespace img {
		cxstr_t null = "../img/null.png";
		cxstr_t menu_bg = "../img/menu/bg.png";
		cxstr_t menu_button = "../img/button/menu.png";
	}
	namespace bgm {
		cxstr_t menu = "../bgm/menu.ogg";
	}
	namespace sfx {
		cxstr_t error = "../sfx/critical_error.ogg";
		cxstr_t quit = "../sfx/shutdown.ogg";
	}
}
namespace math {
	constexpr float pi = 3.14159265358979323; /* Should be enough */
}