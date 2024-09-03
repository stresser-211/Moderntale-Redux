#pragma once

#include "incl.hpp"

enum struct LOCALE {
	EN,
	RU,
	MD,
	_END
};

#define locale_t constexpr std::array<const char*, static_cast<size_t>(LOCALE::_END)>

namespace menu {
	namespace start {
		locale_t play = {"[Play]", "[Играть]", "[Joacă]"};
		locale_t settings = {"[Settings]","[Настройки]","[Setări]"};
		locale_t about = {"[About]","[Об игре]","[Despre joc]"};
		locale_t quit = {"[Quit]","[Выйти]","[Ieși]"};
		locale_t quit_confirm = {"Quit the game?","Покинуть игру?","Să ieși de la joc?"};
		locale_t version = {"Version:","Версия:","Versiune:"};
	}
	namespace multiplayer {
		locale_t add = {"[Add a server]","[Добавить сервер]","[Adaugă un server]"};
		locale_t direct_connect = {"[Direct connect]","[Подключиться]","[Conectarea directă]"};
		locale_t remove = {"[Remove the server]","[Убрать сервер]","[Elimină serverul]"};
		locale_t refresh = {"[Refresh]","[Обновить]","[Actualizare]"};
		locale_t bookmark = {"[Add to favourites]","[Добавить в избранное]","[Adaugă la favorite]"};
		locale_t connecting = {"Connecting","Подключаемся","Ne conectăm"};
		locale_t connection_error = {"Connection error:","Ошибка подключения:","Eroară de conectare:"};
	}
	namespace settings {
		locale_t vsync = {"[V-sync]","[Вертикальная синхронизация]","[Sincronizare verticală]"};
		locale_t music_volume = {"[Music volume]","[Громкость музыки]","[Volumul muzicii]"};
		locale_t sfx_volume = {"[SFX volume]","[Громкость звуков]","[Volumul sunetelor]"};
	}
	namespace about {
		locale_t version = {"Version:","Версия:","Versiune:"};
		locale_t developed_with = {"Developed with:","Разработано с использованием:","Dezvoltat folosind:"};
		locale_t thanks_to = {"Special thanks:","Особые благодарности:","Mulțumiri speciale:"};
	}
}
namespace popup {
	locale_t yes = {"[Yes]","[Да]","[Da]"};
	locale_t no = {"[No]","[Нет]","[Nu]"};
	locale_t ok = {"[Got it]","[Понятно]","[Am înțeles]"};
	locale_t info = {"[Information]","[Информация]","[Informație]"};
	locale_t warning = {"[Warning!]","[Внимание!]","[Atenție!]"};
	locale_t error = {"[Error!]","[Ошибка!]","[Eroară!]"};
}
