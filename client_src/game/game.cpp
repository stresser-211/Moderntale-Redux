#include "incl.hpp"
#include "global.hpp"
#include "init.hpp"
#include "io.hpp"
#include "asio.hpp"
#include "nodes/object.hpp"
#include "scenes/menu.hpp"

void FRAMERATE_DELAY(void) {
	const auto start = SDL_GetTicks();
	auto frame_time = SDL_GetTicks() - start;
		if (frame_time < _duration) {
			SDL_Delay(_duration - frame_time);
		}
}

int main(int argc, char** argv) {
	gl::logfile = fopen("../stacktrace.log", "a");
	SDL_Window* window; SDL_Renderer* rend;
	try {
		stacktrace(module::core, "Launched Moderntale Redux.");
		CRC_init(); verify_integrity(); init();

		window = SDL_CreateWindow("[Moderntale Redux]", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_BORDERLESS);
		rend = SDL_CreateRenderer(window, -1, 0); SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

		/* todo: create a room */
		obj_t bg = create_object<_object>(rend, -69Z, 0, 0, path::img::menu_bg);
		//obj_t bg2 = create_object<_object>(rend, bg);
		obj_t button_exit = create_object<_button>(rend, 420Z, 50, 50, path::img::menu_button);
		button_exit->center();
		std::sort(gl::objects.begin(), gl::objects.end(), [](auto& a, auto& b) {
			return a.second < b.second;
		});
		auto _rerender = [&](void) {
			for (const auto& iter : gl::objects) {
				_render(rend, iter.first);
			}
		};
		_oggplay(path::bgm::menu, -18.0f);
		_rerender();
		fclose(gl::logfile);

		/* Main loop */
		for (;;) {
			gl::logfile = fopen("../stacktrace.log", "a");
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_MOUSEBUTTONDOWN:
					int x, y;
					SDL_GetMouseState(&x, &y);
					if (button_exit->was_clicked(x, y)) {
						goto CLEANUP;
					}
					break;
				}
			}
			FRAMERATE_DELAY();
			fclose(gl::logfile);
		}
	} catch (ERROR E) {
		_oggplay(path::sfx::error, -18.0f);
		switch (E) {
		case INITIALISATION:
			fclose(gl::logfile);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "", "Initialisation error (see stacktrace.log for details).", NULL);
			break;
		case MISSING_ENGINE_FILE:
		case INTEGRITY_VIOLATED:
			fclose(gl::logfile);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "", "Critical engine error (see stacktrace.log for details).", NULL);
			break;
		case OUT_OF_Z_ORDER:
			fclose(gl::logfile);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "", "Object limit exceeded (see stacktrace.log for details).", NULL);
			break;
		default: fclose(gl::logfile); break;
		}
		goto CLEANUP_ERR;
	}
CLEANUP:
	for (auto& iter : gl::objects) {
		_destroy(iter.first);
	}
	_oggplay(path::sfx::quit, -18.0f);
CLEANUP_ERR:
	float alpha = 1.0f;
	while (alpha > 0.0f) {
		if (alpha < 0.0f) break;
		SDL_SetWindowOpacity(window, alpha -= 0.01f);
		SDL_Delay(35);
	}
	{
		SDL_Quit();
		IMG_Quit();
		Mix_Quit();
		TTF_Quit();
	}
	fclose(gl::logfile);
	gl::logfile = fopen("../stacktrace.log", "a");
	stacktrace(module::core, "Session terminated.\n\0");
	fclose(gl::logfile);
	return 0;
}
