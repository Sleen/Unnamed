#pragma once

#include <string>
#include <memory>

#include "Transform.hpp"
#include "GL.hpp"

//#include "Reflection/Reflection.hpp"

namespace me {

	class Bitmap;

	class Texture {
		/*BEGIN_TYPE(Texture)
			CTORS(DEFAULT_CTOR(), CTOR(int, int), CUSTOM_CTOR(Load))
			END_TYPE*/
	protected:
		GLuint id = 0;
		int width = 0, height = 0;
		static int current_id;

	public:
		Texture() {}
		Texture(const Bitmap& bmp);
		Texture(const std::string& file);
		Texture(int width, int height);
		Texture(int width, int height, int* data);

		Texture(const Texture& tex) {
			Delete();
			id = tex.id;
			width = tex.width;
			height = tex.height;
			const_cast<Texture&>(tex).id = 0;
		}

		Texture(Texture&& tex) {
			Delete();
			id = tex.id;
			width = tex.width;
			height = tex.height;
			tex.id = 0;
		}

		Texture& operator=(const Texture& tex) {
			Delete();
			id = tex.id;
			width = tex.width;
			height = tex.height;
			const_cast<Texture&>(tex).id = 0;
			return *this;
		}

		Texture& operator=(Texture&& tex) {
			Delete();
			id = tex.id;
			width = tex.width;
			height = tex.height;
			tex.id = 0;
			return *this;
		}

		virtual ~Texture() {
			Delete();
		}

		static Texture* Load(const std::string& res);

		// never invoke glBindTexture directly!
		static void Bind(GLuint id) {
			if (current_id != id) {
				glBindTexture(GL_TEXTURE_2D, id);
				current_id = id;
			}
		}

		void Bind() const {
			//if (current_id != id) {
				glBindTexture(GL_TEXTURE_2D, id);
				current_id = id;
			//}
		}

		void Delete();

		void SetParam(GLenum param, GLfloat value) {
			Bind();
			glTexParameterf(GL_TEXTURE_2D, param, value);
		}

		int GetWidth() const {
			return width;
		}

		int GetHeight() const {
			return height;
		}

		GLuint GetID() const {
			return id;
		}

		std::shared_ptr<Bitmap> SaveToBitmap() const;
	};

	class RenderableTexture {
	protected:
		Texture* tex = NULL;
		bool del = false;
		GLuint depth_stencil_buffer = 0;
		GLuint fbo = 0;
		std::shared_ptr<Transform> transform, savedState;

		void Setup(bool useStencilBuffer);

	public:
		RenderableTexture(int width, int height, bool useStencilBuffer = false);
		RenderableTexture(Texture* tex, bool useStencilBuffer = false);
		void Begin();
		void End();
		std::shared_ptr<Bitmap> SaveToBitmap() const;

		~RenderableTexture() {
			glDeleteFramebuffers(1, &fbo);

			if (del && tex)
				delete tex;

			if (depth_stencil_buffer)
				glDeleteRenderbuffers(1, &depth_stencil_buffer);
		}

		Texture* GetTexture() {
			return tex;
		}

	};

}
