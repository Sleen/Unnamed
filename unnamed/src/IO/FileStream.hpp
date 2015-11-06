#pragma once

#include "Stream.hpp"

namespace me {

	enum class FileAccess {
		ReadOnly,		// r
		WriteOnly,		// w
		AppendOnly,		// a
		ReadWrite,		// r+
		Create,			// w
		CreateReadWrite,// w+
		ReadAppend		// a+
	};

	struct FileNotFoundException : Exception {};

	class FileStream : public Stream {
	protected:
		FILE* file = nullptr;
		FileAccess access = FileAccess::ReadOnly;

		virtual int read(void *buf, int len) override;
		virtual int write(const void *data, int len) override;
		virtual int seek(int offset, SeekLocation relativeTo) override;

	public:
		FileStream() {}
		FileStream(const FileStream&) = delete;
		FileStream& operator=(const FileStream&) = delete;

		FileStream(const std::string& file, FileAccess access = FileAccess::ReadOnly);
		FileStream(FileStream&& fs);
		//FileStream(FileStream&&) = default;		// not supported on visual studio 2013

		FileStream& operator=(FileStream&& fs);

		virtual void Close() override;

		virtual ~FileStream() override {
			Close();
		}

	};

}
