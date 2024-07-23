#pragma once
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#pragma comment(lib, "SDL2_ttf.lib")

#include "incl.hpp"
#include "init.hpp"
#include "io.hpp"
#include "scenes/menu.hpp"

int main(int argc, char** argv) {
	gl::logfile = fopen("../stacktrace.log", "a");
	try {
		stacktrace(module::core, "Launched Moderntale Redux.");
		verify_integrity(); init();
		/*  Test */
		SDL_Window* window = SDL_CreateWindow("[Moderntale Redux]", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_BORDERLESS);
		SDL_Renderer* rend = SDL_CreateRenderer(window, -1, 0);
		_render(rend, IMG_LoadTexture(rend, path::bg::menu));
		for (;;) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				goto CLEANUP;
				}
			}
			SDL_Delay(16);
		}
	} catch (ERROR E) {
		switch (E) {
		case INITIALISATION:
			stacktrace(module::error, "SDL initialisation failed.");
			break;
		case MISSING_ENGINE_FILE:
		case INTEGRITY_VIOLATED:
		case Z_ORDER:
		default: break;
		}
	}
CLEANUP:
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	stacktrace(module::core, "Session terminated.");
	fclose(gl::logfile);
	return 0;
}
