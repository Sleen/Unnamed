#pragma once

#include <cstdarg>
#include <string>
#include <list>

#include "StringHelper.hpp"

namespace me {
	// Verbose, Info, Debug, Warning, Error, Fatal
	class Log {
	private:
		enum LogPriority {
			Verbose,
			Debug,
			Info,
			Warn,
			Error,
			Fatal
		};

		struct LogRecord
		{
			int timestamp;
			LogPriority priority;
			std::string text;
		};

		std::list<LogRecord> records;

		static void log(LogPriority priority, const std::string& text);

	public:
		static void V(const std::string& text) { log(Verbose, text); }
		static void I(const std::string& text) { log(Info, text); }
		static void D(const std::string& text) { log(Debug, text); }
		static void W(const std::string& text) { log(Warn, text); }
		static void E(const std::string& text) { log(Error, text); }
		static void F(const std::string& text) { log(Fatal, text); }

		static void V(const char* format, ...) { 
			va_list args;
			va_start(args, format);
			V(StringHelper::Formatv(format, args));
			va_end(args);
		}

		static void I(const char* format, ...) {
			va_list args;
			va_start(args, format);
			I(StringHelper::Formatv(format, args));
			va_end(args);
		}

		static void D(const char* format, ...) {
			va_list args;
			va_start(args, format);
			D(StringHelper::Formatv(format, args));
			va_end(args);
		}

		static void W(const char* format, ...) {
			va_list args;
			va_start(args, format);
			W(StringHelper::Formatv(format, args));
			va_end(args);
		}

		static void E(const char* format, ...) {
			va_list args;
			va_start(args, format);
			E(StringHelper::Formatv(format, args));
			va_end(args);
		}

		static void F(const char* format, ...) {
			va_list args;
			va_start(args, format);
			F(StringHelper::Formatv(format, args));
			va_end(args);
		}

	};

}
