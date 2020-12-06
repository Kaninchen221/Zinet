#include "Zinet/Frame/ZtWindow.h"

namespace zt {

	Window::Window(const WindowSettings& settings) {

		applySettingsToBaseWindow(settings);

	}

	void Window::setLoop(LoopPtr& loop) noexcept
	{
		this->loop = std::move(loop);
	}

	inline void Window::startLoop(const LoopSettings& loopSettings)
	{
		if (loop) {
			loop->start(loopSettings, baseWindow);
		}
		else {
			throw FrameException("setLoop must be invoked before startLoop");
		}
	}

	inline void Window::applySettingsToBaseWindow(const WindowSettings& windowSettings)
	{
		auto videoMode = CreateVideoMode(windowSettings);
		auto contextSettings = CreateContextSettings(windowSettings);
		auto title = windowSettings.title;
		auto style = static_cast<sf::Uint32>(windowSettings.style);

		baseWindow.create(videoMode, title, style, contextSettings);
	}

	inline typename Window::VideoMode Window::CreateVideoMode(const WindowSettings& windowSettings)
	{
		VideoMode videoMode = VideoMode::getFullscreenModes().front();

		if (!videoMode.isValid()) {
			throw FrameException("Video mode is invalid");
		}

		return videoMode;
	}

	inline typename Window::ContextSettings Window::CreateContextSettings(const WindowSettings& windowSettings)
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