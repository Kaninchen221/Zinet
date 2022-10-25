#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

#include "vk_mem_alloc.h"

namespace zt::gl
{
	class Renderer;

	class ZINET_GRAPHIC_LAYER_API Vma
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Vma");

	public:

		Vma() = default;
		Vma(const Vma& other) = default;
		Vma(Vma&& other) = default;

		Vma& operator = (const Vma& other) = default;
		Vma& operator = (Vma&& other) = default;

		~Vma() noexcept = default;

		const VmaAllocator getInternal() const;

		VmaAllocatorCreateInfo createAllocatorCreateInfo(const Renderer& renderer) const;

		void create(const VmaAllocatorCreateInfo& allocatorCreateInfo);

	protected:

		VmaAllocator vmaAllocator{};

	};

}