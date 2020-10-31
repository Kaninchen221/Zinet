#pragma once

#include "gtest/gtest.h"

#include "Zinet/Main/ZtUniqueIndexer.h"

class ZtUniqueIndexerTests : public ::testing::Test {
protected:


};

TEST_F(ZtUniqueIndexerTests, reserveTest) {

	zt::UniqueIndexer uniqueIndexer;

	auto samplesCount = 5u;
	for (auto expectedNumber = 0u; expectedNumber < samplesCount; expectedNumber++) {

		auto id = uniqueIndexer.reserve();
		auto idAsNumber = id.getNumber();
		ASSERT_EQ(expectedNumber, idAsNumber);

	}

}

TEST_F(ZtUniqueIndexerTests, releaseTest) {

	zt::UniqueIndexer uniqueIndexer;

	uniqueIndexer.reserve();
	auto idForRelease = uniqueIndexer.reserve();
	auto expectedIdNumber = idForRelease.getNumber();
	uniqueIndexer.release(idForRelease);
	
	auto idResult = uniqueIndexer.reserve();
	auto resultIdNumber = idResult.getNumber();

	ASSERT_EQ(expectedIdNumber, resultIdNumber);

}

TEST_F(ZtUniqueIndexerTests, releasedCountTest) {

	zt::UniqueIndexer uniqueIndexer;
	uniqueIndexer.reserve();
	uniqueIndexer.reserve();
	uniqueIndexer.reserve();

	uniqueIndexer.release({1u});
	uniqueIndexer.release({2u});

	auto expectedReleasedCount = 2u;
	auto releasedCount = uniqueIndexer.releasedCount();

	ASSERT_EQ(expectedReleasedCount, releasedCount);
}

TEST_F(ZtUniqueIndexerTests, reservedCountTest) {

	zt::UniqueIndexer uniqueIndexer;
	uniqueIndexer.reserve();
	uniqueIndexer.reserve();
	uniqueIndexer.reserve();
	uniqueIndexer.reserve();
	uniqueIndexer.release({0u});

	auto expectedReservedCount = 3;
	auto reservedCount = uniqueIndexer.reservedCount();

	ASSERT_EQ(expectedReservedCount, reservedCount);
}

TEST_F(ZtUniqueIndexerTests, releaseThrowException) {

	zt::UniqueIndexer uniqueIndexer;

	ASSERT_THROW(uniqueIndexer.release({ 0u }), zt::MainException);

	auto reserved = uniqueIndexer.reserve();
	uniqueIndexer.release(reserved);

	ASSERT_THROW(uniqueIndexer.release(reserved), zt::MainException);
	
}