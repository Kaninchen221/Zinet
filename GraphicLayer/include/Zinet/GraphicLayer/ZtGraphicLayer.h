#pragma once

#include "Zinet/Core/ZtCore.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/vulkan.hpp"
#include "vulkan/vulkan_raii.hpp"

// Needed for future compability
#define ZINET_GRAPHIC_LAYER_API ZINET_CORE_API