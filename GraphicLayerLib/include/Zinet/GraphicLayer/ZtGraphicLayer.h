#pragma once

#include "Zinet/Core/ZtCoreConfig.h"

// GLFW
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// Vulkan
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>

// Needed for future compatibility
#define ZINET_GRAPHIC_LAYER_API ZINET_CORE_API

// GLM
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES

// STB
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>