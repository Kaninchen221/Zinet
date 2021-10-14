#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtFileFinder.h"
#include "Zinet/Core/ZtFileOpenMode.h"

#include <fstream>

class ZINET_CORE_API ZtFile
{

public:

	void Open(const ZtFileFinder::Path& FilePath, ZtFileOpenMode OpenMode);

	bool IsOpen() const;

	std::string ReadLine();

	std::string ReadAll();

	static std::ios_base::openmode ZtFileOpenModeToStdOpenMode(ZtFileOpenMode OpenMode);

protected:

	std::fstream FileStream;

};