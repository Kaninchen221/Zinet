#pragma once

namespace zt::gl
{

	template<class InternalType>
	class VulkanObject
	{

	public:

		VulkanObject() = default;
		VulkanObject(const VulkanObject& Other) = default;
		VulkanObject(VulkanObject&& Other) = default;

		VulkanObject& operator=(const VulkanObject& Other) = default;
		VulkanObject& operator=(VulkanObject&& Other) = default;

		~VulkanObject() noexcept = default;

		InternalType& getInternal();

		InternalType* operator->();

	protected:

		InternalType internal{ std::nullptr_t{} };

	};

	template<class InternalType>
	inline InternalType& VulkanObject<InternalType>::getInternal()
	{
		return internal;
	}

	template<class InternalType>
	inline InternalType* VulkanObject<InternalType>::operator->()
	{
		return &internal;
	}

}