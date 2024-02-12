#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"
#include "Zinet/Engine/Assets/ZtAsset.hpp"

#include "Zinet/Core/ZtLogger.hpp"
#include "Zinet/Core/Reflection/ZtClassInfo.hpp"
#include "Zinet/Core/Reflection/ZtClassPropertyInfo.hpp"

#include <tuple>


class Texture {};

ZT_REFLECT_NAMESPACE()
namespace zt::engine
{
	ZT_REFLECT_CLASS()
	class ZINET_ENGINE_API AssetTexture : public Asset
	{
		inline static auto Logger = core::ConsoleLogger::Create("AssetTexture");

	public:
		
		ZT_REFLECT_MEMBER(ReadOnly)
		int i1;

		ZT_REFLECT_MEMBER(ReadOnly)
		long long int lli1;

		ZT_REFLECT_MEMBER(ReadOnly)
		int i2;

		ZT_REFLECT_MEMBER(ReadOnly)
		Texture texture;

	protected:

	public:

/*GENERATED_CODE_START*/
		AssetTexture() = default;
		AssetTexture(const AssetTexture& other) = default;
		AssetTexture(AssetTexture&& other) = default;
		
		~AssetTexture() noexcept = default;
		
		AssetTexture& operator = (const AssetTexture& other) = default;
		AssetTexture& operator = (AssetTexture&& other) = default;
		
		const int& getI1() const { return i1; }
		
		const long long& getLli1() const { return lli1; }
		
		const int& getI2() const { return i2; }
		
		const Texture& getTexture() const { return texture; }
		
		class ClassInfo : public zt::core::reflection::ClassInfo
		{
		public:
		    std::string_view getClassName() const override { return "AssetTexture"; }
		
			zt::core::reflection::ClassPropertiesInfos getClassPropertiesInfos() override { return zt::core::reflection::ClassPropertiesInfos(std::vector{zt::core::reflection::ClassPropertyInfo{offsetof(AssetTexture, i1), "i1", "int"},
			                                                                                                                                               zt::core::reflection::ClassPropertyInfo{offsetof(AssetTexture, lli1), "lli1", "long long"},
			                                                                                                                                               zt::core::reflection::ClassPropertyInfo{offsetof(AssetTexture, i2), "i2", "int"},
			                                                                                                                                               zt::core::reflection::ClassPropertyInfo{offsetof(AssetTexture, texture), "texture", "Texture"}}); };
		
		};
		std::unique_ptr<zt::core::reflection::ClassInfo> getClassInfoObject() const { return std::make_unique<ClassInfo>(); }
		auto getCopyOfAllMembers() { return std::make_tuple(i1, lli1, i2, texture); };
		
/*GENERATED_CODE_END*/
	};
}