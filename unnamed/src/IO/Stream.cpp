#include "Stream.hpp"

namespace me {

	int Stream::Peek(void *buf, int len) {
		if (!canRead)
			THROW(IOException, "Peek() called on a un-readable stream!");

		if (!canSeek)
			THROW(IOException, "Peek() called on a un-seekable stream!");

		int read_size = Read(buf, len);
		Seek(-read_size);

		return read_size;
	}

	int Stream::Seek(int offset, SeekLocation relativeTo) {
		if (!canSeek)
			THROW(IOException, "Seek() called on a un-seekable stream!");

		int real_offset = seek(offset, relativeTo);
		position += real_offset;

		return real_offset;
	}

	int Stream::Write(const void *data, int len) {
		if (!canWrite)
			THROW(IOException, "Write() called on a un-writable stream!");

		int s = write(data, len);

		position += s;

		if (size < position) {
			size = position;
		}

		return s;
	}

	int Stream::Read(void *buf, int len) {
		if (!canRead)
			THROW(IOException, "Read() called on a un-readable stream!");

		int s = read(buf, len);

		if (canSeek) {
			position += s;
		}
		else {
			size -= s;
		}

		return s;
	}

	std::string&& Stream::ReadString(int len) {
		char* buf = new char[len + 1];
		buf[Read(buf, len)] = 0;
		std::string* ret = new std::string(buf);
		delete[] buf;
		return std::move(*ret);
	}

	std::string&& Stream::ReadLine() {
		std::string& s = *(new std::string);
		int len = 0;
		char ch;
		while (Read(&ch, 1) == 1 && ch != '\n') {
			s += ch;
			len++;
		}
		if (len >= 0 && s[len - 1] == '\r')
			s = s.substr(0, len - 1);
		return std::move(s);
	}

	std::string&& Stream::ReadToEnd() {
		if (!canRead)
			THROW(IOException, "ReadToEnd() called on a un-readable stream!");

		if (RestSize() < 0)
			THROW(IOException, "ReadToEnd() called on a un-measurable stream!");

		char* buf = new char[RestSize() + 1];
		char* read_buf = buf;

		while (RestSize() > 0)
		{
			int len = Read(read_buf, RestSize());
			if(len == 0)
				THROW(IOException, "error occurs in ReadToEnd()!");
			read_buf += len;
		}

		read_buf[0] = 0;

		std::string* s = new std::string(buf);
		delete[] buf;

		return std::move(*s);
	}
}
