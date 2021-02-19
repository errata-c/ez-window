#pragma once
#include "Engine.hpp"

namespace ez::window {
	class BasicEngine: public ez::window::Engine {
	public:
		void handleInput(std::vector<std::shared_ptr<Window>>& windows) override {
			ez::InputEvent ev;
			for (std::shared_ptr<Window>& window : windows) {
				window->handleInput();
			}
		}
		void drawWindows(std::vector<std::shared_ptr<Window>>& windows) override {
			for (std::shared_ptr<Window>& window : windows) {
				window->draw();
			}
		}
		void processCommandLine(int argc, char* argv[]) override {};
	};
}