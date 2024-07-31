#pragma once

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

#include "../api"
#include "../net_transfer/main.h"

#include <stdio.h> //
#include <stdlib.h> //
#include <string.h> //
#include <stdint.h> //
#include <math.h>
#include <time.h> //

#include <algorithm>
#include <utility> //
#include <thread>
#include <vector> //
#include <set> //
#include <type_traits>
#include <ranges>

#include <SDL.h> //
#include <SDL_image.h> //
#include <SDL_mixer.h> //
#include <SDL_ttf.h>

const long double pi = 3.141592653589793; /* Should be enough */

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
/* Paths */
namespace path {
	std::vector<std::pair<const char*, const uint32_t>> engine { /* path | CRC */
		{"_internal/base_library.zip",0x3B0952F2},
		{"_internal/python310.dll",0xD2698ACC},
		//{"game.exe",0x},
		{"get_skin_list.exe",0xD932A50B},
		//{"net_transfer.dll",0x},
		{"SDL2.dll",0xADC3F513},
		{"SDL2_image.dll",0x9AE4833C},
		{"SDL2_mixer.dll",0x8FF78E0B},
		{"SDL2_net.dll",0x3C0883EB},
		{"SDL2_ttf.dll",0xE34AC27F},
		{"x_input.exe",0x21DF94C7}
	};
	namespace img {
		const char* menu_bg = "../img/menu/bg.png";
	}
	namespace bgm {
		const char* menu = "../bgm/menu.ogg";
	}
	namespace sfx {
		const char* error = "../sfx/critical_error.ogg";
		const char* quit = "../sfx/shutdown.ogg";
	}
}
