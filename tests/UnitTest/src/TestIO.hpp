#pragma once

#include <cstdint>

#include "UnitTest.hpp"
#include "IO/FileStream.hpp"
#include "IO/MemoryStream.hpp"
#include "IO/FileSystem.hpp"

using namespace me;

BEGIN_TESTS(IO)

#ifdef _WIN32
#	define TEST_FILE "test.txt"
#elif defined(__ANDROID__)
#	define TEST_FILE "/sdcard/test.txt"
#else
#	define TEST_FILE "test.txt"
#endif

TEST(FileStream) {
	std::string file = TEST_FILE;

	FileStream stream(file, FileAccess::Create);
	CHECK(FileSystem::ExistsFile(file));
	CHECK(!FileSystem::ExistsDirectory(file));
	CHECK(!FileSystem::ExistsFile(file+"1"));
	CHECK(!stream.CanRead());
	CHECK(stream.CanSeek());
	CHECK(stream.CanWrite());
	stream.WriteLine("hello");
	stream.Write("world");
	stream.Close();
	stream = FileStream(file);
	CHECK(stream.ReadToEnd() == "hello" NEW_LINE "world");
	stream.Close();
	CHECK(FileSystem::Delete(file));
}

TEST(MemoryStream) {
	int32_t a = 0;
	MemoryStream stream(&a, 4);
	CHECK(stream.CanRead());
	CHECK(stream.CanSeek());
	CHECK(stream.CanWrite());
	stream.Write(1234567);
	CHECK(a == 1234567);
	CHECK(stream.Seek(-4) == -4);
	CHECK(stream.Read<int>() == a);
	a = 0x74736574;
	stream.Seek(0, SeekLocation::Begin);
	CHECK(stream.ReadToEnd() == "test");
	stream.Close();
}

TEST(FileSystem) {
	std::string file = TEST_FILE;

	if (FileSystem::ExistsFile(file))
		FileSystem::Delete(file);

	CHECK(!FileSystem::ExistsFile(file));
	FileStream(file, FileAccess::Create);
	CHECK(FileSystem::ExistsFile(file));
	CHECK(FileSystem::Exists(file));
	CHECK(!FileSystem::ExistsDirectory(file));
	CHECK(FileSystem::Delete(file));
	CHECK(!FileSystem::ExistsFile(file));
	CHECK(FileSystem::GetFileName("C:\\test\\test.txt") == "test.txt");
	CHECK(FileSystem::GetFileName("C:/test/test.txt") == "test.txt");
	CHECK(FileSystem::GetFileNameWithoutExtension("C:\\test\\test.txt") == "test");
	CHECK(FileSystem::GetExtension("C:\\test\\test.txt") == ".txt");
	CHECK(FileSystem::GetDirectoryName("C:\\test\\test.txt") == "C:/test");
	CHECK(FileSystem::GetDirectoryName("C:\\test\\") == "C:/test");
	CHECK(FileSystem::GetDirectoryName("C:\\test") == "C:/");
	CHECK(FileSystem::IsAbsolutelyPath("C:\\"));
	CHECK(FileSystem::IsAbsolutelyPath("/"));
	CHECK(!FileSystem::IsAbsolutelyPath("a.txt"));
	CHECK(FileSystem::GetStartupDirectory() != "");
	CHECK(FileSystem::GetPathRoot("C:\\a.txt") == "C:/");
	CHECK(FileSystem::GetPathRoot("D:\\a\\b.txt") == "D:/");
	CHECK(FileSystem::GetPathRoot("/a.txt") == "/");
	CHECK(FileSystem::GetFullPath("C:\\a.txt") == "C:/a.txt");
	CHECK(FileSystem::GetFullPath("a.txt") == StringHelper::TrimEnd(FileSystem::GetStartupDirectory(), '/') + "/a.txt");
	CHECK(FileSystem::GetFullPath("test/") == StringHelper::TrimEnd(FileSystem::GetStartupDirectory(), '/') + "/test/");
	CHECK(FileSystem::GetFullPath("a/../a.txt") == StringHelper::TrimEnd(FileSystem::GetStartupDirectory(), '/') + "/a.txt");
	CHECK(FileSystem::GetFullPath("./a.txt") == StringHelper::TrimEnd(FileSystem::GetStartupDirectory(), '/') + "/a.txt");
	CHECK(FileSystem::GetFullPath("/a.txt") == FileSystem::GetPathRoot(FileSystem::GetStartupDirectory()) + "a.txt");
}

END_TESTS()
