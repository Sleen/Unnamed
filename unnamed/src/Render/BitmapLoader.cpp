#include "BitmapLoader.hpp"
#include "IO/Stream.hpp"
#include "IO/MemoryStream.hpp"
#include "IO/FileSystem.hpp"
#include "IO/FileStream.hpp"
#include "Base/System.hpp"
#include "Base/StringHelper.hpp"

namespace me {

	class BMPLoader : public BitmapLoader {
	public:
		bool Load(Stream& stream, unsigned& width, unsigned& height, GLubyte*& data);
		bool Save(const std::string& file, unsigned width, unsigned height, GLubyte* data);
		static BMPLoader* GetInstance() {
			static BMPLoader loader;
			return &loader;
		}
	};

	BitmapLoader* BitmapLoader::GetLoader(const std::string& file) {
		//DEBUG_LOG("load image \"%s\" ...\n", file.c_str());

		std::string ex = StringHelper::ToLower(file.substr(file.length() - 4));
		if (ex == ".bmp") {
			return BMPLoader::GetInstance();
		}

		THROW(FileFormatException, "\"" + file + "\"  unsupported image format");

		return NULL;
	}

	bool BitmapLoader::Load(const std::string& file, unsigned& width, unsigned& height, GLubyte*& data) {
		auto fs = FileStream(file);
		return Load(fs, width, height, data);
	}

	bool BMPLoader::Load(Stream& stream, unsigned& width, unsigned& height, GLubyte*& data) {
		if (stream.RestSize() > 0) {
			int64_t t = System::GetMicroSecond();
			BITMAPFILEHEADER fh;
			BITMAPINFOHEADER ih;
			fh = stream.Read<decltype(fh)>();
			ih = stream.Read<decltype(ih)>();

			if (ih.biBitCount == 24 && ih.biCompression == 0) {
				width = ih.biWidth;
				height = abs(ih.biHeight);
				int padding = ih.biSizeImage / height - width * 3;
				int padding_buf;
				GLubyte *d;
				if (ih.biHeight < 0) {
					data = new GLubyte[width*height * 4];
					for (unsigned int i = 0; i < height; i++) {
						for (unsigned int j = 0; j < width; j++)
						{
							d = data + (i*width + j) * 4;
							GLubyte c[3];
							stream.Read(c, 3);
							d[0] = c[2];
							d[1] = c[1];
							d[2] = c[0];
							d[3] = 255;
						}
						if (padding > 0) {
							stream.Read(&padding_buf, padding);
						}
					}
				}
				else {
					data = new GLubyte[width*height * 4];
					for (int i = height - 1; i >= 0; i--) {
						for (unsigned int j = 0; j < width; j++)
						{
							d = data + (i*width + j) * 4;
							GLubyte c[3];
							stream.Read(c, 3);
							d[0] = c[2];
							d[1] = c[1];
							d[2] = c[0];
							d[3] = 255;
						}
						if (padding > 0) {
							stream.Read(&padding_buf, padding);
						}
					}
				}
				//DEBUG_LOG("load success, size: %d x %d, time consumed: %.3f ms\n", width, height, (System::GetMicroSecond() - t) / 1000.0f);
				return true;
			}
			else {
				//DEBUG_LOG("load failed from stream, only 24-bit non-compression BMP files are supported\n");
			}
		}
		else {
			//DEBUG_LOG("load failed from stream, too short\n");
		}
		return false;
	}

	bool BMPLoader::Save(const std::string& file, unsigned width, unsigned height, GLubyte* data) {
		FILE *f = fopen(file.c_str(), "wb");
		if (f) {
			BITMAPFILEHEADER fh;
			BITMAPINFOHEADER ih;
			memset(&fh, 0, sizeof(fh));
			memset(&ih, 0, sizeof(ih));
			fh.bfType = 0x4D42;
			fh.bfOffBits = 54;
			fh.bfSize = 1;
			ih.biSize = 40;
			ih.biWidth = width;
			ih.biHeight = height;
			ih.biPlanes = 1;
			ih.biBitCount = 24;
			int line = width * 3;
			int padding = 0;
			char padding_char = 0;
			if (line % 4 != 0) {
				padding = 4 - line % 4;
				line += padding;
			}
			ih.biSizeImage = line * height;
			fwrite(&fh, sizeof(fh), 1, f);
			fwrite(&ih, sizeof(ih), 1, f);
			for (int i = height - 1; i >= 0; i--) {
				for (int j = 0; j < width; j++)
				{
					GLubyte *d = data + (i*width + j) * 4;
					GLubyte c[3];
					c[0] = d[2];
					c[1] = d[1];
					c[2] = d[0];
					fwrite(c, 3, 1, f);
				}
				if (padding > 0) {
					fwrite(&padding_char, 1, padding, f);
				}
			}
			fclose(f);
			return true;
		}
		else {
			//DEBUG_LOG("\"%s\"  save failed\n", file.c_str());
		}

		return false;
	}

}
