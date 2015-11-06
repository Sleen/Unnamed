#pragma once

#include <string>

#include "Render/GL.hpp"

namespace me {

	class Stream;

	class Shader {
	protected:
		GLuint id = 0;
		std::string src;

		Shader(const std::string& src) {
			this->src = src;
		}

		virtual bool Compile() = 0;
		virtual void PrintLog() const;

	public:

		GLuint GetID() const {
			return id;
		}

		const std::string& GetSource() const {
			return src;
		}
	};

	class VertexShader : public Shader {
	private:
		bool Compile() override{
			id = glCreateShader(GL_VERTEX_SHADER);
			return Shader::Compile();
		}

	public:
		VertexShader(const std::string& src)
			: Shader(src) {
			Compile();
		}

	};

	class FragmentShader : public Shader {
	private:
		bool Compile() override{
			id = glCreateShader(GL_FRAGMENT_SHADER);
			return Shader::Compile();
		}

	public:
		FragmentShader(const std::string& src)
			: Shader(src) {
			Compile();
		}
		
	};

	enum ShaderLoc {
		POSITION_ATTRIB_LOC,
		COLOR_ATTRIB_LOC,
		NORMAL_ATTRIB_LOC,
		TEXCOORD_ATTRIB_LOC
	};

	class Program {
	private:
		GLint valid;

	protected:
		GLuint prog = 0;

		static Program *current;

		void CreateProgram(GLuint vs, GLuint fs);
		void PrintLog();
		void BindVars();
		void ReadLocs();

	public:
		GLuint uMMatrix;
		GLuint uPMatrix;
		GLuint uTMatrix;

		Program(GLuint vs, GLuint fs);
		Program(Stream& vs, Stream& fs);
		Program(const VertexShader& vs, const FragmentShader& fs);
		Program(const char* vs, const char* fs);

		bool IsValid() { return valid != 0; }
		void Use();
		GLuint GetID() const { return prog; }
		GLint GetUniLoc(const GLchar *name);
		GLint GetAttrLoc(const GLchar *name);

		static Program* CurrentShader() {
			return current;
		}

	};

}
