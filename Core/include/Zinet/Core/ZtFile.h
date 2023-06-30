#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtFileFinder.h"
#include "Zinet/Core/ZtFileOpenMode.h"

#include <fstream>

namespace zt::core
{

	class ZINET_CORE_API File
	{

	public:

		File() = default;
		File(const File& other) = delete;
		File(File&& other) = default;

		File& operator = (const File& other) = delete;
		File& operator = (File&& other) = default;

		~File() noexcept;

		void open(const FileFinder::Path& filePath, FileOpenMode openMode);

		bool isOpen() const;

		std::string readLine();

		std::string readAll();

		static std::ios_base::openmode ToStdOpenMode(FileOpenMode openMode);

		void close();

	protected:

		std::fstream fileStream;

	};

}