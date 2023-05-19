#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Renderer;

	class ZINET_GRAPHIC_LAYER_API Imgui
	{
		inline static ConsoleLogger Logger = ConsoleLogger::Create("Imgui");

	public:

		Imgui() = default;
		Imgui(const Imgui& Other) = default;
		Imgui(Imgui&& Other) = default;

		Imgui& operator=(const Imgui& Other) = default;
		Imgui& operator=(Imgui&& Other) = default;

		~Imgui() noexcept;

		void init(Renderer& renderer);

		const DescriptorPool& getDescriptorPool() const { return descriptorPool; }

	private:

		void createDescriptorPool(Renderer& renderer);

		DescriptorPool descriptorPool;
		bool isInitialized = false;

	};

}