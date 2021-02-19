#pragma once
#include <glm/vec2.hpp>
#include <ez/input/Mouse.hpp>

namespace ez::window {
	class Cursor;

	bool captureMouse(bool val);
	void allowScreenSaver(bool val);
	bool isScreenSaverAllowed();

	glm::ivec2 getMousePos();
	ez::MouseButtons getMouseState();
};