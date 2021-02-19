#pragma once
#include <vector>
#include <memory>
#include <cinttypes>
#include <string_view>
#include <cstdio>
#include <cassert>
#include <chrono>

#include "Window.hpp"

namespace ez_window = ez::window;

namespace ez::window {
	// Store a list of active windows
	// store the nuklear context, store the message passing engine as well.
	class Engine {
	public:
		Engine();
		virtual ~Engine();
		
		std::shared_ptr<Window> add(Window* window);
		void add(std::shared_ptr<Window> window);

		bool contains(const Window& window) const noexcept;
		bool contains(Window const * const window) const noexcept;
		bool contains(std::string_view name) const noexcept;

		bool isRealtime() const noexcept;
		void setRealtime(bool val) noexcept;

		void setDelayMicroseconds(uint64_t period) noexcept;
		uint64_t getDelayMicroseconds() const noexcept;

		int run(int argc, char* argv[]);

		/// <summary>
		/// To be overloaded by a specific engine implementation. Called on a per-frame
		/// basis to handle any input produced by the window backend.
		/// </summary>
		/// <param name="_windows">
		/// The list of windows owned by this engine, provided to allow custom
		/// handling or pre/post processing of input.
		/// </param>
		virtual void handleInput(std::vector<std::shared_ptr<Window>>& _windows) = 0;
		
		/// <summary>
		/// To be overloaded by a specific engine implementation. Called on a per-frame
		/// basis to run any necessary drawing code for all active windows.
		/// </summary>
		/// <param name="_windows">
		/// The list of windows owned by this engine, provided to allow custom
		/// rendering.
		/// </param>
		virtual void drawWindows(std::vector<std::shared_ptr<Window>> & _windows) = 0;
		
		/// <summary>
		/// To be overloaded by a specific engine implementation. Only called once
		/// to allow custom command line args to be passed to an engine.
		/// </summary>
		/// <param name="argc">The number of arguments passed.</param>
		/// <param name="argv">The array of c-string arguments.</param>
		virtual void processCommandLine(int argc, char* argv[]) = 0;

		
	private:
		bool running, realtime;
		std::chrono::microseconds delayPeriod;
		std::vector<std::shared_ptr<Window>> windows;

		void checkWindows();

		void renderInternal();

		bool hasEvent() const;
	};
}