#include <fmt/core.h>

#include <ez/window/BasicEngine.hpp>
#include <ez/window/backends/SDL2.hpp>


class CustomWindow : public ez_window::SDL2Window {
public:
	CustomWindow(std::string_view _title, glm::ivec2 _size, ez_window::Style _style)
		: ez_window::SDL2Window(_title, _size, _style)
	{}

	void handleInput(const ez::InputEvent& ev) override {
		fmt::print("{}\n", ev.to_string());
		if (ev.type == ez::InputEventType::Closed) {
			close();
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
	engine.add(new CustomWindow{ "Basic Test", {800, 600}, ez_window::Style::Default });

	return engine.run(argc, argv);
}