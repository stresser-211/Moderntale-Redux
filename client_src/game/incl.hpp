#pragma once

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

#include "../api"
#include "../net_transfer/main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#include <algorithm>
#include <utility>
#include <thread>
#include <vector>
#include <type_traits>
#include <ranges>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

const long double pi = 3.141592653589793; /* Should be enough */

enum struct LOCALE {
	EN,
	RU,
	MD
};
enum ERROR {
	SUCCESS,
	INITIALISATION,
	INTEGRITY_VIOLATED,
	MISSING_ENGINE_FILE,
	MISSING_TEXTURE,
	MISSING_AUDIO_FILE,
	MISSING_FONT
};
/* Global varibles */
namespace gl {
	uint32_t CRC_table[256];
	LOCALE locale;
	constexpr int version = 0x1;
	_iobuf* logfile;
}
namespace module {
	const char* core = "CORE";
	const char* error = "ERROR";
	const char* ios = "IOSTREAM";
	const char* audio = "AUDIO";
	const char* render = "RENDER";
	const char* net = "NET";
	const char* key = "KEY";
	const char* node = "NODE";
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
		{"x_input.exe",0x9432C704}
	};
	namespace bg {
		const char* menu = "../img/menu/bg.png";
	}
}
/* Localisation */
namespace menu {
	namespace main {
		std::vector<const char*> play {"[Play]","[Играть]","[Joacă]"};
		std::vector<const char*> settings {"[Settings]","[Настройки]","[Setări]"};
		std::vector<const char*> about {"[About]","[Об игре]","[Despre joc]"};
		std::vector<const char*> quit {"[Quit]","[Выйти]","[Ieși]"};
		std::vector<const char*> quit_confirm {"Quit the game?","Покинуть игру?","Să ieși de la joc?"};
		std::vector<const char*> version {"Version:","Версия:","Versiune:"};
	}
	namespace multiplayer {
		std::vector<const char*> add {"[Add a server]","[Добавить сервер]","[Adaugă un server]"};
		std::vector<const char*> direct_connect {"[Direct connect]","[Подключиться]","[Conectarea directă]"};
		std::vector<const char*> remove {"[Remove the server]","[Убрать сервер]","[Elimină serverul]"};
		std::vector<const char*> refresh {"[Refresh]","[Обновить]","[Actualizare]"};
		std::vector<const char*> bookmark {"[Add to favourites]","[Добавить в избранное]","[Adaugă la favorite]"};
		std::vector<const char*> connecting {"Connecting","Подключаемся","Ne conectăm"};
		std::vector<const char*> connection_error {"Connection error:","Ошибка подключения:","Eroară de conectare:"};
	}
	namespace settings {
		std::vector<const char*> vsync {"[V-sync]","[Вертикальная синхронизация]","[Sincronizare verticală]"};
		std::vector<const char*> custom_fps {"[Custom framerate]","[Пользовательская частота кадров]","[Rata de cadre personalizată]"};
	}
	namespace about {
		std::vector<const char*> version {"Version:","Версия:","Versiune:"};
		std::vector<const char*> developed_with{"Developed with:","Разработано с использованием:","Dezvoltat folosind:"};
		std::vector<const char*> thanks_to {"Special thanks:","Особые благодарности:","Mulțumiri speciale:"};
	}
}
namespace popup {
	std::vector<const char*> yes {"[Yes]","[Да]","[Da]"};
	std::vector<const char*> no {"[No]","[Нет]","[Nu]"};
	std::vector<const char*> ok {"[Got it]","[Понятно]","[Am înțeles]"};
	std::vector<const char*> info {"[Information]","[Информация]","[Informație]"};
	std::vector<const char*> warning {"[Warning!]","[Внимание!]","[Atenție!]"};
	std::vector<const char*> error {"[Error!]","[Ошибка!]","[Eroară!]"};
}
