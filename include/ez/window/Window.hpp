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
		virtual ~Window() {};

		/// <summary>
		/// Returns the render settings that were established for the window.
		/// Note that they may differ from the ones used to create the window, because of 
		/// the underlying capabilities of the system.
		/// </summary>
		/// <returns>Structure containing the window's render settings.</returns>
		virtual RenderSettings getRenderSettings() const = 0;

		/// <summary>
		/// Attempts to set the render settings of the window to the provided settings. There is no 
		/// guarantee that it will succeed.
		/// </summary>
		/// <param name="settings">The settings desired for the window.</param>
		/// <returns>bool representing success or failure.</returns>
		virtual bool setRenderSettings(const RenderSettings& settings) = 0;

		/// <summary>
		/// Getter for Style flags
		/// </summary>
		/// <returns></returns>
		virtual Style getStyle() const = 0;

		/// <summary>
		/// Getter for Window dimensions
		/// </summary>
		/// <returns>Size of window</returns>
		virtual glm::ivec2 getSize() const = 0;

		/// <summary>
		/// Getter for Window position in screen coords
		/// </summary>
		/// <returns>Position of top left corner of window</returns>
		virtual glm::ivec2 getPosition() const = 0;

		/// <summary>
		/// Determines if the window is currently open.
		/// Note that this is different from visible and minimized, this is if the window has not been closed.
		/// </summary>
		/// <returns>Window open?</returns>
		virtual bool isOpen() const = 0;

		/// <summary>
		/// Queries the visiblity state of the window.
		/// </summary>
		/// <returns>A boolean representing the visiblity state of the window.</returns>
		virtual bool isVisible() const = 0;

		/// <summary>
		/// Returns a string view of the window title.
		/// </summary>
		/// <returns>A std::string_view of the title.</returns>
		virtual std::string_view getTitle() const = 0;

		/// <summary>
		/// Sets the size of the window in pixel dimensions. This size includes the frame and other decorations.
		/// </summary>
		/// <param name="val">Integer vector representing the size of the window.</param>
		virtual void setSize(glm::ivec2 val) = 0;
		/// <summary>
		/// Sets the position of the window in pixel coordinates.
		/// </summary>
		/// <param name="val">Location of the top left corner of the window.</param>
		virtual void setPosition(glm::ivec2 val) = 0;

		/// <summary>
		/// Closes the window.
		/// </summary>
		virtual void close() = 0;

		/// <summary>
		/// Shows or hides the window without destroying it.
		/// </summary>
		/// <param name="val">The value determining wheter to show or hide the window.</param>
		virtual void setVisible(bool val) = 0;

		/// <summary>
		/// Sets the title of the window.
		/// </summary>
		/// <param name="title">String containing the new title for the window.</param>
		virtual void setTitle(std::string_view title) = 0;

		/// <summary>
		/// Activates or deactivates this window's OpenGL context
		/// </summary>
		/// <param name="val">Activate?</param>
		virtual void setActive(bool val) = 0;


		/// <summary>
		/// Backend dependent, at the very least displays what has been rendered.
		/// </summary>
		virtual void swapBuffers() = 0;

		/// <summary>
		/// Checks to see if any input has been submitted to the window.
		/// </summary>
		/// <param name="ev">The event structure to fill upon success.</param>
		/// <returns>True if there was an event, false otherwise.</returns>
		virtual bool pollInput(ez::InputEvent& ev) = 0;

		/// <summary>
		/// Function meant for the user to overload, allows the user to decide what to do with input.
		/// </summary>
		/// <param name="event">The event that has been generated by the system.</param>
		/// <returns>True if the event was handled, false otherwise.</returns>
		virtual void handleInput(const ez::InputEvent& event) = 0;

		/// <summary>
		/// Function meant for the user to overload, allows the user to draw to the window.
		/// </summary>
		virtual void draw() = 0;
	protected:

	};
}