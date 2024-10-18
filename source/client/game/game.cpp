#include "incl.hpp"
#include "utility.hpp"
#include "asio.hpp"
#include "locale.hpp"
#include "node/basic_objects.hpp"
#include "node/scene.hpp"

struct {
	int x;
	int y;
} mouse;

int main(int argc, char** argv) {
	gl::logfile = fopen("../stacktrace.log", "a");
	SDL_Window* window; SDL_Renderer* rend;
	try {
		stacktrace(module::core, "Launched Moderntale Redux.");
		verify_integrity(); init(); gl::config();

		window = SDL_CreateWindow("[Moderntale Redux]", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_BORDERLESS);
		rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		Mix_AllocateChannels(0x10);
		SDL_Event event;
		
		/* TODO something with this sheet already dammit */
		scene MainMenu(rend);
		MainMenu.create_object<object>(0, 0, -69Z, path::img::menu_bg);
		MainMenu.create_object<button>(50, 50, 420Z, path::img::menu_button);
		MainMenu.get<button>(420Z)->move_to(40, 460);
		audio menu_loop(path::bgm::menu);
		menu_loop.play(CH_MUS);
		for (;;) {
			MainMenu.rerender();
			SDL_GetMouseState(&mouse.x, &mouse.y);
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				default: break;
				case SDL_MOUSEBUTTONDOWN:
					if (MainMenu.get<button>(420Z)->was_clicked(mouse.x, mouse.y)) {
						goto CLEANUP;
					}
					break;
				}
			}
			SDL_Delay(gl::delay);
		}
	}
	catch (ERROR E) {
		Mix_HaltChannel(-1);
		if (E != INITIALISATION) {
			audio menu_loop(path::sfx::error);
			menu_loop.play(CH_SND);
		} //ехидный деструктор (146% kurwa)
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
		case OBJECT_LIMIT_REACHED:
			ERROR_CRIT("Object limit exceeded.");
			break;
		default: break;
		}
		goto CLEANUP_ERR;
	}
CLEANUP:
	Mix_HaltChannel(-1);
	{
		audio menu_loop(path::sfx::quit);
		menu_loop.play(CH_SND);
		float alpha = 1.0f;
		while (alpha > 0.0f) {
			if (alpha < 0.0f) break;
			SDL_SetWindowOpacity(window, alpha -= 0.01f);
			SDL_Delay(35);
		}
	}
CLEANUP_ERR:
	{
		TTF_Quit();
		IMG_Quit();
		Mix_Quit();
		SDL_Quit();
	}
	stacktrace(module::core, "Session terminated.\n\0");
	fclose(gl::logfile);
	return 0;
}
