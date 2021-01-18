#include "ez/window/RenderSettings.hpp"
#include <cassert>

namespace ez::window {
	RenderSettings::RenderSettings() noexcept
		: type(Type::None)
	{}

	RenderSettings::Type RenderSettings::getType() const {
		return type;
	}

	GLSettings& RenderSettings::asGLSettings() {
		assert(type == Type::OpenGL);
		return static_cast<GLSettings&>(*this);
	}
	const GLSettings& RenderSettings::asGLSettings() const {
		assert(type == Type::OpenGL);
		return static_cast<const GLSettings&>(*this);
	}

	VulkanSettings& RenderSettings::asVulkanSettings() {
		assert(type == Type::Vulkan);
		return static_cast<VulkanSettings&>(*this);
	}
	const VulkanSettings& RenderSettings::asVulkanSettings() const {
		assert(type == Type::Vulkan);
		return static_cast<const VulkanSettings&>(*this);
	}

	RenderSettings::RenderSettings(Type _type) noexcept
		: type(_type)
	{}



	GLSettings::GLSettings() noexcept
		: GLSettings(3, 2)
	{}
	GLSettings::GLSettings(int major, int minor) noexcept
		: RenderSettings(Type::OpenGL)
	{
		majorVersion() = major;
		minorVersion() = minor;

		colorBits() = { 8, 8, 8, 8 };
		accumBits() = { 0, 0, 0, 0 };

		depthBits() = 24;
		stencilBits() = 0;

		multisampleBuffers() = 0;
		multisampleSamples() = 0;
	}

	RenderSettings::Bits& GLSettings::colorBits() {
		return glData.colorBits;
	}
	const RenderSettings::Bits& GLSettings::colorBits() const {
		return glData.colorBits;
	}

	RenderSettings::Bits& GLSettings::accumBits() {
		return glData.accumBits;
	}
	const RenderSettings::Bits& GLSettings::accumBits() const {
		return glData.accumBits;
	}

	int GLSettings::depthBits() const {
		return glData.depthBits;
	}
	unsigned char& GLSettings::depthBits() {
		return glData.depthBits;
	}

	int GLSettings::stencilBits() const {
		return glData.stencilBits;
	}
	unsigned char& GLSettings::stencilBits() {
		return glData.stencilBits;
	}

	int GLSettings::multisampleBuffers() const {
		return glData.msBuffers;
	}
	unsigned char& GLSettings::multisampleBuffers() {
		return glData.msBuffers;
	}

	int GLSettings::multisampleSamples() const {
		return glData.msSamples;
	}
	unsigned char& GLSettings::multisampleSamples() {
		return glData.msSamples;
	}

	int GLSettings::majorVersion() const {
		return glData.major;
	}
	unsigned char& GLSettings::majorVersion() {
		return glData.major;
	}

	int GLSettings::minorVersion() const {
		return glData.minor;
	}
	unsigned char& GLSettings::minorVersion() {
		return glData.minor;
	}

	bool GLSettings::isForwardCompatible() const noexcept {
		return (glData.flags & GLContextFlags::ForwardCompatible) != GLContextFlags::None;
	}
	bool GLSettings::isDebug() const noexcept {
		return (glData.flags & GLContextFlags::Debug) != GLContextFlags::None;
	}
	bool GLSettings::isNoError() const noexcept {
		return (glData.flags & GLContextFlags::NoError) != GLContextFlags::None;
	}
	bool GLSettings::isRobustAccess() const noexcept {
		return (glData.flags & GLContextFlags::RobustAccess) != GLContextFlags::None;
	}

	GLContextFlags& GLSettings::flags() noexcept {
		return glData.flags;
	}
	const GLContextFlags& GLSettings::flags() const noexcept {
		return glData.flags;
	}

	GLProfile& GLSettings::profile() noexcept {
		return glData.profile;
	}
	const GLProfile& GLSettings::profile() const noexcept {
		return glData.profile;
	}



	VulkanSettings::VulkanSettings(VkInstance_T* _instance) noexcept 
		: RenderSettings(Type::Vulkan)
	{
		instance() = _instance;
	}

	VkInstance_T*& VulkanSettings::instance() {
		return vulkanData.instance;
	}
	VkInstance_T const* const& VulkanSettings::instance() const {
		return vulkanData.instance;
	}
}

ez::window::GLContextFlags operator|(ez::window::GLContextFlags lh, ez::window::GLContextFlags rh) {
	using ez::window::GLContextFlags;
	return static_cast<GLContextFlags>(static_cast<int>(lh) | static_cast<int>(rh));
}
ez::window::GLContextFlags operator&(ez::window::GLContextFlags lh, ez::window::GLContextFlags rh) {
	using ez::window::GLContextFlags;
	return static_cast<GLContextFlags>(static_cast<int>(lh) & static_cast<int>(rh));
}
ez::window::GLContextFlags operator^(ez::window::GLContextFlags lh, ez::window::GLContextFlags rh) {
	using ez::window::GLContextFlags;
	return static_cast<GLContextFlags>(static_cast<int>(lh) ^ static_cast<int>(rh));
}
ez::window::GLContextFlags operator~(ez::window::GLContextFlags lh) {
	using ez::window::GLContextFlags;
	return static_cast<GLContextFlags>((~static_cast<int>(lh)) ) & GLContextFlags::All;
}

ez::window::GLContextFlags& operator|=(ez::window::GLContextFlags& lh, ez::window::GLContextFlags rh) {
	lh = lh | rh;
	return lh;
}
ez::window::GLContextFlags& operator&=(ez::window::GLContextFlags& lh, ez::window::GLContextFlags rh) {
	lh = lh & rh;
	return lh;
}
ez::window::GLContextFlags& operator^=(ez::window::GLContextFlags& lh, ez::window::GLContextFlags rh) {
	lh = lh ^ rh;
	return lh;
}