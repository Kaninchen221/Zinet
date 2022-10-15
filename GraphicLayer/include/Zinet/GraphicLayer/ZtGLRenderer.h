#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLDebugUtilsMessenger.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Renderer
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Renderer");

	public:

		Renderer();
		Renderer(const Renderer& other) = default;
		Renderer(Renderer&& other) = default;

		Renderer& operator = (const Renderer& other) = default;
		Renderer& operator = (Renderer&& other) = default;

		~Renderer() noexcept;

		void initialize();

		const Context& getContext() const;

		const Instance& getInstance() const;

		const DebugUtilsMessenger& getDebugUtilsMessenger() const;

		const Window& getWindow() const;

		const Surface& getSurface() const;

		const PhysicalDevice& getPhysicalDevice() const;

	protected:

		void createInstance();
		void createDebugUtilsMessenger();
		void createWindow();
		bool createSurface();
		bool createPhysicalDevice();

		Context context;
		Instance instance;
		DebugUtilsMessenger debugUtilsMessenger;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;

	};

}