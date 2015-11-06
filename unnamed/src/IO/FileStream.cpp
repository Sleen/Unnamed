#include "FileStream.hpp"

#include <sys/stat.h>

namespace me {

	int FileStream::read(void *buf, int len) {
		return fread(buf, 1, len, file);
	}

	int FileStream::write(const void *data, int len) {
		if (access != FileAccess::ReadAppend || (position == size || Seek(size - position)))
			return fwrite(data, 1, len, file);
		return 0;
	}

	int FileStream::seek(int offset, SeekLocation relativeTo) {
		int t = 0;
		int s = SEEK_CUR;

		switch (relativeTo)
		{
		case SeekLocation::Begin:
			t = 0;
			s = SEEK_SET;
			break;
		case SeekLocation::Current:
			t = position;
			s = SEEK_CUR;
			break;
		case SeekLocation::End:
			t = size;
			s = SEEK_END;
			break;
		}

		t += offset;
		if (t < 0)
			t = 0;
		else if (t > size)
			t = size;

		if (fseek(file, offset, s) != 0)
			t = position;

		return t - position;
	}

	FileStream::FileStream(const std::string& file, FileAccess access) {
		static const char* ms[7] = { "rb", "wb", "ab", "rb+", "wb", "wb+", "ab+" };

		this->file = fopen(file.c_str(), ms[(int)access]);
		if (this->file == nullptr) {
			if (access == FileAccess::Create || access == FileAccess::CreateReadWrite) {
				THROW(IOException, "can not create file '" + file + "'.");
			}
			else {
				THROW(FileNotFoundException, "file '" + file + "' not found.");
			}
		}

		canRead = true;
		canWrite = true;
		canSeek = true;

#ifdef _WIN32
#	define stat _stat
#endif
		struct stat st;
		if (stat(file.c_str(), &st))
			size = 0;
		else
			size = st.st_size;

		switch (access)
		{
		case FileAccess::ReadOnly:
			canWrite = false;
			break;
		case FileAccess::WriteOnly:
			canRead = false;
			break;
		case FileAccess::AppendOnly:
			canRead = false;
			canSeek = false;
			position = size;
			break;
		case FileAccess::ReadWrite:
			break;
		case FileAccess::Create:
			canRead = false;
			break;
		case FileAccess::CreateReadWrite:
			break;
		case FileAccess::ReadAppend:
			position = 0;
			break;
		default:
			break;
		}

	}

	FileStream::FileStream(FileStream&& fs) {
		this->~FileStream();

		memcpy(this, &fs, sizeof(FileStream));
		memset(&fs, 0, sizeof(FileStream));
	}

	FileStream& FileStream::operator=(FileStream&& fs) {
		if (&fs == this)
			return *this;

		this->~FileStream();

		memcpy(this, &fs, sizeof(FileStream));
		memset(&fs, 0, sizeof(FileStream));

		return *this;
	}

	void FileStream::Close() {
		if (file != nullptr) {
			fclose(file);
			file = nullptr;
		}
	}

}