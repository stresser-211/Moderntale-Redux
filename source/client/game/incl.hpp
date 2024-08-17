#pragma once

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

#include "../../api"
#include "../../net_transfer/main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

#include <utility>
#include <algorithm>
#include <vector>
#include <set>
#include <any>
#include <type_traits>
#include <typeinfo>
#include <thread>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#define obj_t auto* __restrict

constexpr uint8_t MTX_version = 0x1;
constexpr int_fast64_t operator""Z(unsigned long long i) {
	return static_cast<int_fast64_t>(i);
}
const auto pi = 3.14159265358979323; /* Should be enough */
const uint8_t _framerate = 60;
const auto _duration = 1000 / _framerate;

enum ERROR {
	SUCCESS,
	INITIALISATION,
	INTEGRITY_VIOLATED,
	MISSING_ENGINE_FILE,
	OUT_OF_Z_ORDER
};
namespace module {
	const char* core = "CORE";
	const char* error = "ERROR";
	const char* warning = "WARNING";
	const char* ios = "IOSTREAM";
	const char* audio = "AUDIO";
	const char* render = "RENDER";
	const char* net = "NET";
}
namespace path {
	std::vector<std::pair<const char*, const uint32_t>> engine { /* path | CRC */
		{"_internal/base_library.zip",0xD6CDE4E4},
		{"_internal/python310.dll",0xD2698ACC},
		//{"game.exe",0x},
		{"skin_manager.exe",0xC714932},
		//{"net_transfer.dll",0x},
		{"SDL2.dll",0xADC3F513},
		{"SDL2_image.dll",0x9AE4833C},
		{"SDL2_mixer.dll",0x8FF78E0B},
		{"SDL2_net.dll",0x3C0883EB},
		{"SDL2_ttf.dll",0xE34AC27F},
		{"x_input.exe",0x21DF94C7}
	};
	namespace img {
		const char* null = "../img/null.png";
		const char* menu_bg = "../img/menu/bg.png";
		const char* menu_button = "../img/button/menu.png";
	}
	namespace bgm {
		const char* menu = "../bgm/menu.ogg";
	}
	namespace sfx {
		const char* error = "../sfx/critical_error.ogg";
		const char* quit = "../sfx/shutdown.ogg";
	}
}
