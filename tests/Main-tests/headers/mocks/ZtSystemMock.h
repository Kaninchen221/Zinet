#pragma once

#include "Zinet/Main/ECRS/ZtSystemBase.h"

#include "gmock/gmock.h"

class ZtSystemMock : zt::SystemBase {

public:

	size_t scanEntity(zt::Entity& entity) override {
		return 0u;
	}

	void update(zt::Time::Microseconds timeAfterLastUpdate) override {

	}

};