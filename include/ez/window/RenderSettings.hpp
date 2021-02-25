#pragma once
#include <cinttypes>
#include <ez/BitFlags.hpp>

// Predeclare actual structs, for compatibility
struct VkInstance_T;
struct VkSurfaceKHR_T;

namespace ez::window {
	// Provide for opengl, vulkan, or software.
	// Opengl and vulkan support sharing
	// Swap interval is important as well.

	enum class GLContextOption {
		ForwardCompatible = 0,
		Debug,
		RobustAccess,
		NoError,
		_Count,
		_EnableOperators
	};
	using GLContextFlagsBase = ez::BitFlags<GLContextOption>;

	struct GLContextFlags: public GLContextFlagsBase {
		using GLContextFlagsBase::None;
		using GLContextFlagsBase::All;

		static constexpr GLContextFlagsBase ForwardCompatible{ GLContextOption::ForwardCompatible };
		static constexpr GLContextFlagsBase Debug{ GLContextOption::Debug };
		static constexpr GLContextFlagsBase RobustAccess{ GLContextOption::RobustAccess };
		static constexpr GLContextFlagsBase NoError{ GLContextOption::NoError };
		
		using GLContextFlagsBase::GLContextFlagsBase;

		constexpr GLContextFlags(const GLContextFlagsBase& val)
			: GLContextFlagsBase(val)
		{};
	};

	enum class GLProfile {
		Default = 0,
		Core,
		Compatibility,
		ES
	};

	class GLSettings;
	class VulkanSettings;

	class RenderSettings {
	public:
		struct Bits {
			char red, green, blue, alpha;
		};

		enum class Type {
			OpenGL,
			Vulkan,
			None
		};

		Type getType() const;

		GLSettings& asGLSettings();
		const GLSettings& asGLSettings() const;

		VulkanSettings& asVulkanSettings();
		const VulkanSettings& asVulkanSettings() const;
	private:
		Type type;

	protected:
		RenderSettings(Type _type) noexcept;
		RenderSettings() noexcept;

		struct GLData {
			Bits colorBits, accumBits;
			unsigned char depthBits, stencilBits;
			unsigned char msBuffers, msSamples;
			unsigned char major, minor;
			GLContextFlags flags;
			GLProfile profile;
		} glData;

		struct VulkanData {
			VkInstance_T* instance;
			uint64_t surface;
		} vulkanData;
	};

	class GLSettings : public RenderSettings {
	public:
		GLSettings() noexcept;
		GLSettings(int major, int minor) noexcept;
			
		Bits& colorBits();
		const Bits& colorBits() const;

		Bits& accumBits();
		const Bits& accumBits() const;

		int depthBits() const;
		unsigned char& depthBits();

		int stencilBits() const;
		unsigned char& stencilBits();
			
		int multisampleBuffers() const;
		unsigned char& multisampleBuffers();

		int multisampleSamples() const;
		unsigned char& multisampleSamples();

		int majorVersion() const;
		unsigned char& majorVersion();

		int minorVersion() const;
		unsigned char& minorVersion();

		bool isForwardCompatible() const noexcept;
		bool isDebug() const noexcept;
		bool isNoError() const noexcept;
		bool isRobustAccess() const noexcept;

		GLContextFlags& flags() noexcept;
		const GLContextFlags& flags() const noexcept;

		GLProfile& profile() noexcept;
		const GLProfile& profile() const noexcept;
	};

	class VulkanSettings : public RenderSettings {
	public:
		VulkanSettings(VkInstance_T * _instance) noexcept;

		VkInstance_T*& instance();
		VkInstance_T const*const instance() const;
	};
};