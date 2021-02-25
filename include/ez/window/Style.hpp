#pragma once
#include <ez/BitFlags.hpp>

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
		_EnableOperators
	};

	using StyleBase = ez::BitFlags<StyleOption>;
	struct Style : public StyleBase {
		using StyleBase::None;
		using StyleBase::All;

		static constexpr StyleBase Resize{ StyleOption::Resize };
		static constexpr StyleBase Close{ StyleOption::Close };
		static constexpr StyleBase Visible{ StyleOption::Visible };
		static constexpr StyleBase HighDPI{ StyleOption::HighDPI };
		static constexpr StyleBase AlwaysOnTop{ StyleOption::AlwaysOnTop };
		static constexpr StyleBase Fullscreen{ StyleOption::Fullscreen };
		
		using StyleBase::StyleBase;

		constexpr Style(const StyleBase& val)
			: StyleBase(val)
		{};
	};

	namespace StylePreset {
		static constexpr Style None = Style::None;

		static constexpr Style Default = Style::Resize | Style::Close | Style::Visible;

		static constexpr Style Borderless = Style::Visible;

		static constexpr Style All = Style::All;
	}
};




