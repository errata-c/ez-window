#include <ez/window/Display.hpp>
#include <SDL2/SDL.h>

namespace ez {
	PixelFormat::PixelFormat(Kind _kind) noexcept
		: kind(_kind)
	{}

	PixelFormat::operator Kind() const noexcept {
		return kind;
	}

	int PixelFormat::bytesPerPixel() const noexcept {
		return SDL_BYTESPERPIXEL(static_cast<int>(kind));
	}
	int PixelFormat::bitsPerPixel() const noexcept {
		return SDL_BITSPERPIXEL(static_cast<int>(kind));
	}
	bool PixelFormat::isIndexed() const noexcept {
		return SDL_ISPIXELFORMAT_INDEXED(static_cast<int>(kind));
	}
	bool PixelFormat::hasAlpha() const noexcept {
		return SDL_ISPIXELFORMAT_ALPHA(static_cast<int>(kind));
	}


	static DisplayMode failMode() {
		return DisplayMode{ PixelFormat::Unknown, {0,0}, 0, nullptr };
	}
	static DisplayMode convertMode(const SDL_DisplayMode& mode) {
		PixelFormat format;
		switch (mode.format) {
		case SDL_PIXELFORMAT_ABGR8888:
			format = PixelFormat::ABGR8888;
			break;
		case SDL_PIXELFORMAT_ARGB8888:
			format = PixelFormat::ARGB8888;
			break;
		case SDL_PIXELFORMAT_BGR888:
			format = PixelFormat::BGR888;
			break;
		case SDL_PIXELFORMAT_BGRA8888:
			format = PixelFormat::BGRA8888;
			break;
		case SDL_PIXELFORMAT_RGB888:
			format = PixelFormat::RGB888;
			break;
		case SDL_PIXELFORMAT_RGBA8888:
			format = PixelFormat::RGBA8888;
			break;
		case SDL_PIXELFORMAT_IYUV:
			format = PixelFormat::IYUV;
			break;
		case SDL_PIXELFORMAT_NV12:
			format = PixelFormat::NV12;
			break;
		case SDL_PIXELFORMAT_NV21:
			format = PixelFormat::NV21;
			break;
		case SDL_PIXELFORMAT_UYVY:
			format = PixelFormat::UYVY;
			break;
		case SDL_PIXELFORMAT_YVYU:
			format = PixelFormat::YVYU;
			break;
		case SDL_PIXELFORMAT_YV12:
			format = PixelFormat::YV12;
			break;
		case SDL_PIXELFORMAT_YUY2:
			format = PixelFormat::YUY2;
			break;
		default:
			format = PixelFormat::Unknown;
			break;
		}
	}


	bool DisplayMode::isValid() const noexcept {
		return
			format != PixelFormat::Unknown &&
			size.x != 0 &&
			size.y != 0;
	}


	int Display::count() {
		return SDL_GetNumVideoDisplays();
	}

	Display::Display(int _index) noexcept
		: display(_index)
	{}

	int Display::numModes() const {
		return SDL_GetNumDisplayModes(display);
	}
	DisplayMode Display::getMode(int index) const {
		DisplayMode mode{ PixelFormat::Unknown, {0,0}, 0, nullptr };
		int result = SDL_GetDisplayMode(display, index, (SDL_DisplayMode*)&mode);
		if (result == 0) {
			return failMode();
		}

		return mode;
	}
	DisplayMode Display::getCurrentMode() const {
		DisplayMode mode{ PixelFormat::Unknown, {0,0}, 0, nullptr};
		int result = SDL_GetCurrentDisplayMode(display, (SDL_DisplayMode*)&mode);
		if (result == 0) {
			return failMode();
		}
		
		return mode;
	}
	DisplayMode Display::getNativeMode() const {
		DisplayMode mode{ PixelFormat::Unknown, {0,0}, 0, nullptr };
		int result = SDL_GetDesktopDisplayMode(display, (SDL_DisplayMode*)&mode);
		if (result == 0) {
			return failMode();
		}

		return mode;
	}
};