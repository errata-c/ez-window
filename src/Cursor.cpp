#include "ez/window/Cursor.hpp"
#include "SDL2/SDL.h"

namespace ez::window {
	Cursor::Cursor(SystemCursor type)
		: cursor(nullptr)
	{
		SDL_SystemCursor result;

		switch (type) {
		case SystemCursor::Arrow:
			result = SDL_SYSTEM_CURSOR_ARROW;
			break;
		case SystemCursor::IBeam:
			result = SDL_SYSTEM_CURSOR_IBEAM;
			break;
		case SystemCursor::Wait:
			result = SDL_SYSTEM_CURSOR_WAIT;
			break;
		case SystemCursor::SmallWait:
			result = SDL_SYSTEM_CURSOR_WAITARROW;
			break;
		case SystemCursor::Crosshair:
			result = SDL_SYSTEM_CURSOR_CROSSHAIR;
			break;
		case SystemCursor::Hand:
			result = SDL_SYSTEM_CURSOR_HAND;
			break;
		case SystemCursor::SizeH:
			result = SDL_SYSTEM_CURSOR_SIZEWE;
			break;
		case SystemCursor::SizeV:
			result = SDL_SYSTEM_CURSOR_SIZENS;
			break;
		case SystemCursor::SizeAll:
			result = SDL_SYSTEM_CURSOR_SIZEALL;
			break;
		case SystemCursor::SizeFDiag:
			result = SDL_SYSTEM_CURSOR_SIZENESW;
			break;
		case SystemCursor::SizeBDiag:
			result = SDL_SYSTEM_CURSOR_SIZENWSE;
			break;
		case SystemCursor::Disabled:
			result = SDL_SYSTEM_CURSOR_NO;
			break;
		}
		cursor = SDL_CreateSystemCursor(result);
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