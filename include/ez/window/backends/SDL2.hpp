#pragma once
#include "../Window.hpp"
#include <ez/input/compat/SDL2.hpp>
#include <ez/gl.hpp>

namespace ez::window {
	class SDL2Window: public ez::window::Window {
	public:
		SDL2Window(std::string_view _title, glm::ivec2 size, Style _style, const RenderSettings & rs)
			: style(_style & (Style::Resize | Style::Visible | Style::Close | Style::Fullscreen | Style::HighDPI))
			, window(nullptr)
			, title(_title)
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
				glctx = SDL_GL_CreateContext(window);
			}
			assert(window != nullptr);
		}

		~SDL2Window() override {
			if (isOpen()) {
				close();
			}
		}

		RenderSettings getRenderSettings() const override {
			GLSettings gset;
			return gset;
		}

		bool setRenderSettings(const RenderSettings&) override {
			return false;
		}

		Style getStyle() const override {
			return style;
		}
		glm::ivec2 getSize() const override {
			assert(window != nullptr);

			glm::ivec2 tmp;
			SDL_GetWindowSize(window, &tmp.x, &tmp.y);
			return tmp;
		}
		glm::ivec2 getPosition() const override {
			assert(window != nullptr);

			glm::ivec2 tmp;
			SDL_GetWindowPosition(window, &tmp.x, &tmp.y);
			return tmp;
		}

		void setSize(glm::ivec2 val) override {
			assert(window != nullptr);

			SDL_SetWindowSize(window, val.x, val.y);
		}
		void setPosition(glm::ivec2 val) override {
			assert(window != nullptr);

			SDL_SetWindowPosition(window, val.x, val.y);
		}

		void close() override {
			// SDL2 sends two close events for some reason, so just check to make sure this is ok
			if (isOpen()) {
				SDL_GL_DeleteContext(glctx);
				SDL_DestroyWindow(window);
				window = nullptr;
			}
		}
		void setVisible(bool val) override {
			if (val) {
				SDL_ShowWindow(window);
			}
			else {
				SDL_HideWindow(window);
			}
		}
		void setTitle(std::string_view _title) override {
			assert(window != nullptr);

			title = _title;
			SDL_SetWindowTitle(window, title.c_str());
		}
		void setActive(bool val) override {
			assert(window != nullptr);
			if (val) {
				SDL_GL_MakeCurrent(window, glctx);
			}
		}

		void swapBuffers() override {
			assert(window != nullptr);

			SDL_GL_SwapWindow(window);
		}

		bool isOpen() const override {
			return window != nullptr;
		}
		bool isVisible() const override {
			return visible;
		}
		std::string_view getTitle() const override {
			return std::string_view(title);
		}

		bool pollInput(ez::InputEvent& ev) override {
			SDL_Event sdlev;
			if (SDL_PollEvent(&sdlev)) {
				ev = remapSDLEvent(sdlev);
				return true;
			}
			else {
				return false;
			}
		}
	private:
		bool visible;
		std::string title;
		SDL_Window* window;
		SDL_GLContext glctx;
		Style style;
	};
}