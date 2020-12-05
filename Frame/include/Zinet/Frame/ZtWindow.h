#pragma once

#include "Zinet/Frame/ZtFrameConfig.h"
#include "Zinet/Frame/ZtFrameException.h"
#include "Zinet/Frame/ZtLoop.h"
#include "Zinet/Frame/ZtWindowSettings.h"

#include "SFML/Graphics/RenderWindow.hpp"

namespace zt {

	template<class Loop>
	class ZINET_FRAME_API Window {

	public:

		using BaseWindow = typename Loop::BaseWindow;
		using VideoMode = sf::VideoMode;
		using ContextSettings = sf::ContextSettings;

		static constexpr bool IsLoopDerivedFromZtLoop() noexcept;
		static_assert(IsLoopDerivedFromZtLoop(), "Loop template param must derived from zt::Loop class");

		Window() = delete;
		Window(const Window& other) = delete;
		Window(Window&& other) = delete;

		Window(const WindowSettings& settings);

		Window& operator = (const Window& other) = delete;
		Window& operator = (Window&& other) = delete;

		~Window() noexcept = default;

		void startLoop(const LoopSettings& loopSettings);

	private:

		void applySettingsToBaseWindow(const WindowSettings& windowSettings);

		VideoMode createVideoMode(const WindowSettings& windowSettings);
		ContextSettings createContextSettings(const WindowSettings& windowSettings);

		Loop loop;
		BaseWindow baseWindow;

	};

	template<class Loop>
	constexpr bool Window<Loop>::IsLoopDerivedFromZtLoop() noexcept {
		return std::is_base_of_v<zt::Loop, Loop>;
	}

	template<class Loop>
	Window<Loop>::Window(const WindowSettings& settings) {
		
		applySettingsToBaseWindow(settings);

	}

	template<class Loop>
	inline void Window<Loop>::startLoop(const LoopSettings& loopSettings)
	{
		while (baseWindow.isOpen()) {
			loop.start(loopSettings, baseWindow);
		}
	}

	template<class Loop>
	inline void Window<Loop>::applySettingsToBaseWindow(const WindowSettings& windowSettings)
	{
		auto videoMode = createVideoMode(windowSettings);
		auto contextSettings = createContextSettings(windowSettings);
		auto title = windowSettings.title;
		auto style = static_cast<sf::Uint32>(windowSettings.style);

		baseWindow.create(videoMode, title, style, contextSettings);
	}

	template<class Loop>
	inline typename Window<Loop>::VideoMode Window<Loop>::createVideoMode(const WindowSettings& windowSettings)
	{
		VideoMode videoMode;
		videoMode.height = windowSettings.height;
		videoMode.width = windowSettings.width;
		videoMode.bitsPerPixel = windowSettings.bitsPerPixel;

		return videoMode;
	}

	template<class Loop>
	inline typename Window<Loop>::ContextSettings Window<Loop>::createContextSettings(const WindowSettings& windowSettings)
	{
		ContextSettings contextSettings;
		contextSettings.antialiasingLevel = windowSettings.antialiasingLevel;
		contextSettings.attributeFlags = static_cast<sf::Uint32>(windowSettings.openGLAttribute);
		contextSettings.depthBits = windowSettings.depthBits;
		contextSettings.majorVersion = windowSettings.openGLMajorVersion;
		contextSettings.minorVersion = windowSettings.openGLMinorVersion;
		contextSettings.sRgbCapable = windowSettings.sRgbCapable;
		contextSettings.stencilBits = windowSettings.stencilBits;

		return contextSettings;
	}

}