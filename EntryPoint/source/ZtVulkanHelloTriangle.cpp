#include "ZtVulkanHelloTriangle.h"

void ZtVulkanHelloTriangle::Run()
{
	InitWindow();
	InitVulkan();
	MainLoop();
	Cleanup();
}

void ZtVulkanHelloTriangle::InitWindow()
{
}

void ZtVulkanHelloTriangle::InitVulkan()
{
	CreateInstance();
	SetupDebugMessenger();
}

void ZtVulkanHelloTriangle::CreateInstance()
{
	if (!CheckValidationLayerSupport())
	{
		throw std::runtime_error("CheckValidationLayerSupport return false");
	}

	vk::ApplicationInfo ApplicationInfo{};
	ApplicationInfo.sType = vk::StructureType::eApplicationInfo;
	ApplicationInfo.pApplicationName = "Hello Triangle";
	ApplicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	ApplicationInfo.pEngineName = "No Engine";
	ApplicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	ApplicationInfo.apiVersion = VK_API_VERSION_1_0;

	vk::InstanceCreateInfo InstanceCreateInfo{};
	InstanceCreateInfo.sType = vk::StructureType::eInstanceCreateInfo;
	InstanceCreateInfo.pApplicationInfo = &ApplicationInfo;
	
	auto Extensions = GetRequiredExtensions();
	InstanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(Extensions.size());
	InstanceCreateInfo.ppEnabledExtensionNames = Extensions.data();

	if (EnableValidationLayers) {
		InstanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size());
		InstanceCreateInfo.ppEnabledLayerNames = ValidationLayers.data();
	}
	else {
		InstanceCreateInfo.enabledLayerCount = 0;
	}

	Instance = vk::createInstance(InstanceCreateInfo);
	vk::Result Result = vk::createInstance(&InstanceCreateInfo, nullptr, &Instance);
	if (Result != vk::Result::eSuccess)
	{
		throw std::runtime_error("Failed to create instance");
	}

	// Extensions - this should be done before create instance
	std::vector<vk::ExtensionProperties> ExtensionProperties = vk::enumerateInstanceExtensionProperties();
	std::cout << "Available extensions:\n";
	for (const auto& Extension : ExtensionProperties)
	{
		std::cout << '\t' << Extension.extensionName << '\n';
	}
	std::cout << '\n';

}

bool ZtVulkanHelloTriangle::CheckValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	std::vector<vk::LayerProperties> AvailableLayers = vk::enumerateInstanceLayerProperties();

	for (const std::string& ValidationLayer : ValidationLayers)
	{
		bool FoundLayer = false;
		for (const vk::LayerProperties& AvailableLayer : AvailableLayers)
		{ 
			const std::string& LayerName = AvailableLayer.layerName;
			if (ValidationLayer == LayerName)
			{ 
				FoundLayer = true;
				break;
			}
		}

		if (!FoundLayer)
		{
			return false;
		}
	}

	return true;
}

std::vector<const char*> ZtVulkanHelloTriangle::GetRequiredExtensions()
{
	uint32_t GlfwExtensionCount = 0;
	const char** GlfwExtensions;
	GlfwExtensions = glfwGetRequiredInstanceExtensions(&GlfwExtensionCount);

	std::vector<const char*> Extensions(GlfwExtensions, GlfwExtensions + GlfwExtensionCount);

	if (EnableValidationLayers) {
		Extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return Extensions;
}

void ZtVulkanHelloTriangle::MainLoop()
{
	
}

void ZtVulkanHelloTriangle::Cleanup()
{
	if (EnableValidationLayers) {
		DestroyDebugUtilsMessengerEXT(Instance, DebugMessenger, nullptr);
	}
}

void ZtVulkanHelloTriangle::SetupDebugMessenger()
{
	if (!EnableValidationLayers)
	{
		return;
	}

	VkDebugUtilsMessengerCreateInfoEXT CreateInfo{};
	CreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	CreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	CreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	CreateInfo.pfnUserCallback = DebugCallback;
	CreateInfo.pUserData = nullptr; // Optional

	if (CreateDebugUtilsMessengerEXT(Instance, &CreateInfo, nullptr, &DebugMessenger) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to set up debug messenger!");
	}
}

VKAPI_ATTR VkBool32 VKAPI_CALL ZtVulkanHelloTriangle::DebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{
	if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) 
	{
		throw std::runtime_error("Vulkan fatal error");
	}

	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

	return VK_FALSE;
}

VkResult ZtVulkanHelloTriangle::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto Func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(Instance, "vkCreateDebugUtilsMessengerEXT");
	if (Func != nullptr) {
		return Func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	
}

void ZtVulkanHelloTriangle::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance, debugMessenger, pAllocator);
	}
}
