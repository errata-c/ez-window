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
};

namespace ez::display {
	int count() {
		return SDL_GetNumVideoDisplays();
	}
};