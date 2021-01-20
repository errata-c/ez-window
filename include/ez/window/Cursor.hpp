#pragma once

struct SDL_Cursor;

namespace ez::window {
	enum class SystemCursor {
		Arrow,
		IBeam,
		Wait,
		SmallWait,
		Crosshair,
		Hand,
		SizeH,
		SizeV,
		SizeAll,
		SizeFDiag, // Forward diagonal, like forward slash '/'
		SizeBDiag, // Back diagonal, like back slash '\'
		Disabled, // slashed circle or crossbones
	};

	class Cursor {
	public:
		Cursor(SystemCursor type);
		~Cursor();

		void setActive(bool val);
		bool isActive() const;

		static void setVisible(bool val);
		static bool isVisible();
	private:
		SDL_Cursor* cursor;
	};
};