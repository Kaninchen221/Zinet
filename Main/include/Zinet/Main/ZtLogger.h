#pragma once

#include "Zinet/Main/ZtMainConfig.h"

#include "spdlog/spdlog.h"

namespace zt {

	class ZINET_MAIN_API Logger {

	public:

		struct Settings {
			std::string pattern;
		};

		using LoggerT = std::shared_ptr<spdlog::logger>;

		static void Trace(const std::string& loggerName, const std::string& message);
		static void Debug(const std::string& loggerName, const std::string& message);
		static void Info(const std::string& loggerName, const std::string& message);
		static void Warn(const std::string& loggerName, const std::string& message);
		static void Error(const std::string& loggerName, const std::string& message);
		static void Critical(const std::string& loggerName, const std::string& message);

		static std::string GetLoggsFolder();
		static std::string GetLoggsFileFormat();

	private:

		static LoggerT GetOrCreateLogger(const std::string& loggerName);

		static LoggerT CreateDefaultLogger(const std::string& loggerName);

		static LoggerT GetLogger(const std::string& loggerName);

		static void AddStdoutSinkToLogger(LoggerT logger);
		static void AddFileSinkToLogger(LoggerT logger);

		template<class FuncT>
		static void CatchAndPrintExceptionToStandardOutput(FuncT function, const std::string& functionInfoMacro) noexcept;

		inline static std::string LoggsFolder = "logs/";
		inline static std::string LoggsFileFormat = ".txt";
		inline static bool Truncate = true;
	};

	template<class FuncT>
	inline void Logger::CatchAndPrintExceptionToStandardOutput(FuncT function, const std::string& functionInfoMacro) noexcept
	{
		try {
			std::invoke(function);
		}
		catch (const spdlog::spdlog_ex& spdlogEx) {
			std::cout << "Function " + functionInfoMacro + " throw exception : " + spdlogEx.what() << '\n';
		}
		catch (const std::exception& ex) {
			std::cout << "Function " + functionInfoMacro + " throw exception : " + ex.what() << '\n';
		}
		catch (...) {
			std::cout << "Uncatchable exception type from function : " << functionInfoMacro << '\n';
		}
	}

}