#pragma once
// For the window title.
#include <string>
#include <string_view>

// For input management
#include <ez/input/InputEvent.hpp>

// For the window dimensions.
#include <glm/vec2.hpp>

// Window styling flags
#include "Style.hpp"
#include "RenderSettings.hpp"

struct SDL_Window;

namespace ez_window = ez::window;

namespace ez::window {
	// Forward declare the engine class
	class Engine;
	class RenderSettings;

	/// <summary>
	/// Abstract window class to act over various different backends.
	/// </summary>
	class Window {
	public:
		/// <summary>
		/// Function meant for the user to overload, allows the user to decide what to do with input.
		/// </summary>
		/// <param name="event">The event that has been generated by the system.</param>
		/// <returns>True if the event was handled, false otherwise.</returns>
		virtual void handleInput() = 0;

		/// <summary>
		/// Function meant for the user to overload, allows the user to draw to the window.
		/// </summary>
		virtual void draw() = 0;

		Window(std::string_view _title, glm::ivec2 size, Style _style, const RenderSettings& rs);
		virtual ~Window();

		// Grab input
		void grabInput(bool value);

		// Is the window grabbing input.
		bool isInputGrabbed() const;

		// Set the cursor position relative to this window.
		void setCursorPos(glm::ivec2 pos);

		// Get the cursor position relative to this window.
		glm::ivec2 getCursorPos() const;

		// Window specific clipboard.
		std::string getClipboardString() const;

		// Window specific clipboard.
		void setClipboardString(std::string_view str);

		// Raise the window, and set focus.
		void raise();

		void setResizable(bool val);

		bool isResizable() const;

		// Make as big as possible
		void maximize();

		// Make as small as possible
		void minimize();

		// Set size and position to what it was prior to maximize/minimize
		void restore();

		bool isMaximized() const;

		bool isMinimized() const;

		// Makes the window fullscreen, matching the display mode of the current display.
		void setFullscreen(bool val);

		// Makes the window fullscreen, but changes the display mode to one nearest to the window size.
		void setFullscreenStretched(bool val);

		bool isFullscreen() const;

		void setBorderless(bool val);

		bool isBorderless() const;

		/// <summary>
		/// Returns the render settings that were established for the window.
		/// Note that they may differ from the ones used to create the window, because of 
		/// the underlying capabilities of the system.
		/// </summary>
		/// <returns>Structure containing the window's render settings.</returns>
		virtual RenderSettings getRenderSettings() const;

		/// <summary>
		/// Attempts to set the render settings of the window to the provided settings. There is no 
		/// guarantee that it will succeed.
		/// </summary>
		/// <param name="settings">The settings desired for the window.</param>
		/// <returns>bool representing success or failure.</returns>
		virtual bool setRenderSettings(const RenderSettings& settings);

		/// <summary>
		/// Getter for Style flags
		/// </summary>
		/// <returns></returns>
		virtual Style getStyle() const;

		/// <summary>
		/// Getter for Window dimensions
		/// </summary>
		/// <returns>Size of window</returns>
		glm::ivec2 getSize() const;

		/// <summary>
		/// Getter for actual drawing area size, ie. not including decorations.
		/// </summary>
		/// <returns>Viewport dimensions</returns>
		glm::ivec2 getViewportSize() const;

		/// <summary>
		/// Getter for Window position in screen coords
		/// </summary>
		/// <returns>Position of top left corner of window</returns>
		glm::ivec2 getPosition() const;

		/// <summary>
		/// Determines if the window is currently open.
		/// Note that this is different from visible and minimized, this is if the window has not been closed.
		/// </summary>
		/// <returns>Window open?</returns>
		bool isOpen() const;

		/// <summary>
		/// Queries the visiblity state of the window.
		/// </summary>
		/// <returns>A boolean representing the visiblity state of the window.</returns>
		bool isVisible() const;

		/// <summary>
		/// Returns a string view of the window title.
		/// </summary>
		/// <returns>A std::string_view of the title.</returns>
		std::string_view getTitle() const;

		/// <summary>
		/// Sets the size of the window in pixel dimensions. This size includes the frame and other decorations.
		/// </summary>
		/// <param name="val">Integer vector representing the size of the window.</param>
		void setSize(glm::ivec2 val);

		/// <summary>
		/// Sets the position of the window in pixel coordinates.
		/// </summary>
		/// <param name="val">Location of the top left corner of the window.</param>
		void setPosition(glm::ivec2 val);

		/// <summary>
		/// Closes the window.
		/// </summary>
		void close();

		/// <summary>
		/// Shows or hides the window without destroying it.
		/// </summary>
		/// <param name="val">The value determining wheter to show or hide the window.</param>
		void setVisible(bool val);

		/// <summary>
		/// Sets the title of the window.
		/// </summary>
		/// <param name="title">String containing the new title for the window.</param>
		void setTitle(std::string_view title);

		/// <summary>
		/// Activates or deactivates this window's OpenGL context
		/// </summary>
		/// <param name="val">Activate?</param>
		void setActive(bool val);


		/// <summary>
		/// Backend dependent, at the very least displays what has been rendered.
		/// </summary>
		void swapBuffers();

		/// <summary>
		/// Checks to see if any input has been submitted to the window.
		/// </summary>
		/// <param name="ev">The event structure to fill upon success.</param>
		/// <returns>True if there was an event, false otherwise.</returns>
		bool pollInput(ez::InputEvent& ev);

		
	protected:

	private:
		SDL_Window* window;

		RenderSettings::Type rtype;
		void* rctx;
		Style style;
		std::string title;
	};
}

namespace ez {
	using Window = window::Window;
};
