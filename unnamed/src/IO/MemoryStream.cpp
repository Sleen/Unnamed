#include "MemoryStream.hpp"

namespace me {

	int MemoryStream::read(void *buf, int len) {
		int read_size = RestSize();
		if (len < read_size)
			read_size = len;
		memcpy(buf, this->buf + position, read_size);
		return read_size;
	}

	int MemoryStream::write(const void *data, int len) {
		int write_size = RestSize();
		if (len < write_size)
			write_size = len;
		memcpy(this->buf + position, data, write_size);
		return write_size;
	}

	int MemoryStream::seek(int offset, SeekLocation relativeTo) {
		int t = 0;
		switch (relativeTo)
		{
		case SeekLocation::Begin:
			t = 0;
			break;
		case SeekLocation::Current:
			t = position;
			break;
		case SeekLocation::End:
			t = size;
			break;
		}

		t += offset;
		if (t < 0)
			t = 0;
		else if (t > size)
			t = size;

		return t - position;
	}
}