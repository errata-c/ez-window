#include <ez/window/Style.hpp>

using namespace ez::window;

static constexpr int maskAll = (int)StylePreset::All;

Style::Style() noexcept
	: Style(Style::None)
{}
Style::Style(StyleOption opt) noexcept
	: value(1 << (int)opt)
{}
Style::Style(StylePreset preset) noexcept
	: value((int)preset)
{}

bool Style::allOf(const Style& other) const noexcept {
	return (value & other.value) == other.value;
}
bool Style::noneOf(const Style& other) const noexcept {
	return (value & other.value) == 0;
}
bool Style::anyOf(const Style& other) const noexcept {
	return (value & other.value) != 0;
}

void Style::clear() noexcept {
	value = 0;
}

Style& Style::operator|=(const Style& other) noexcept {
	value |= other.value;
	return *this;
}
Style& Style::operator&=(const Style& other) noexcept {
	value &= other.value;
	return *this;
}
Style& Style::operator^=(const Style& other) noexcept {
	value ^= other.value;
	value &= maskAll;
	return *this;
}
bool Style::operator==(const Style& other) const noexcept {
	return value == other.value;
}
bool Style::operator!=(const Style& other) const noexcept {
	return value != other.value;
}

Style::operator bool() const {
	return value != 0;
}

Style operator|(const Style& lv, const Style& rv) noexcept {
	Style res = lv;
	res |= rv;
	return res;
}
Style operator&(const Style& lv, const Style& rv) noexcept {
	Style res = lv;
	res &= rv;
	return res;
}
Style operator~(const Style& lv) noexcept {
	Style res = lv;
	res.value = (~res.value) & maskAll;
	return res;
}

Style(operator|)(const StylePreset& lv, const Style& rv) noexcept {
	return Style{ lv } | rv;
}
Style(operator&)(const StylePreset& lv, const Style& rv) noexcept {
	return Style{ lv } &rv;
}
/*
Style(operator|)(const Style& lv, const StylePreset& rv) noexcept {
	return lv | Style{ rv };
}
Style(operator&)(const Style& lv, const StylePreset& rv) noexcept {
	return lv & Style{ rv };
}
*/
Style(operator~)(const StylePreset& lv) noexcept {
	return ~Style{ lv };
}
