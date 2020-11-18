#include "Zinet/Main/ECRS/ZtComponent.h"

namespace zt {

	Component::Component(const Component& other) noexcept 
	{	
		*this = other;
	}

	Component::Component(Component&& other) noexcept 
	{
		*this = std::move(other);
	}

	Component::Component(Identificator entityOwnerIdentificator) noexcept 
	{
		this->entityOwnerIdentificator = entityOwnerIdentificator;

		try {
			uniqueIdentificator = ComponentsUniqueIndexer.reserve();
		}
		catch (const std::exception& ex) {
			Logger::Error(LoggerName, ex.what());
		}
		catch (...) {
			Logger::Critical(LoggerName, "Uncatched exception");
		}
	}

	Component& Component::operator=(const Component& other) noexcept
	{
		entityOwnerIdentificator = other.entityOwnerIdentificator;
		setTag(other.tag);

		try {
			uniqueIdentificator = ComponentsUniqueIndexer.reserve();
		}
		catch (const std::exception& ex) {
			Logger::Error(LoggerName, ex.what());
		}

		return *this;
	}

	Component& Component::operator=(Component&& other) noexcept
	{
		tag = std::move(other.tag);
		entityOwnerIdentificator = std::move(other.entityOwnerIdentificator);
		uniqueIdentificator = std::move(other.uniqueIdentificator);

		try {
			other.uniqueIdentificator = ComponentsUniqueIndexer.reserve();
		}
		catch (const std::exception& ex) {
			Logger::Error(LoggerName, ex.what());
		}
		catch (...) {
			Logger::Critical(LoggerName, "Uncatched exception");
		}

		return *this;
	}

	Component::~Component() noexcept
	{
		try {
			ComponentsUniqueIndexer.release(uniqueIdentificator);
		}
		catch (const std::exception& ex) {
			Logger::Error(LoggerName, ex.what());
		}
	}

	void Component::setOwnerIdentificator(Identificator entityOwnerIdentificator) noexcept
	{
		this->entityOwnerIdentificator = entityOwnerIdentificator;
	}

	Identificator Component::getOwnerIdentificator() const noexcept
	{
		return entityOwnerIdentificator;
	}

	void Component::setTag(const Tag& tag) noexcept
	{
		try {
			this->tag = tag;
		}
		catch (const std::exception& ex) {
			Logger::Error(LoggerName, ex.what());
		}
	}

	Component::Tag Component::getTag() const noexcept
	{
		return tag;
	}

	Identificator Component::getIdentificator() const noexcept
	{
		return uniqueIdentificator;
	}

}