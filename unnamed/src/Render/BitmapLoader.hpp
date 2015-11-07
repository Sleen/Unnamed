#pragma once

#include <string>

#include "GL.hpp"

#ifndef _WIN32
typedef struct{
	uint16_t	bfType;
	uint32_t	bfSize;
	uint16_t	bfReserved1;
	uint16_t	bfReserved2;
	uint32_t	bfOffBits;
} BITMAPFILEHEADER;

typedef struct{
	uint32_t	biSize;
	uint32_t	biWidth;
	int32_t     biHeight;
	uint16_t	biPlanes;
	uint16_t	biBitCount;
	uint32_t	biCompression;
	uint32_t	biSizeImage;
	uint32_t	biXPelsPerMeter;
	uint32_t	biYPelsPerMeter;
	uint32_t	biClrUsed;
	uint32_t	biClrImportant;
} BITMAPINFOHEADER;
#endif

namespace me {

	class Stream;

	class BitmapLoader {
	public:
		virtual bool Load(const std::string& file, unsigned& width, unsigned& height, GLubyte*& data);
		virtual bool Load(Stream& stream, unsigned& width, unsigned& height, GLubyte*& data) = 0;
		virtual bool Save(const std::string& file, unsigned width, unsigned height, GLubyte* data) = 0;
		static BitmapLoader*  GetLoader(const std::string& file);
	};

}
