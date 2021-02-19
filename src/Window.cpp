#include "ez/window/window.hpp"
#include <ez/input/compat/SDL2.hpp>
#include "SDL2/SDL.h"

namespace ez::window {
	Window::Window(std::string_view _title, glm::ivec2 size, Style _style, const RenderSettings& rs)
		: style(_style& (Style::Resize | Style::Visible | Style::Close | Style::Fullscreen | Style::HighDPI))
		, window(nullptr)
		, title(_title)
		, closed(false)
		, rctx(nullptr)
	{
		int flags = 0;
		if (style.allOf(Style::Resize)) {
			flags |= SDL_WINDOW_RESIZABLE;
		}
		if (style.allOf(Style::Visible)) {
			flags |= SDL_WINDOW_SHOWN;
		}
		if (style.allOf(Style::Fullscreen)) {
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if (style.noneOf(Style::Resize | Style::Close)) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		switch (rs.getType()) {
		case RenderSettings::Type::None:
			break;
		case RenderSettings::Type::OpenGL: {
			flags |= SDL_WINDOW_OPENGL;
			const GLSettings& gset = rs.asGLSettings();

			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gset.majorVersion());
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gset.minorVersion());

			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, gset.colorBits().red);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, gset.colorBits().green);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, gset.colorBits().blue);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, gset.colorBits().alpha);

			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, gset.depthBits());
			SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, gset.stencilBits());

			SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, gset.accumBits().red);
			SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, gset.accumBits().green);
			SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, gset.accumBits().blue);
			SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, gset.accumBits().alpha);

			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, gset.multisampleBuffers());
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, gset.multisampleSamples());

			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, static_cast<int>(gset.flags()));
			switch (gset.profile()) {
			case GLProfile::Default:
				break;
			case GLProfile::Compatibility:
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
				break;
			case GLProfile::ES:
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
				break;
			case GLProfile::Core:
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
				break;
			}
			break;
		}
		case RenderSettings::Type::Vulkan:
			flags |= SDL_WINDOW_VULKAN;
			const VulkanSettings& vset = rs.asVulkanSettings();
			assert((vset.instance() != nullptr) && "No valid Vulkan instance passed in! It must be created before creating a window.");
			
			break;
		}


		window = SDL_CreateWindow(title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, size.x, size.y, flags);

		if (window == nullptr) {
			// In the case that the window could not be made...
			printf("Failed to create SDL2 window!\nError: %s\n", SDL_GetError());
		}
		else {
			switch (rs.getType()) {
			case RenderSettings::Type::OpenGL:
				rctx = SDL_GL_CreateContext(window);
				break;
			case RenderSettings::Type::Vulkan:

				break;
			}
			
		}
		assert(window != nullptr);
	}

	Window::~Window() {
		SDL_GL_DeleteContext(rctx);
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	std::string Window::getClipboardString() const {
		if (SDL_HasClipboardText()) {
			char* txt = SDL_GetClipboardText();
			std::string tmp{ txt };
			SDL_free(txt);
			return tmp;
		}
		else {
			return std::string{};
		}
	}
	void Window::setClipboardString(std::string_view str) {
		SDL_SetClipboardText(str.data());
	}

	void Window::grabInput(bool value) {
		SDL_SetWindowGrab(window, static_cast<SDL_bool>(value));
	}
	bool Window::isInputGrabbed() const {
		return SDL_GetWindowGrab(window) == SDL_TRUE;
	}

	bool Window::isKeyboardFocus() const {
		return (SDL_GetWindowFlags(window) & SDL_WINDOW_INPUT_FOCUS) == SDL_WINDOW_INPUT_FOCUS;
	}

	bool Window::isMouseFocus() const {
		return (SDL_GetWindowFlags(window) & SDL_WINDOW_MOUSE_FOCUS) == SDL_WINDOW_MOUSE_FOCUS;
	}

	void Window::raise() {
		SDL_RaiseWindow(window);
	}

	void Window::setResizable(bool val) {
		SDL_SetWindowResizable(window, static_cast<SDL_bool>(val));
	}

	bool Window::isResizable() const {
		return (SDL_GetWindowFlags(window) & SDL_WINDOW_RESIZABLE) == SDL_WINDOW_RESIZABLE;
	}

	void Window::maximize() {
		SDL_MaximizeWindow(window);
	}
	void Window::minimize() {
		SDL_MinimizeWindow(window);
	}
	void Window::restore() {
		SDL_RestoreWindow(window);
	}

	bool Window::isMaximized() const {
		return (SDL_GetWindowFlags(window) & SDL_WINDOW_MAXIMIZED) == SDL_WINDOW_MAXIMIZED;
	}

	bool Window::isMinimized() const {
		return (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) == SDL_WINDOW_MINIMIZED;
	}

	bool Window::isFullscreen() const {
		return (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN;
	}

	void Window::setFullscreen(bool val) {
		if (val) {
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else {
			SDL_SetWindowFullscreen(window, 0);
		}	
	}
	
	void Window::setFullscreenStretched(bool val) {
		if (val) {
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		}
		else {
			SDL_SetWindowFullscreen(window, 0);
		}
	}

	void Window::setBorderless(bool val) {
		SDL_SetWindowBordered(window, static_cast<SDL_bool>(!val));
	}

	bool Window::isBorderless() const {
		return (SDL_GetWindowFlags(window) & SDL_WINDOW_BORDERLESS) == SDL_WINDOW_BORDERLESS;
	}


	DisplayMode Window::getDisplayMode() const noexcept {
		DisplayMode mode{ PixelFormat::Unknown, {0,0}, 0, nullptr };
		int result = SDL_GetWindowDisplayMode(window, (SDL_DisplayMode*)&mode);
		if (result == 0) {
			return DisplayMode{ PixelFormat::Unknown, {0,0}, 0, nullptr };
		}
		return mode;
	}
	bool Window::setDisplayMode(const DisplayMode& mode) {
		if (isFullscreen()) {
			int result = SDL_SetWindowDisplayMode(window, (const SDL_DisplayMode*)&mode);
			return result != 0;
		}
		else {
			return false;
		}
	}

	void Window::setCursorPos(glm::ivec2 pos) {
		SDL_WarpMouseInWindow(window, pos.x, pos.y);
	}
	glm::ivec2 Window::getCursorPos() const {
		glm::ivec2 pos{0,0};
		SDL_GetGlobalMouseState(&pos.x, &pos.y);
		return pos - getPosition();
	}

	RenderSettings Window::getRenderSettings() const {
		GLSettings gset;
		return gset;
	}

	bool Window::setRenderSettings(const RenderSettings&) {
		return false;
	}

	Style Window::getStyle() const {
		return style;
	}
	glm::ivec2 Window::getSize() const {
		assert(window != nullptr);

		glm::ivec2 tmp;
		SDL_GetWindowSize(window, &tmp.x, &tmp.y);
		return tmp;
	}

	glm::ivec2 Window::getViewportSize() const {
		assert(window != nullptr);

		glm::ivec2 tmp;
		SDL_GL_GetDrawableSize(window, &tmp.x, &tmp.y);
		return tmp;
	}

	glm::ivec2 Window::getPosition() const {
		assert(window != nullptr);

		glm::ivec2 tmp;
		SDL_GetWindowPosition(window, &tmp.x, &tmp.y);
		return tmp;
	}

	void Window::setSize(glm::ivec2 val) {
		assert(window != nullptr);

		SDL_SetWindowSize(window, val.x, val.y);
	}
	void Window::setPosition(glm::ivec2 val) {
		assert(window != nullptr);

		SDL_SetWindowPosition(window, val.x, val.y);
	}

	void Window::close() {
		closed = true;
	}
	void Window::setVisible(bool val) {
		if (val) {
			SDL_ShowWindow(window);
		}
		else {
			SDL_HideWindow(window);
		}
	}
	void Window::setTitle(std::string_view _title) {
		assert(window != nullptr);

		title = _title;
		SDL_SetWindowTitle(window, title.c_str());
	}
	void Window::setActive(bool val) {
		assert(window != nullptr);
		if (val) {
			SDL_GL_MakeCurrent(window, rctx);
		}
	}

	void Window::swapBuffers() {
		assert(window != nullptr);

		SDL_GL_SwapWindow(window);
	}

	bool Window::isOpen() const {
		return closed == false;
	}
	bool Window::isVisible() const {
		return (SDL_GetWindowFlags(window) & SDL_WINDOW_SHOWN) == SDL_WINDOW_SHOWN;
	}
	std::string_view Window::getTitle() const {
		return std::string_view(title);
	}

	bool Window::pollInput(ez::InputEvent& ev) {
		SDL_Event sdlev;
		if (SDL_PollEvent(&sdlev)) {
			ev = remapSDLEvent(sdlev);
			return true;
		}
		else {
			return false;
		}
	}

	bool Window::waitInput(ez::InputEvent& ev, int millis) {
		SDL_Event sdlev;
		if (SDL_WaitEventTimeout(&sdlev, millis)) {
			ev = remapSDLEvent(sdlev);
			return true;
		}
		else {
			return false;
		}
	}
};