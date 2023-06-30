#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class ZINET_GRAPHIC_LAYER_API VmaAllocLogger
	{
		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Vma_alloc");
		static inline std::once_flag onceFlag = {};

	public:

		VmaAllocLogger() = delete;
		VmaAllocLogger(const VmaAllocLogger& other) = delete;
		VmaAllocLogger(VmaAllocLogger&& other) = delete;

		VmaAllocLogger& operator = (const VmaAllocLogger& other) = delete;
		VmaAllocLogger& operator = (VmaAllocLogger&& other) = delete;

		~VmaAllocLogger() noexcept = delete;

		template<typename... Args>
		static void Log(const std::string& format, Args &&...args)
		{
			std::call_once(onceFlag, []() { Logger.turnOff(); });

			char buffer[1024];
			sprintf_s(buffer, sizeof(buffer), format.c_str(), args...); // MSVC only

			Logger->info(buffer);
		}

	};

}

#define VMA_DEBUG_LOG(format, ...) \
	zt::gl::VmaAllocLogger::Log(format, __VA_ARGS__);

#define VMA_VULKAN_VERSION 1002000 // Vulkan 1.2
#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>