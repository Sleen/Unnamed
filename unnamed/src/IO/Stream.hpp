#pragma once

#include <string>
#include "Base/Exception.hpp"
#include "Base/Event.hpp"

namespace me{

#ifdef _WIN32
#	define NEW_LINE "\r\n"
#elif defined(__MACOSX__)
#	define NEW_LINE "\n\r"
#else
#	define NEW_LINE "\n"
#endif

enum class SeekLocation{
	Begin,
	Current,
	End
};

struct IOException : Exception {};

class Stream{
protected:
	bool canWrite = false;
	bool canRead = false;
	bool canSeek = false;
	int size = 0;
	int position = 0;

	virtual int read(void *buf, int len) = 0;
	virtual int write(const void *data, int len) = 0;
	virtual int seek(int offset, SeekLocation relativeTo) = 0;

public:
	Stream() = default;
	Stream(const Stream&) = delete;
	Stream& operator=(const Stream&) = delete;

	virtual ~Stream() { Close(); }
	virtual void Close() { }
	bool CanWrite() const { return canWrite; }
	bool CanRead() const { return canRead; }
	bool CanSeek() const { return canSeek; }
	int RestSize() const { return size - position; }
	int TotalSize() const { return size; }

	int Peek(void *buf, int len);
	int Seek(int offset, SeekLocation relativeTo = SeekLocation::Current);
	int Write(const void *data, int len);
	int Read(void *buf, int len);
	std::string&& ReadString(int len);
	std::string&& ReadLine();
	std::string&& ReadToEnd();

	inline int WriteLine(const std::string& str){
		return Write(str.c_str(), str.length()) + Write((const void*)NEW_LINE, strlen(NEW_LINE));
	}

	template<typename T>
	inline int Write(const T& t){
		return Write((const void*)&t, sizeof(T)) == sizeof(T);
	}

	inline int Write(const char* str){
		return Write(str, strlen(str));
	}

	inline int Write(const std::string& str) {
		return Write(str.c_str(), str.length());
	}

	template<typename T>
	inline T Read(){
		T t;
		if (Read(&t, sizeof(T)) == sizeof(T))
			return t;
		THROW(IOException, "failed to read");
	}

	template<typename T>
	inline T Peek(){
		T t;
		if (Peek(&t, sizeof(T)) == sizeof(T))
			return t;
		THROW(IOException, "failed to peek");
	}

};

}
