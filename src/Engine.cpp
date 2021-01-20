#include <ez/window/Engine.hpp>
#include <SDL2/SDL.h>

namespace ez::window {
	Engine::Engine()
		: running(false)
	{
		int error = 0;

		error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK);
		if (error != 0) {
			printf("Failed to initialize the SDL2 library.\n");
			const char* desc = SDL_GetError();
			printf("Error code: %x\n", error);
			if (desc != nullptr) {
				printf("Error description: %s\n", desc);
			}
			else {
				printf("Could not retrieve error description.\n");
			}
			assert(false);
		}
	}

	Engine::~Engine() {
		SDL_Quit();
	}

	int Engine::run(int argc, char** argv) {
		processCommandLine(argc, argv);

		running = true;

		while (running) {
			handleInput(windows);

			checkWindows();

			renderInternal();
		}

		return 0;
	}

	void Engine::renderInternal() {
		drawWindows(windows);

		for (std::shared_ptr<Window> & window : windows) {
			window->swapBuffers();
		}
	}

	void Engine::checkWindows() {
		for (std::size_t i = 0; i < windows.size(); ++i) {
			if (!windows[i]->isOpen()) {
				std::swap(windows[i], windows.back());
				windows.pop_back();
			}
		}

		if (windows.size() == 0) {
			running = false;
		}
	}

	std::shared_ptr<Window> Engine::add(Window* window) {
		windows.push_back(std::shared_ptr<Window>(window));
		return windows.back();
	}

	void Engine::add(std::shared_ptr<Window> window) {
		windows.push_back(window);
	}


	bool Engine::contains(const Window& window) const noexcept {
		return contains(&window);
	}
	bool Engine::contains(std::string_view name) const noexcept {
		for (const std::shared_ptr<Window>& item : windows) {
			if (item->getTitle() == name) {
				return true;
			}
		}
		return false;
	}
	bool Engine::contains(Window const* const window) const noexcept {
		for (const std::shared_ptr<Window>& item : windows) {
			if (item.get() == window) {
				return true;
			}
		}
		return false;
	}
}
