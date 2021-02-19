#pragma once
#include <glm/vec2.hpp>

namespace ez {
	struct PixelFormat {
		enum class Kind {
			Unknown = 0,

			RGB888 = 370546692,
			BGR888 = 374740996,

			RGBX8888 = 371595268,
			BGRX8888 = 375789572,

			ARGB8888 = 372645892,
			ABGR8888 = 376840196,

			RGBA8888 = 373694468,
			BGRA8888 = 377888772,

			YV12 = 842094169,
			IYUV = 1448433993,
			YUY2 = 844715353,
			UYVY = 1498831189,
			NV12 = 842094158,
			NV21 = 825382478,
			YVYU = 1431918169,
		};
		static constexpr Kind
			Unknown = Kind::Unknown,
			RGB888 = Kind::RGB888,
			BGR888 = Kind::BGR888,
			RGBX8888 = Kind::RGBX8888,
			BGRX8888 = Kind::BGRX8888,
			ARGB8888 = Kind::ARGB8888,
			ABGR8888 = Kind::ABGR8888,
			RGBA8888 = Kind::RGBA8888,
			BGRA8888 = Kind::BGRA8888,

			YV12 = Kind::YV12,
			IYUV = Kind::IYUV,
			YUY2 = Kind::YUY2,
			UYVY = Kind::UYVY,
			NV12 = Kind::NV12,
			NV21 = Kind::NV21,
			YVYU = Kind::YVYU;

		PixelFormat(const PixelFormat&) noexcept = default;
		PixelFormat& operator=(const PixelFormat&) noexcept = default;
		~PixelFormat() = default;
		
		PixelFormat(Kind _kind = Kind::Unknown) noexcept;

		operator Kind() const noexcept;

		int bytesPerPixel() const noexcept;
		int bitsPerPixel() const noexcept;
		bool isIndexed() const noexcept;
		bool hasAlpha() const noexcept;
	private:
		Kind kind;
	};

	struct DisplayMode {
		bool isValid() const noexcept;

		const PixelFormat format;
		const glm::ivec2 size;
		const int refreshRate;
		void*const driverData;
	};

	class Display {
	public:
		static int count();

		Display(const Display&) noexcept = default;
		Display& operator=(const Display&) noexcept = default;

		Display(int _index) noexcept;
		
		int numModes() const;
		DisplayMode getMode(int index) const;
		DisplayMode getCurrentMode() const;
		DisplayMode getNativeMode() const;
	private:
		int display;
	};
};