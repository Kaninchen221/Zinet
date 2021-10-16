#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtFileFinder.h"
#include "Zinet/Core/ZtFileOpenMode.h"

#include <fstream>

class ZINET_CORE_API ZtFile
{

public:

	ZtFile() = default;
	ZtFile(const ZtFile& Other) = default;
	ZtFile(ZtFile&& Other) = default;

	ZtFile& operator = (const ZtFile& Other) = default;
	ZtFile& operator = (ZtFile&& Other) = default;

	~ZtFile() noexcept;

	void Open(const ZtFileFinder::Path& FilePath, ZtFileOpenMode OpenMode);

	bool IsOpen() const;

	std::string ReadLine();

	std::string ReadAll();

	static std::ios_base::openmode ZtFileOpenModeToStdOpenMode(ZtFileOpenMode OpenMode);

	void Close();

protected:

	std::fstream FileStream;

};