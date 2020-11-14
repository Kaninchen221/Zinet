#include "Zinet/Main/ZtUniqueIndexer.h"

#include "Zinet/Main/ZtMainException.h"

namespace zt {

	Identificator UniqueIndexer::reserve()
	{
		if (releasedIdentificators == 0u) {
			return reserveNewIdentificator();
		}
		else {
			return reserveReleasedIdentificator();
		}

	}

	void UniqueIndexer::release(const zt::Identificator& identificatorToRelease)
	{
		auto identificatorNumberToRelease = identificatorToRelease.getNumber();
		if (identificatorNumberToRelease >= identificators.size()) {
			throw MainException("Trying release not existing identificator (out of range)");
		}

		auto identificator = identificators.at(identificatorNumberToRelease);
		if (identificator == Reserved()) {
			++releasedIdentificators;
			identificator = Released();
		}
		else {
			auto identificatorNumberAsString = std::to_string(identificatorNumberToRelease);
			throw MainException("Trying release already released identificator with number : " + identificatorNumberAsString);
		}
	}

	size_t UniqueIndexer::releasedCount() const noexcept
	{
		return releasedIdentificators;
	}

	size_t UniqueIndexer::reservedCount() const noexcept
	{
		return identificators.size() - releasedCount();
	}

	Identificator UniqueIndexer::reserveNewIdentificator()
	{
		size_t identificatorNumber = identificators.size();
		identificators.push_back(Reserved());
		auto identificator = Identificator(identificatorNumber);
		return identificator;
	}

	Identificator UniqueIndexer::reserveReleasedIdentificator()
	{
		size_t identificatorNumber = 0u;
		for (auto& identificator : identificators) {
			if (identificator == Released()) {
				identificator = Reserved();
				--releasedIdentificators;
				return identificatorNumber;
			}
			++identificatorNumber;
		}

		throw MainException("Trying reserve released identificator when all identificators are reserved");
	}

}