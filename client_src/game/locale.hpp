#pragma once

#include "incl.hpp"

enum struct LOCALE {
	EN,
	RU,
	MD
};

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
		std::vector<const char*> music_volume {"[Music volume]","[Громкость музыки]","[Volumul muzicii]"};
		std::vector<const char*> sfx_volume {"[SFX volume]","[Громкость звуков]","[Volumul sunetelor]"};
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
