#include <fmt/core.h>

#include "SDL2/SDL.h"

#include <ez/window/BasicEngine.hpp>
#include <ez/window/Window.hpp>


class CustomWindow : public ez::window::Window {
public:
	CustomWindow(std::string_view _title, glm::ivec2 _size, ez_window::Style _style, const ez_window::RenderSettings& rs)
		: ez::window::Window(_title, _size, _style, rs)
	{}

	void handleInput() override {
		//fmt::print("{}\n", ev.to_string());
		ez::InputEvent ev;
		while (pollInput(ev)) {
			if (ev.type == ez::InputEventType::Closed) {
				close();
			}
		}
	}
	void draw() override {

	}
};

int main(int argc, char** argv) {
	// Create the engine.
	ez_window::BasicEngine engine;

	ez_window::GLSettings gset;
	gset.majorVersion() = 4;
	gset.minorVersion() = 5;

	gset.colorBits() = { 8,8,8,8 };

	// Create a window class, give it to the engine.
	CustomWindow* win = new CustomWindow{ "Basic Test", {800, 600}, ez_window::Style::Default, gset };
	engine.add(win);

	fmt::print("There are {} displays.\n", SDL_GetNumVideoDisplays());
	fmt::print("There are {} display drivers.\n", SDL_GetNumVideoDrivers());

	for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {
		int nmodes = SDL_GetNumDisplayModes(i);
		fmt::print("Display {} has {} modes.\n", i, nmodes);
		fmt::print("Name is {}.\n", SDL_GetDisplayName(i));

		for (int j = 0; j < nmodes; ++j) {
			SDL_DisplayMode mode;
			SDL_GetDisplayMode(i, j, &mode);

			fmt::print("   {} x {}, {} Hz, {}\n", mode.w, mode.h, mode.refresh_rate, SDL_GetPixelFormatName(mode.format));
		}
	}

	return engine.run(argc, argv);
}