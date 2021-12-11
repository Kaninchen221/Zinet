#include "Zinet/Core/ZtFile.h"

namespace zt
{

	File::~File() noexcept
	{
		if (IsOpen())
		{
			Close();
		}
	}

	void File::Open(const FileFinder::Path& FilePath, FileOpenMode OpenMode)
	{
		std::ios_base::openmode StdOpenMode = ToStdOpenMode(OpenMode);
		FileStream.open(FilePath, StdOpenMode);
	}

	bool File::IsOpen() const
	{
		return FileStream.is_open();
	}

	std::string File::ReadLine()
	{
		std::string Line;
		std::getline(FileStream, Line);
		return Line;
	}

	std::string File::ReadAll()
	{
		std::string Line;
		std::getline(FileStream, Line, '\0');
		return Line;
	}

	std::ios_base::openmode File::ToStdOpenMode(FileOpenMode OpenMode)
	{
		switch (OpenMode)
		{
		case FileOpenMode::App:
			return std::ios_base::app;

		case FileOpenMode::Binary:
			return std::ios_base::binary;

		case FileOpenMode::In:
			return std::ios_base::in;

		case FileOpenMode::Out:
			return std::ios_base::out;

		case FileOpenMode::Truncate:
			return std::ios_base::trunc;

		case FileOpenMode::Ate:
			return std::ios_base::ate;

		default:
			return std::ios_base::in;
		}
	}

	void File::Close()
	{
		FileStream.close();
	}

}