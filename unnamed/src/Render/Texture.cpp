#include "Texture.hpp"
#include "Bitmap.hpp"
#include "Base/System.hpp"

namespace me {

	int Texture::current_id = 0;

	Texture::Texture(const Bitmap& bmp) {
		glGenTextures(1, &id);
		//glBindTexture(GL_TEXTURE_2D, id);
		Bind();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmp.GetWidth(), bmp.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bmp.GetData());
		this->width = bmp.GetWidth();
		this->height = bmp.GetHeight();
	}

	Texture::Texture(const std::string& file) {
		glGenTextures(1, &id);
		//glBindTexture(GL_TEXTURE_2D, id);
		Bind();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		Bitmap bmp(file);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmp.GetWidth(), bmp.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bmp.GetData());
		this->width = bmp.GetWidth();
		this->height = bmp.GetHeight();
	}

	Texture::Texture(int width, int height) {
		this->width = width;
		this->height = height;
		glGenTextures(1, &id);
		Bind();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}

	Texture::Texture(int width, int height, int* data) {
		this->width = width;
		this->height = height;
		glGenTextures(1, &id);
		Bind();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	std::shared_ptr<Bitmap> Texture::SaveToBitmap() const {
		return std::make_shared<Bitmap>(id, 0, 0, width, height);
	}

	Texture * Texture::Load(const std::string & res)
	{
		return NULL;
	}

	void Texture::Delete() {
		if (id) {
			Log::D("delete: %d", id);
			glDeleteTextures(1, &id);
			id = 0;
		}
	}

	void RenderableTexture::Setup(bool useStencilBuffer) {
		glGenFramebuffers(1, &fbo);
		if (fbo == 0) {
			Log::E("failed to glGenFramebuffers\n");
			return;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->GetID(), 0);

		if (useStencilBuffer) {
			GLuint depth_stencil_rb;
			glGenRenderbuffers(1, &depth_stencil_rb);
			glBindRenderbuffer(GL_RENDERBUFFER, depth_stencil_rb);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, tex->GetWidth(), tex->GetHeight());
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_stencil_rb);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth_stencil_rb);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}

		auto result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (result != GL_FRAMEBUFFER_COMPLETE) {
			/*
			#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
			#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
			#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
			#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
			#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS 0x8CDA
			#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
			#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
			#define GL_FRAMEBUFFER_UNSUPPORTED 0x8CDD
			*/
			const char* error_msg[] = {
				"GL_FRAMEBUFFER_COMPLETE",
				"GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT",
				"GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT",
				"UNKNOWN",
				"GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS",
				"GL_FRAMEBUFFER_INCOMPLETE_FORMATS",
				"GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER",
				"GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER",
				"GL_FRAMEBUFFER_UNSUPPORTED"
			};

			Log::E("FBO error: %s\n", error_msg[result - 0x8CD5]);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		transform = std::make_shared<Transform>();
		Begin();
		Viewport(0, 0, tex->GetWidth(), tex->GetHeight());
		MatrixMode(PROJECTION_MATRIX);
		LoadIdentity();
		Ortho(0, tex->GetWidth(), 0, tex->GetHeight(), -1, 1);
		MatrixMode(MODELVIEW_MATRIX);
		LoadIdentity();
		End();
	}

	RenderableTexture::RenderableTexture(int width, int height, bool useStencilBuffer) {
		tex = new Texture(Bitmap(width, height));
		del = true;
		Setup(useStencilBuffer);
	}

	RenderableTexture::RenderableTexture(Texture* tex, bool useStencilBuffer) {
		this->tex = tex;
		Setup(useStencilBuffer);
	}

	void RenderableTexture::Begin() {
		//cout << "begin: " << fbo << endl;
		//int64_t t1 = GetMicroSecond();
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		//int64_t t2 = GetMicroSecond();
		savedState = SaveState();
		LoadState(transform);
		//int64_t t3 = GetMicroSecond();
		//cout << t2 - t1 <<"/"<< t3 - t1 << endl;
	}

	void RenderableTexture::End() {
		//cout << "end: " << fbo << endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		LoadState(savedState);
	}

	std::shared_ptr<Bitmap> RenderableTexture::SaveToBitmap() const {
		auto bmp = std::make_shared<Bitmap>(tex->GetWidth(), tex->GetHeight());
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glReadPixels(0, 0, tex->GetWidth(), tex->GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, bmp->GetData());
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return bmp;
	}

}
