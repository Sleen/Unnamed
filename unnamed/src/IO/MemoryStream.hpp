#pragma once

#include "Stream.hpp"

namespace me {

	class MemoryStream : public Stream {
	protected:
		char *buf = nullptr;
		bool toFree = false;

		virtual int read(void *buf, int len) override;
		virtual int write(const void *data, int len) override;
		virtual int seek(int offset, SeekLocation relativeTo) override;

	public:
		MemoryStream(void* buf, int size) {
			this->buf = (char*)buf;
			this->size = size;
			canRead = true;
			canWrite = true;
			canSeek = true;
		}

		MemoryStream(const void* buf, int size) {
			this->buf = const_cast<char*>((const char*)buf);
			this->size = size;
			canRead = true;
			canWrite = false;
			canSeek = true;
		}

		MemoryStream(int size) {
			this->size = size;
			buf = new char[size];
			toFree = true;
			canRead = true;
			canWrite = true;
			canSeek = true;
		}

		MemoryStream(Stream& s) {
			size = s.TotalSize();
			buf = new char[size];
			s.Read(buf, size);
			toFree = true;
			canRead = true;
			canWrite = true;
			canSeek = true;
		}

		MemoryStream(const MemoryStream&) = delete;
		MemoryStream& operator=(const MemoryStream&) = delete;

		MemoryStream(MemoryStream&& ms) {
			this->~MemoryStream();

			memcpy(this, &ms, sizeof(MemoryStream));
			memset(&ms, 0, sizeof(MemoryStream));
		}

		MemoryStream& operator=(MemoryStream&& ms) {
			if (&ms == this)
				return *this;

			this->~MemoryStream();

			memcpy(this, &ms, sizeof(MemoryStream));
			memset(&ms, 0, sizeof(MemoryStream));

			return *this;
		}

		char* GetBuffer() {
			return buf;
		}

		char* GetCurrentBuffer() {
			return buf + position;
		}

		virtual void Close() {
			if (toFree && buf) {
				delete[] buf;
				buf = nullptr;
			}
		}

		virtual ~MemoryStream() {
			Close();
		}
	};

}
