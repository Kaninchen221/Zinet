#include "Zinet/Core/ZtFile.h"

void ZtFile::Open(const ZtFileFinder::Path& FilePath, ZtFileOpenMode OpenMode)
{
	std::ios_base::openmode StdOpenMode = ZtFileOpenModeToStdOpenMode(OpenMode);
	FileStream.open(FilePath, StdOpenMode);
}

bool ZtFile::IsOpen() const
{
	return FileStream.is_open();
}

std::string ZtFile::ReadLine()
{
	std::string Line;
	std::getline(FileStream, Line);
	return Line;
}

std::string ZtFile::ReadAll()
{
	std::string Line;
	std::getline(FileStream, Line, '\0');
	return Line;
}

std::ios_base::openmode ZtFile::ZtFileOpenModeToStdOpenMode(ZtFileOpenMode OpenMode)
{
	switch (OpenMode)
	{
	case ZtFileOpenMode::App:
		return std::ios_base::app;

	case ZtFileOpenMode::Binary:
		return std::ios_base::binary;

	case ZtFileOpenMode::In:
		return std::ios_base::in;

	case ZtFileOpenMode::Out:
		return std::ios_base::out;

	case ZtFileOpenMode::Truncate:
		return std::ios_base::trunc;

	case ZtFileOpenMode::Ate:
		return std::ios_base::ate;

	default:
		return std::ios_base::in;
	}
}
