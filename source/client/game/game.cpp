#include "incl.hpp"
#include "utility.hpp"
#include "asio.hpp"
#include "locale.hpp"
#include "node/basic_objects.hpp"
#include "node/scene.hpp"

int main(int argc, char** argv) {
	gl::logfile = fopen("../stacktrace.log", "a");
	SDL_Window* window; SDL_Renderer* rend;
	try {
		stacktrace(module::core, "Launched Moderntale Redux.");
		verify_integrity(); init();

		window = SDL_CreateWindow("[Moderntale Redux]", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_BORDERLESS);
		rend = SDL_CreateRenderer(window, -1, 0); SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		
		/* TODO something with this abomination. */
		_scene MainMenu(rend);
		MainMenu.create_object<_object>(0, 0, -69Z, path::img::menu_bg);
		MainMenu.create_object<_button>(50, 50, 420Z, path::img::menu_button);
		MainMenu.get<_button>(420Z)->move_to(40, 460);
		MainMenu.rerender();
		_oggplay(path::bgm::menu, -18.0f);
		for (;;) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_MOUSEBUTTONDOWN:
					int x, y;
					SDL_GetMouseState(&x, &y);
					if (MainMenu.get<_button>(420Z)->was_clicked(x, y)) {
						goto CLEANUP;
					}
					break;
				}
			}
			FRAMERATE_DELAY();
		}
	} catch (ERROR E) {
		if (E != INITIALISATION) _oggplay(path::sfx::error, -18.0f);
		switch (E) {
		case INITIALISATION:
			ERROR_CRIT("Initialisation error.");
			break;
		case MISSING_ENGINE_FILE:
			ERROR_CRIT("An engine's file is missing.");
			break;
		case INTEGRITY_VIOLATED:
			ERROR_CRIT("Engine's integrity violated.");
			break;
		case OUT_OF_Z_ORDER:
			ERROR_CRIT("Object limit exceeded.");
			break;
		default: break;
		}
		goto CLEANUP_ERR;
	}
CLEANUP:
	_oggplay(path::sfx::quit, -18.0f);
	float alpha; alpha = 1.0f;
	while (alpha > 0.0f) {
		if (alpha < 0.0f) break;
		SDL_SetWindowOpacity(window, alpha -= 0.01f);
		SDL_Delay(35);
	}
CLEANUP_ERR:
	{
		SDL_Quit();
		IMG_Quit();
		Mix_Quit();
		TTF_Quit();
	}
	stacktrace(module::core, "Session terminated.\n\0");
	fclose(gl::logfile);
	return 0;
}
