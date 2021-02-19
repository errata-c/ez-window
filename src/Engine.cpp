#include <thread>
#include <chrono>

#include <ez/window/Engine.hpp>
#include <SDL2/SDL.h>

namespace ez::window {
	Engine::Engine()
		: running(false)
		, realtime(true)
		, delayPeriod(std::chrono::microseconds(1000))
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

	bool Engine::isRealtime() const noexcept {
		return realtime;
	}
	void Engine::setRealtime(bool val) noexcept {
		realtime = val;
	}

	void Engine::setDelayMicroseconds(uint64_t period) noexcept {
		delayPeriod = std::chrono::microseconds(period);
	}
	uint64_t Engine::getDelayMicroseconds() const noexcept {
		return delayPeriod.count();
	}

	int Engine::run(int argc, char* argv[]) {
		processCommandLine(argc, argv);

		running = true;

		while (running) {
			if (!realtime) {
				while (!hasEvent()) {
					std::this_thread::sleep_for(delayPeriod);
					SDL_PumpEvents();
				}
			}

			handleInput(windows);

			renderInternal();

			checkWindows();
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
		// Filter out any windows not present anymore.
		for (std::size_t i = 0; i < windows.size(); ++i) {
			if (!windows[i]->isOpen()) {
				std::swap(windows[i], windows.back());
				windows.pop_back();
			}
		}

		// Nothing left to do, just finish up.
		if (windows.size() == 0) {
			running = false;
		}
	}

	// Wrap a newly created window and add to the engine, this is a convienience function
	std::shared_ptr<Window> Engine::add(Window* window) {
		windows.push_back(std::shared_ptr<Window>(window));
		return windows.back();
	}

	// Take a preexisting window and add it into the render queue.
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

	bool Engine::hasEvent() const {
		return SDL_HasEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
	}
}
