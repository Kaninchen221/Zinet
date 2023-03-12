#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

// VMA
namespace zt::gl
{
	class ZINET_GRAPHIC_LAYER_API VmaAllocLogger
	{
		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Vma_alloc");

	public:

		template<typename... Args>
		static void Log(fmt::format_string<Args...> format, [[maybe_unused]] Args &&...args) // TODO use args
		{
			Logger->info(format);
		}

	};
}

#define VMA_DEBUG_LOG(format, ...) \
	zt::gl::VmaAllocLogger::Log(format, __VA_ARGS__);

#define VMA_VULKAN_VERSION 1002000 // Vulkan 1.2
#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>