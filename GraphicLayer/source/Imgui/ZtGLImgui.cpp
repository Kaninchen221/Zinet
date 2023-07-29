#include "Zinet/GraphicLayer/Imgui/ZtGLImgui.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLCommandBuffer.h"

#include "Zinet/Core/ZtDebug.h"

#include <imgui.h>
#include <imgui_impl_vulkan.h>
#include <imgui_impl_glfw.h>

namespace zt::gl
{
	void Imgui::preinit(RendererContext& rendererContext)
	{
		#ifdef ZINET_DEBUG
		IMGUI_CHECKVERSION();
		#endif // ZINET_DEBUG

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForVulkan(rendererContext.getWindow().getInternal(), true);
	}

	void Imgui::init(RendererContext& rendererContext)
	{
		createDescriptorPool(rendererContext);
		
		ImGui_ImplVulkan_InitInfo initInfo = {};
		initInfo.Instance = rendererContext.getInstance().getVk();
		initInfo.PhysicalDevice = rendererContext.getPhysicalDevice().getVk();
		initInfo.Device = rendererContext.getDevice().getVk();
		initInfo.QueueFamily = rendererContext.getQueueFamilyIndex();
		initInfo.Queue = rendererContext.getQueue().getVk();
		//initInfo.PipelineCache = g_PipelineCache;
		initInfo.DescriptorPool = descriptorPool.getVk();
		initInfo.Allocator = nullptr;
		initInfo.MinImageCount = 3;
		initInfo.ImageCount = 3;
		initInfo.CheckVkResultFn = LogImgui;
		initInfo.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
		isInitialized = ImGui_ImplVulkan_Init(&initInfo, rendererContext.getRenderPass().getVk());

		auto function = [](CommandBuffer& commandBuffer) 
		{ 
			ImGui_ImplVulkan_CreateFontsTexture(commandBuffer.getVk()); 
		};
		
		rendererContext.submitCommandsWaitIdle(function);

		ImGui_ImplVulkan_DestroyFontUploadObjects();
	}

	void Imgui::createDescriptorPool(RendererContext& rendererContext)
	{
		// It's copied from imgui demo
		std::array<vk::DescriptorPoolSize, 11> descriptorPoolSizes =
		{
			vk::DescriptorPoolSize{ vk::DescriptorType::eSampler, 1000u },
			vk::DescriptorPoolSize{ vk::DescriptorType::eCombinedImageSampler, 1000u },
			vk::DescriptorPoolSize{ vk::DescriptorType::eSampledImage, 1000u },
			vk::DescriptorPoolSize{ vk::DescriptorType::eStorageImage, 1000u },
			vk::DescriptorPoolSize{ vk::DescriptorType::eUniformTexelBuffer, 1000u },
			vk::DescriptorPoolSize{ vk::DescriptorType::eStorageTexelBuffer, 1000u },
			vk::DescriptorPoolSize{ vk::DescriptorType::eUniformBuffer, 1000u },
			vk::DescriptorPoolSize{ vk::DescriptorType::eStorageBuffer, 1000u },
			vk::DescriptorPoolSize{ vk::DescriptorType::eUniformBufferDynamic, 1000u },
			vk::DescriptorPoolSize{ vk::DescriptorType::eStorageBufferDynamic, 1000u },
			vk::DescriptorPoolSize{ vk::DescriptorType::eInputAttachment, 1000u }
		};

		vk::DescriptorPoolCreateInfo createInfo = {};
		createInfo.flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet;
		createInfo.maxSets = 1000;
		createInfo.poolSizeCount = static_cast<std::uint32_t>(descriptorPoolSizes.size());
		createInfo.pPoolSizes = descriptorPoolSizes.data();

		descriptorPool.create(rendererContext.getDevice(), createInfo);
	}

	Imgui::~Imgui() noexcept
	{
		if (isInitialized)
			deinit();
	}

	void Imgui::LogImgui(VkResult error)
	{
		vk::Result result{ error };
		if (result != vk::Result::eSuccess)
		{
			Logger->error("Imgui error {}", error);
			zt::core::Ensure(false);
		}
	}

	void Imgui::update()
	{
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();
	}

	void Imgui::draw(CommandBuffer& drawCommandBuffer)
	{
		if (!drawCommandBuffer.getIsCommandBufferInvalid())
			ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), drawCommandBuffer.getVk());
	}

	void Imgui::deinit()
	{
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
	}

}