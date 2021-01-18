#pragma once 
#include <string>

#include "../Window.hpp"

#include <SFML/Window.hpp>
#include <ez/input/compat/SFML.hpp>
#include <ez/gl.hpp>

namespace ez::window {
	class SFMLWindow: public Window {
	public:
		SFMLWindow(std::string_view _title, glm::ivec2 size, Style _style, const RenderSettings & settings)
			: title(_title)
			, style(_style & (Style::Resize | Style::Close | Style::Fullscreen))
			, visible(true)
		{
			uint32_t flags = 0;
			if (style.anyOf(Style::Resize | Style::Close)) {
				flags |= sf::Style::Titlebar;
			}
			if (style.allOf(Style::Resize)) {
				flags |= sf::Style::Resize;
			}
			if (style.allOf(Style::Close)) {
				flags |= sf::Style::Close;
			}
			if (style.allOf(Style::Fullscreen)) {
				flags |= sf::Style::Fullscreen;
			}
			
			if (settings.getType() != RenderSettings::Type::OpenGL) {
				assert(false && "SFML only supports OpenGL");
			}

			const GLSettings& gset = settings.asGLSettings();

			sf::ContextSettings cset;
			cset.majorVersion = gset.majorVersion();
			cset.minorVersion = gset.minorVersion();

			cset.stencilBits = gset.stencilBits();
			cset.depthBits = gset.depthBits();
			cset.antialiasingLevel = gset.multisampleSamples();

			window.create(sf::VideoMode(size.x, size.y), title, flags, cset);
			window.setActive(true);

			
		}

		~SFMLWindow() override {}

		RenderSettings getRenderSettings() const override {
			GLSettings gset;
			sf::ContextSettings cset = window.getSettings();
			gset.majorVersion() = cset.majorVersion;
			gset.minorVersion() = cset.minorVersion;

			gset.depthBits() = cset.depthBits;
			gset.stencilBits() = cset.stencilBits;

			gset.multisampleSamples() = cset.antialiasingLevel;
			if (gset.multisampleSamples() > 0) {
				gset.multisampleBuffers() = 1;
			}
			
			if (cset.attributeFlags & sf::ContextSettings::Debug) {
				gset.flags() |= GLContextFlags::Debug;
			}

			return gset;
		}

		bool setRenderSettings(const RenderSettings& settings) override {
			return false;
		}

		Style getStyle() const override {
			return style;
		}
		glm::ivec2 getSize() const override {
			auto val = window.getSize();
			return { val.x, val.y };
		}
		glm::ivec2 getPosition() const override {
			auto val = window.getPosition();
			return { val.x, val.y };
		}

		bool isOpen() const override {
			return window.isOpen();
		}
		bool isVisible() const override {
			return visible;
		}
		std::string_view getTitle() const override {
			return std::string_view(title);
		}

		void setSize(glm::ivec2 val) override {
			window.setSize({ static_cast<unsigned>(val.x), static_cast<unsigned>(val.y) });
		}
		void setPosition(glm::ivec2 val) override {
			window.setPosition({val.x, val.y});
		}

		void close() override {
			window.close();
		}
		void setVisible(bool val) override {
			window.setVisible(val);
		}
		void setTitle(std::string_view _title) override {
			title = _title;
			window.setTitle(title.c_str());
		}
		void setActive(bool val) override {
			window.setActive(val);
		}

		void swapBuffers() override {
			window.display();
		}

		bool pollInput(ez::InputEvent& ev) override {
			sf::Event sfev;
			if (window.pollEvent(sfev)) {
				ev = remapSFMLEvent(sfev);
				return true;
			}
			else {
				return false;
			}
		}
	private:
		bool visible;
		Style style;
		std::string title;
		sf::Window window;
	};
}