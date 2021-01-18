#include <fmt/core.h>

#include <ez/window/BasicEngine.hpp>
#include <ez/window/backends/SFML.hpp>

class CustomWindow : public ez_window::SFMLWindow {
public:
	CustomWindow(std::string_view _title, glm::ivec2 _size, ez_window::Style _style, const ez_window::RenderSettings & rs)
		: ez_window::SFMLWindow(_title, _size, _style, rs)
	{}

	void handleInput(const ez::InputEvent& ev) override {
		if (ev.type == ez::InputEventType::KeyRelease) {
			fmt::print("Got a key press!\n");
		}
		else if (ev.type == ez::InputEventType::MousePress) {
			fmt::print("Got a mouse press!\n");
		}
		else if (ev.type == ez::InputEventType::Closed) {
			fmt::print("Is this window open: {}\n", isOpen());
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
	engine.add(new CustomWindow{ "Basic Test", {800, 600}, ez_window::Style::Default, gset });

	return engine.run(argc, argv);
}