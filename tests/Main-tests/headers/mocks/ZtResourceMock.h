#pragma once

#include "gmock/gmock.h"

#include "Zinet/Main/ECRS/ZtResourceBase.h"

class ZtResourceMock : public zt::ResourceBase {

public:

	ZtResourceMock() = default;
	ZtResourceMock(const ZtResourceMock & other) = default;
	ZtResourceMock(ZtResourceMock && other) = default;

	virtual ZtResourceMock& operator = (const ZtResourceMock & other) = default;
	virtual ZtResourceMock& operator = (ZtResourceMock && other) = default;

	zt::ResourcePtr getCopy() const override {
		return std::make_shared<ZtResourceMock>(*this);
	}

	virtual ~ZtResourceMock() noexcept = default;
};