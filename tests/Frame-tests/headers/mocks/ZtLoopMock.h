#pragma once

#include "gmock/gmock.h"

#include "Zinet/Frame/ZtLoop.h"

struct LoopMock : public zt::Loop {

	MOCK_METHOD(void, begin, (), (override));
	MOCK_METHOD(void, loop, (zt::Loop::BaseWindow& baseWindow), (override));
	MOCK_METHOD(void, update, (), (override));
	MOCK_METHOD(void, render, (), (override));
	MOCK_METHOD(void, event, (), (override));
	MOCK_METHOD(void, end, (), (override));

};