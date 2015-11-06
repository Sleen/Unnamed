#include "Bitmap.hpp"

#include "Color.hpp"
#include "BitmapLoader.hpp"
#include "Texture.hpp"

#include "Base/Exception.hpp"

namespace me {

	void Bitmap::setColor(unsigned x, unsigned y, int color) {
		GLubyte *d = data + (y*width + x) * 4;
		d[0] = R(color);
		d[1] = G(color);
		d[2] = B(color);
		d[3] = A(color);
	}

	Bitmap::Bitmap(unsigned width, unsigned height, int color) {
		data = new GLubyte[width*height * 4];
		this->width = width;
		this->height = height;
		if (color == Color::Transparent) {
			memset(data, 0, width*height * 4);
			return;
		}
		for (unsigned i = 0; i < width; i++)
			for (unsigned j = 0; j < height; j++)
				setColor(i, j, color);
	}

	Bitmap::Bitmap(const Bitmap& bmp) {
		width = bmp.width;
		height = bmp.height;
		unsigned size = width*height * 4;
		data = new GLubyte[size];
		memcpy(data, bmp.data, size);
	}

	Bitmap::Bitmap(unsigned width, unsigned height, unsigned checkSize, int c1, int c2) {
		this->width = width;
		this->height = height;
		data = new GLubyte[width*height * 4];

		for (unsigned i = 0; i < width; i++)
			for (unsigned j = 0; j < height; j++)
			{
				if ((i / checkSize + j / checkSize) % 2)
					setColor(i, j, c2);
				else
					setColor(i, j, c1);
			}
	}

	Bitmap::Bitmap(const std::string& file) {
		BitmapLoader::GetLoader(file)->Load(file, width, height, data);
	}

	Bitmap::Bitmap(Stream& stream, const std::string& format) {
		//ASSERT(stream.Size() != 0, "tried to construct a bitmap with an empty stream !");
		BitmapLoader::GetLoader(format)->Load(stream, width, height, data);
	}

	void Bitmap::setup(GLuint textureID, int left, int top, int width, int height) {
		this->width = width;
		this->height = height;
		unsigned size = width*height * 4;
		data = new GLubyte[size];

		GLuint fbo;
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
		glReadPixels(left, top, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDeleteFramebuffers(1, &fbo);
	}

	Bitmap::Bitmap(GLuint textureID, int left, int top, int width, int height) {
		setup(textureID, left, top, width, height);
	}

	Bitmap::Bitmap(const Texture& texture, int left, int top, int width, int height) {
		setup(texture.GetID(), 0, 0, width, height);
	}

	Bitmap::Bitmap(const Texture& texture) {
		setup(texture.GetID(), 0, 0, texture.GetWidth(), texture.GetHeight());
	}

	bool Bitmap::Save(const std::string& file) {
		BitmapLoader::GetLoader(file)->Save(file, width, height, data);
		return false;
	}

	// format can be ".bmp" or ".png"
	bool Bitmap::Save(const std::string& file, const std::string& format) {
		BitmapLoader::GetLoader(format)->Save(file, width, height, data);
		return false;
	}

	void Bitmap::FlipX() {
		int* d = (int*)data;
		int temp;
		for (int i = 0; i < width / 2; i++) {
			int j = width - i - 1;
			for (int k = 0; k < height; k++) {
				temp = d[k*width + i];
				d[k*width + i] = d[k*width + j];
				d[k*width + j] = temp;
			}
		}
	}

	void Bitmap::FlipY() {
		int* d = (int*)data;
		int temp;
		for (int i = 0; i < height / 2; i++) {
			int j = height - i - 1;
			int* a = d + (i*width);
			int* b = d + (j*width);
			for (int k = 0; k < width; k++) {
				temp = a[k];
				a[k] = b[k];
				b[k] = temp;
			}
		}
	}

	void Bitmap::FlipXY() {
		FlipX();
		FlipY();
	}

}
