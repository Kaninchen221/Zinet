#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtFileFinder.h"
#include "Zinet/Core/ZtFileOpenMode.h"

#include <fstream>

namespace zt
{

	class ZINET_CORE_API File
	{

	public:

		File() = default;
		File(const File& Other) = default;
		File(File&& Other) = default;

		File& operator = (const File& Other) = default;
		File& operator = (File&& Other) = default;

		~File() noexcept;

		void Open(const FileFinder::Path& FilePath, FileOpenMode OpenMode);

		bool IsOpen() const;

		std::string ReadLine();

		std::string ReadAll();

		static std::ios_base::openmode ToStdOpenMode(FileOpenMode OpenMode);

		void Close();

	protected:

		std::fstream FileStream;

	};

}