#pragma once

#include <string>
#include <vector>

namespace me {

	class FileSystem {
	public:
		static bool Exists(const std::string& path);
		static bool ExistsFile(const std::string& file);
		static bool ExistsDirectory(const std::string& directory);
		static bool Delete(const std::string& path);
		static bool IsAbsolutelyPath(const std::string& path);
		static std::string GetFileName(const std::string& file);
		static std::string GetFileNameWithoutExtension(const std::string& file);
		static std::string GetDirectoryName(const std::string& path);
		static std::string GetExtension(const std::string& file);
		static std::string GetStartupDirectory();
		static std::string GetPathRoot(const std::string& path);
		static std::string GetFullPath(const std::string& path);
		static std::string GetCurrentDir();
		static bool SetCurrentDir(const std::string& directory);
		static std::vector<std::string> GetFiles(const std::string& directory);
		static std::vector<std::string> GetDirectories(const std::string& directory);
		static std::vector<std::string> GetFilesWithRecursion(const std::string& directory);
	};

}