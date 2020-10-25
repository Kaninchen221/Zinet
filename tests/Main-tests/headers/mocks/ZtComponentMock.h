#pragma once

#include "gmock/gmock.h"

#include "Zinet/Main/ECRS/ZtComponentBase.h"

class ZtComponentMock : public zt::ComponentBase {

public:

	ZtComponentMock() = default;
	ZtComponentMock(const ZtComponentMock& other) = default;
	ZtComponentMock(ZtComponentMock&& other) = default;
	
	ZtComponentMock& operator = (const ZtComponentMock& other) = default;
	ZtComponentMock& operator = (ZtComponentMock&& other) = default;
	
	zt::ComponentPtr getCopy() const override {
		return std::make_shared<ZtComponentMock>(*this);
	}

	~ZtComponentMock() noexcept = default;
};