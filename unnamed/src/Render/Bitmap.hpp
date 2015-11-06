#pragma once

#include <string>

#include "GL.hpp"
#include "IO/Stream.hpp"

namespace me {

	class Texture;

	class Bitmap {
	private:
		GLubyte *data = NULL;
		unsigned width, height;

		void setColor(unsigned x, unsigned y, int color);
		void setup(GLuint textureID, int left, int top, int width, int height);

	public:
		Bitmap(unsigned width, unsigned height, int color = 0);
		Bitmap(const Bitmap& bmp);
		Bitmap(unsigned width, unsigned height, unsigned checkSize, int c1, int c2);
		Bitmap(const std::string& file);
		Bitmap(Stream& stream, const std::string& format = ".png");
		Bitmap(GLuint textureID, int left, int top, int width, int height);
		Bitmap(const Texture& texture, int left, int top, int width, int height);
		Bitmap(const Texture& texture);
		bool Save(const std::string& file);
		bool Save(const std::string& file, const std::string& format);	// format can be ".bmp" or ".png"

		void FlipX();
		void FlipY();
		void FlipXY();

		Bitmap() { }
		~Bitmap() { if (data) delete[] data; }
		GLubyte *GetData() { return data; }
		GLubyte *GetData() const { return data; }
		unsigned GetWidth() const { return width; }
		unsigned GetHeight() const { return height; }
	};

}
