#include "ez/window/Core.hpp"
#include "SDL2/SDL.h"

namespace ez::window {

	bool captureMouse(bool val) {
		return SDL_CaptureMouse(static_cast<SDL_bool>(val)) == 0;
	}
	void allowScreenSaver(bool val) {
		if (val) {
			SDL_EnableScreenSaver();
		}
		else {
			SDL_DisableScreenSaver();
		}
	}
	bool isScreenSaverAllowed() {
		return SDL_IsScreenSaverEnabled() == SDL_TRUE;
	}

	glm::ivec2 getMousePos() {
		glm::ivec2 mp;
		SDL_GetMouseState(&mp.x, &mp.y);
		return mp;
	}

	ez::MouseButtons getMouseState() {
		int state = SDL_GetMouseState(nullptr, nullptr);

		ez::MouseButtons buttons;
		if (state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			buttons.press(ez::Mouse::Left);
		}
		if (state & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			buttons.press(ez::Mouse::Right);
		}
		if (state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
			buttons.press(ez::Mouse::Middle);
		}
		if (state & SDL_BUTTON(SDL_BUTTON_X1)) {
			buttons.press(ez::Mouse::Button4);
		}
		if (state & SDL_BUTTON(SDL_BUTTON_X2)) {
			buttons.press(ez::Mouse::Button5);
		}
		return buttons;
	}
};

namespace ez::display {
	int count() {
		return SDL_GetNumVideoDisplays();
	}
};