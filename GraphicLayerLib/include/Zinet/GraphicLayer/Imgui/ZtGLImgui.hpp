#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLDescriptorPool.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{
	class RendererContext;
	class CommandBuffer;

	class ZINET_GRAPHIC_LAYER_API Imgui
	{
		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Imgui");

		static void LogImgui(VkResult error);

	public:

		Imgui() = default;
		Imgui(const Imgui& Other) = default;
		Imgui(Imgui&& Other) = default;

		Imgui& operator=(const Imgui& Other) = default;
		Imgui& operator=(Imgui&& Other) = default;

		~Imgui() noexcept;

		// Call once for the entire program
		void preinit(RendererContext& rendererContext);

		void init(RendererContext& rendererContext);

		void deinit();

		void update();
		
		void draw(CommandBuffer& drawCommandBuffer);

		const DescriptorPool& getDescriptorPool() const { return descriptorPool; }

	private:

		void createDescriptorPool(RendererContext& rendererContext);

		DescriptorPool descriptorPool;
		bool isInitialized = false;

	};

}