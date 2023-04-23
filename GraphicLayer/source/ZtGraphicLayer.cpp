#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

// TODO: Move it to separate file
// VMA
namespace zt::gl
{
	class ZINET_GRAPHIC_LAYER_API VmaAllocLogger
	{
		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Vma_alloc");
		static inline std::once_flag onceFlag = {};

	public:

		VmaAllocLogger() = default;
		VmaAllocLogger(const VmaAllocLogger& other) = default;
		VmaAllocLogger(VmaAllocLogger&& other) = default;

		VmaAllocLogger& operator = (const VmaAllocLogger& other) = default;
		VmaAllocLogger& operator = (VmaAllocLogger&& other) = default;

		~VmaAllocLogger() noexcept = default;

		template<typename... Args>
		static void Log(fmt::format_string<Args...> format, [[maybe_unused]] Args &&...args) // TODO use args
		{
			std::call_once(onceFlag, []() { Logger->set_level(spdlog::level::off); }); // TODO Refactor to: turnOn/Off (logger) functions 

			Logger->info(format);
		}

	};

}

#define VMA_DEBUG_LOG(format, ...) \
	zt::gl::VmaAllocLogger::Log(format, __VA_ARGS__);

#define VMA_VULKAN_VERSION 1002000 // Vulkan 1.2
#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>