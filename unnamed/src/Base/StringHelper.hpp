#pragma once

#include <cstdarg>
#include <string>
#include <sstream>
#include <vector>

namespace me {

	class StringHelper {
	public:
		static bool StartsWith(const std::string& text, const std::string& value);
		static bool EndsWith(const std::string& text, const std::string& value);
		static std::string Trim(const std::string& text, char c);
		static std::string TrimStart(const std::string& text, char c);
		static std::string TrimEnd(const std::string& text, char c);
		static std::string Trim(const std::string& text, const std::string& chars);
		static std::string TrimStart(const std::string& text, const std::string& chars);
		static std::string TrimEnd(const std::string& text, const std::string& chars);
		static std::string ToLower(const std::string& text);
		static std::string ToUpper(const std::string& text);
		static std::string Replace(const std::string& text, char old, char _new);
		static std::string Format(const char*format, ...);
		static std::string Formatv(const char*format, va_list args);
		static std::vector<std::string> Split(const std::string& str, char c, bool removeEmpty = false);
        static std::vector<std::string> Split(const std::string& str, const std::string& chars, bool removeEmpty = false);
        static std::string FillLeft(const std::string& text, size_t length, const char* fill = " ", const char* ellipsis = "...");
        static std::string FillRight(const std::string& text, size_t length, const char* fill = " ", const char* ellipsis = "...");
        static std::string FillCenter(const std::string& text, size_t length, const char* fill = " ", const char* ellipsis = "...");
        static std::vector<std::string> LineWrap(const std::string& text, size_t length);
        
		template<class T>
		static std::string ToString(T t) {
			std::stringstream ss;
			ss << t;
			return ss.str();
		}
	};

}
