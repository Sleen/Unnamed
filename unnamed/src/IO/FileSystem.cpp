#include <algorithm>

#ifdef _WIN32
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	undef WIN32_LEAN_AND_MEAN
#	include <direct.h>
#	include <io.h>
#	include <sys/stat.h>
#else
#	include <stdio.h>
#	include <unistd.h>
#	include <dirent.h>
#	include <sys/stat.h>
#endif

#include "FileSystem.hpp"
#include "Base/StringHelper.hpp"

namespace me {

#define FN_SIZE 256

	bool FileSystem::Exists(const std::string & path)
	{
		return ExistsFile(path) || ExistsDirectory(path);
	}

	bool FileSystem::ExistsFile(const std::string & file)
	{
		FILE* f = fopen(file.c_str(), "rb");
		if (f) fclose(f);
		return f != NULL;
	}

	bool FileSystem::ExistsDirectory(const std::string & directory)
	{
#ifdef _WIN32
		struct _stat fileStat;
		return (_stat(directory.c_str(), &fileStat) == 0) && (fileStat.st_mode & _S_IFDIR);
#else
		struct stat fileStat;
		return (stat(directory.c_str(), &fileStat) == 0) && S_ISDIR(fileStat.st_mode);
#endif
	}

	bool FileSystem::Delete(const std::string & path)
	{
		return remove(path.c_str()) == 0;
	}

	bool FileSystem::IsAbsolutelyPath(const std::string& path)
	{
		if (path.length() > 0 && (path[0] == '/' || path[0] == '\\'))
			return true;
		else if (path.length() > 2 && path[1] == ':' && (path[2] == '/' || path[2] == '\\'))
			return true;
		else
			return false;
	}

	std::string FileSystem::GetFileName(const std::string & file)
	{
		std::string f = StringHelper::Replace(file, '\\', '/');
		int index = f.find_last_of('/');
		if (index == std::string::npos) {
			return f;
		}
		else {
			return f.substr(index + 1);
		}
	}

	std::string FileSystem::GetFileNameWithoutExtension(const std::string & file)
	{
		std::string f = GetFileName(file);
		int index = f.find_last_of('.');
		if (index == std::string::npos) {
			return f;
		}
		else {
			return f.substr(0, index);
		}
	}

	std::string FileSystem::GetDirectoryName(const std::string & path)
	{
		std::string f = StringHelper::Replace(path, '\\', '/');
		int index = f.find_last_of('/');
		if (index == std::string::npos) {
			return f;
		}
		else {
			return f.substr(0, (index == 0 || f[index - 1] == ':') ? index + 1 : index);
		}
	}

	std::string FileSystem::GetExtension(const std::string & file)
	{
		std::string f = GetFileName(file);
		int index = f.find_last_of('.');
		if (index == std::string::npos) {
			return std::string();
		}
		else {
			return f.substr(index);
		}
	}

	std::string FileSystem::GetStartupDirectory()
	{
#ifdef _WIN32
		static std::string startup = "";
		if (startup == "") {
			char name[FN_SIZE];
			GetModuleFileName(0, name, sizeof(name));
			startup = GetDirectoryName(name);
		}
		return startup;
#else
		return GetCurrentDir();
#endif
	}

	std::string FileSystem::GetPathRoot(const std::string& path)
	{
		std::string p = StringHelper::Replace(path, '\\', '/');
		if (path.length() > 0 && p[0] == '/') return "/";
		else if (path.length() > 2 && p[1] == ':' && p[2] == '/') return p.substr(0, 3);
		else return "";
	}

	std::string FileSystem::GetFullPath(const std::string& path)
	{
		std::string startup = GetStartupDirectory();
		std::string p = StringHelper::Replace(path, '\\', '/');

		if (p[0] == '/') {
			startup = GetPathRoot(startup);
			p = StringHelper::TrimStart(p, '/');
		}
		else if (p[1] == ':') {
			return p;
		}

		int index;
		while ((index = p.find('/')) != std::string::npos) {
			std::string d = p.substr(0, index);
			if (d == ".") {

			}
			else if (d == "..") {
				if (GetPathRoot(startup) != startup) {
					startup = startup.substr(0, startup.find_last_of('/'));
				}
			}
			else {
				startup = StringHelper::TrimEnd(startup, '/') + "/" + d;
			}
			p = p.substr(index + 1);
		}
		
		return StringHelper::TrimEnd(startup, '/') + "/" + p;
	}

	std::string FileSystem::GetCurrentDir()
	{
		char buf[FN_SIZE];
		getcwd(buf, sizeof(buf));
		return buf;
	}

	bool FileSystem::SetCurrentDir(const std::string& directory)
	{
		return chdir(directory.c_str()) == 0;
	}

	std::vector<std::string> FileSystem::GetFiles(const std::string & directory)
	{
		std::vector<std::string> list;
#ifdef _WIN32
		_chdir(directory.c_str());
		_finddata_t info;
		long result;
		if ((result = _findfirst("*", &info)) != -1) {
			do {
				if ((info.attrib & _A_SUBDIR) == 0) {
					list.push_back(StringHelper::TrimEnd(directory, '/') + "/" + info.name);
				}
			} while (_findnext(result, &info) == 0);
			_findclose(result);
		}
#else
		DIR* pDir;
		struct dirent *dmsg;
		if ((pDir = opendir(directory.c_str())) != NULL)
		{
			while ((dmsg = readdir(pDir)) != NULL)
			{
				if (dmsg->d_type != DT_DIR)
				{
					list.push_back(StringHelper::TrimEnd(directory, '/') + "/" + dmsg->d_name);
				}
			}
		}

		if (pDir != NULL)
		{
			closedir(pDir);
		}
#endif
		return list;
	}

	std::vector<std::string> FileSystem::GetDirectories(const std::string & directory)
	{
		std::vector<std::string> list;
#ifdef _WIN32
		_chdir(directory.c_str());
		_finddata_t info;
		long result;
		if ((result = _findfirst("*", &info)) != -1) {
			do {
				if ((info.attrib & _A_SUBDIR) != 0 && strcmp(info.name, ".") != 0 && strcmp(info.name, "..") != 0) {
					list.push_back(StringHelper::TrimEnd(directory, '/') + "/" + info.name);
				}
			} while (_findnext(result, &info) == 0);
			_findclose(result);
		}
#else
		DIR* pDir;
		struct dirent *dmsg;
		if ((pDir = opendir(directory.c_str())) != NULL)
		{
			while ((dmsg = readdir(pDir)) != NULL)
			{
				if (dmsg->d_type == DT_DIR && strcmp(dmsg->d_name, ".") != 0 && strcmp(dmsg->d_name, "..") != 0)
				{
					list.push_back(StringHelper::TrimEnd(directory, '/') + "/" + dmsg->d_name);
				}
			}
		}

		if (pDir != NULL)
		{
			closedir(pDir);
		}
#endif
		return list;
	}

	std::vector<std::string> FileSystem::GetFilesWithRecursion(const std::string & directory)
	{
		std::vector<std::string> list = GetFiles(directory);
		for (std::string subdir : GetDirectories(directory)) {
			auto files = GetFilesWithRecursion(subdir);
			list.insert(list.end(), files.begin(), files.end());
		}
		return list;
	}

}