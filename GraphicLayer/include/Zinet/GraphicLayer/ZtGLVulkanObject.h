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

		const InternalType& getInternal() const;

		InternalType* operator->();

		const InternalType* operator->() const;

		bool operator == (const InternalType& other) const;

		void clear() { internal.clear(); }

		bool isValid() const { return *internal != *InternalType{ std::nullptr_t{} }; }

		// TODO: Add access operator that return "vk::ClassName" not "vk::raii::ClassName"

	protected:

		InternalType internal{ std::nullptr_t{} };

	};

	template<class InternalType>
	inline InternalType& VulkanObject<InternalType>::getInternal()
	{
		return internal;
	}

	template<class InternalType>
	inline const InternalType& VulkanObject<InternalType>::getInternal() const
	{
		return internal;
	}

	template<class InternalType>
	inline InternalType* VulkanObject<InternalType>::operator->()
	{
		return &internal;
	}

	template<class InternalType>
	inline const InternalType* VulkanObject<InternalType>::operator->() const
	{
		return &internal;
	}

	template<class InternalType>
	inline bool VulkanObject<InternalType>::operator==(const InternalType& other) const
	{
		return *getInternal() == *other;
	}

}