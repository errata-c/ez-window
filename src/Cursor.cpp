#include "ez/window/Cursor.hpp"
#include "SDL2/SDL.h"

namespace ez::window {
	Cursor::Cursor(SystemCursor type)
		: cursor(nullptr)
	{
		cursor = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(type));
	}
	Cursor::~Cursor() {
		if (cursor) {
			SDL_FreeCursor(cursor);
			cursor = nullptr;
		}
	}

	void Cursor::setActive(bool val) {
		if (val) {
			SDL_SetCursor(cursor);
		}
		else {
			SDL_SetCursor(SDL_GetDefaultCursor());
		}
	}
	bool Cursor::isActive() const {
		return cursor == SDL_GetCursor();
	}

	void Cursor::setVisible(bool val) {
		SDL_ShowCursor(val);
	}
	bool Cursor::isVisible() {
		return SDL_ShowCursor(-1) == SDL_ENABLE;
	}
};