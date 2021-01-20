#pragma once

namespace ez::window {
	class Cursor;

	bool captureMouse(bool val);
	void allowScreenSaver(bool val);
	bool isScreenSaverAllowed();
};

namespace ez::display {
	// Number of displays
	int count();

	// Other display functions, decide how to handle return values.
};