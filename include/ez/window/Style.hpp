#pragma once

namespace ez::window {
	class Style;
	enum class StylePreset;
};

ez::window::Style (operator|)(const ez::window::Style& lv, const ez::window::Style& rv) noexcept;
ez::window::Style (operator&)(const ez::window::Style& lv, const ez::window::Style& rv) noexcept;
ez::window::Style (operator~)(const ez::window::Style& lv) noexcept;

// Conversion operators, allows presets to be used directly with Style class
ez::window::Style(operator|)(const ez::window::StylePreset& lv, const ez::window::Style& rv) noexcept;
ez::window::Style(operator&)(const ez::window::StylePreset& lv, const ez::window::Style& rv) noexcept;
//ez::window::Style(operator|)(const ez::window::Style& lv, const ez::window::StylePreset& rv) noexcept;
//ez::window::Style(operator&)(const ez::window::Style& lv, const ez::window::StylePreset& rv) noexcept;
ez::window::Style(operator~)(const ez::window::StylePreset& lv) noexcept;

namespace ez::window {
	// Individual options
	enum class StyleOption {
		Resize = 0,
		Close,
		Visible,
		HighDPI,
		AlwaysOnTop,
		Fullscreen,
		_Count,
	};

	// Option presets
	enum class StylePreset {
		None = 0,
		Default = (1 << (int)StyleOption::Resize) | (1 << (int)StyleOption::Close) | (1 << (int)StyleOption::Visible),
		Borderless = (1 << (int)StyleOption::Visible),
		All = (1 << (int)StyleOption::_Count) -1,
	};

	// Actual style class, combines the options as a set of flags.
	class Style {
	public:
		static constexpr StylePreset Resize = (StylePreset)(1 << (int)StyleOption::Resize);
		static constexpr StylePreset Close = (StylePreset)(1 << (int)StyleOption::Close);
		static constexpr StylePreset Visible = (StylePreset)(1 << (int)StyleOption::Visible);
		static constexpr StylePreset HighDPI = (StylePreset)(1 << (int)StyleOption::HighDPI);
		static constexpr StylePreset AlwaysOnTop = (StylePreset)(1 << (int)StyleOption::AlwaysOnTop);
		static constexpr StylePreset Fullscreen = (StylePreset)(1 << (int)StyleOption::Fullscreen);

		static constexpr StylePreset None = StylePreset::None;
		static constexpr StylePreset Default = StylePreset::Default;
		static constexpr StylePreset Borderless = StylePreset::Borderless;
		static constexpr StylePreset All = StylePreset::All;

		Style(const Style&) noexcept = default;
		~Style() = default;
		Style& operator=(const Style&) noexcept = default;

		Style() noexcept;
		Style(StyleOption opt) noexcept;
		Style(StylePreset preset) noexcept;

		bool allOf(const Style& val) const noexcept;
		bool noneOf(const Style& val) const noexcept;
		bool anyOf(const Style& val) const noexcept;

		void clear() noexcept;

		Style& operator|=(const Style& rv) noexcept;
		Style& operator&=(const Style& rv) noexcept;
		Style& operator^=(const Style& rv) noexcept;

		explicit operator bool() const;

		bool operator==(const Style& other) const noexcept;
		bool operator!=(const Style& other) const noexcept;

		friend ez::window::Style (::operator~)(const ez::window::Style&) noexcept;
	private:
		int value;
	};
};




