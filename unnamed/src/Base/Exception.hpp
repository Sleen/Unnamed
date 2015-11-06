#pragma once

#include <string>
#include "StringHelper.hpp"

namespace me {

#define THROW(name, msg) \
do { \
    name ex; \
    ex.What() = msg; \
    ex.Where() = std::string(__FILE__ " (" + me::StringHelper::ToString(__LINE__) + ")"); \
    throw ex; \
} while(false)

	class Exception {
	protected:
		std::string what;
		std::string where;

	public:
		const std::string& What() const {
			return what;
		}

		const std::string& Where() const {
			return where;
		}

		std::string& What() {
			return what;
		}

		std::string& Where() {
			return where;
		}
	};

	class FormatException : public Exception {};
	class FileFormatException : public Exception {};

}
