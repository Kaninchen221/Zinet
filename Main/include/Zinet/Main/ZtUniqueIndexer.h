#pragma once

#include "Zinet/Main/ZtMainConfig.h"
#include "Zinet/Main/ZtIdentificator.h"

#include <vector>

namespace zt {

    class ZINET_MAIN_API UniqueIndexer {

    public:

        using Identificators = std::vector<bool>;
        using Reserved = std::true_type;
        using Released = std::false_type;

        UniqueIndexer() = default;
        UniqueIndexer(const UniqueIndexer& other) = default;
        UniqueIndexer(UniqueIndexer&& other) = default;

        UniqueIndexer& operator = (const UniqueIndexer& other) = default;
        UniqueIndexer& operator = (UniqueIndexer&& other) = default;

        ~UniqueIndexer() = default;

        Identificator reserve();

        void release(const zt::Identificator& identificatorToRelease);

        size_t releasedCount() const noexcept;

        size_t reservedCount() const noexcept;

    private:

        Identificator reserveNewIdentificator();
        Identificator reserveReleasedIdentificator();

        Identificators identificators;
        size_t releasedIdentificators = 0u;

    };

}
