#pragma once

#include "Zinet/Frame/ZtFrameConfig.h"

#include <string>

namespace zt {

	struct ZINET_FRAME_API WindowSettings {

		enum class OpenGLAttribute {
			Default = 0,
			Core = 1 << 0,
			Debug = 1 << 2
		};

		enum class Style {
			None = 0,
			Titlebar = 1 << 0,
			Resize = 1 << 1,
			Close = 1 << 2,
			Fullscreen = 1 << 3
		};

		Style style = Style::Resize;
		std::string title = "Zinet";
		unsigned int width = 400u;
		unsigned int height = 400u;
		unsigned int bitsPerPixel = 32u;
		unsigned int depthBits = 0u;
		unsigned int stencilBits = 0u;
		unsigned int antialiasingLevel = 0u;
		unsigned int openGLMajorVersion = 1u;
		unsigned int openGLMinorVersion = 1u;
		OpenGLAttribute openGLAttribute = OpenGLAttribute::Default;
		bool sRgbCapable = false;

	};

}