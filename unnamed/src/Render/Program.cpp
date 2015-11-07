#include "Program.hpp"
#include "IO/Stream.hpp"
#include "Base/Log.hpp"

namespace me {

	void glCheckErrors() {
	    GLenum errorCode;
	    while ((errorCode = glGetError()) != GL_NO_ERROR) {
	        static const char* errors[] = {
	            "GL_INVALID_ENUM",
	            "GL_INVALID_VALUE",
	            "GL_INVALID_OPERATION",
	            "GL_STACK_OVERFLOW",
	            "GL_STACK_UNDERFLOW",
	            "GL_OUT_OF_MEMORY"
	        };
	        Log::E("GL ERROR: %s", errors[errorCode - 0x0500]);
	    }
	}

	bool Shader::Compile() {
		if (id == 0)
		{
			Log::E("tried to compile shader with invalid shader id");
			return false;
		}

		char *s = const_cast<char*>(src.c_str());
		glShaderSource(id, 1, (const GLchar**)&s, NULL);
		glCompileShader(id);

		glCheckErrors();
		GLint result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (!result) {
			Log::E("shader compile failed (id=%d)", id);
			//glDeleteShader(shader);
		} else {
			Log::I("shader compile success (id=%d)", id);
		}
		PrintLog();
		return result != 0;
	}

	void Shader::PrintLog() const {
		int infoLogLength = 0;
		int charsWritten = 0;
		GLchar *infoLog;

		glCheckErrors();
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		glCheckErrors();

		if (infoLogLength > 0) {
			infoLog = new GLchar[infoLogLength];
			if (infoLog == NULL) {
				Log::E("ERROR: Cound not allocate InfoLog buffer");
				return;
			}
			glGetShaderInfoLog(id, infoLogLength, &charsWritten, infoLog);
			Log::I("Shader ID: %d\n", id);
			Log::I("Log: %s\n\n", infoLog);
			delete[] infoLog;
		}
		glCheckErrors();
	}

	Program *Program::current = NULL;

	void Program::CreateProgram(GLuint vs, GLuint fs) {
		if (vs == 0 || fs == 0)
			return;
		prog = glCreateProgram();
		glAttachShader(prog, vs);
		glAttachShader(prog, fs);
		BindVars();
		glLinkProgram(prog);
		glCheckErrors();
		glGetProgramiv(prog, GL_LINK_STATUS, &valid);
		PrintLog();
		if (!valid) {
			prog = 0;
			Log::E("failed to link shader program !");
		}
		else {
			glUseProgram(prog);
			ReadLocs();
		}
	}

	Program::Program(GLuint vs, GLuint fs) {
		CreateProgram(vs, fs);
	}

	Program::Program(const VertexShader& vs, const FragmentShader& fs) {
		CreateProgram(vs.GetID(), fs.GetID());
	}

	Program::Program(Stream& vstream, Stream& fstream) {
		VertexShader vs(vstream.ReadToEnd());
		FragmentShader fs(fstream.ReadToEnd());
		CreateProgram(vs.GetID(), fs.GetID());
	}

	Program::Program(const char* vstr, const char* fstr) {
		VertexShader vs(vstr);
		FragmentShader fs(fstr);
		CreateProgram(vs.GetID(), fs.GetID());
	}

	void Program::BindVars() {
		glBindAttribLocation(prog, POSITION_ATTRIB_LOC, "aPosition");
		glBindAttribLocation(prog, COLOR_ATTRIB_LOC, "aColor");
		glBindAttribLocation(prog, NORMAL_ATTRIB_LOC, "aNormal");
		glBindAttribLocation(prog, TEXCOORD_ATTRIB_LOC, "aTexCoord");
	}

	void Program::ReadLocs() {
		uMMatrix = GetUniLoc("uMMatrix");
		uPMatrix = GetUniLoc("uPMatrix");
		uTMatrix = GetUniLoc("uTMatrix");
	}

	void Program::Use() {
		if (!IsValid())
			Log::E("tried to use invalid shader program !");
		if (current != this) {
			current = this;
			glUseProgram(prog);
			/*glUniform1i(uTex, 0);
			glUniform1i(uTex2, 1);
			glUniformMatrix4fv(uMMatrix, 1, false, ModelViewMatrix());
			glUniformMatrix4fv(uPMatrix, 1, false, ProjectionMatrix());
			glUniformMatrix4fv(uTMatrix, 1, false, TextureMatrix());*/
			Log::D("use shader %d", prog);
		}
	}

	GLint Program::GetUniLoc(const GLchar *name) {
		GLint loc = glGetUniformLocation(prog, name);
		if (loc == -1)
			Log::W("No such uniform named \"%s\"", name);
		glCheckErrors();
		return loc;
	}

	GLint Program::GetAttrLoc(const GLchar *name) {
		GLint loc = glGetAttribLocation(prog, name);
		if (loc == -1)
			Log::W("No such attribute named \"%s\"", name);
		glCheckErrors();
		return loc;
	}

	void Program::PrintLog() {
		int infoLogLength = 0;
		int charsWritten = 0;
		GLchar *infoLog;

		glCheckErrors();
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLogLength);
		glCheckErrors();

		if (infoLogLength > 0) {
			infoLog = new GLchar[infoLogLength];
			if (infoLog == NULL) {
				Log::E("ERROR: Cound not allocate InfoLog buffer");
			}
			glGetProgramInfoLog(prog, infoLogLength, &charsWritten, infoLog);
			Log::I("Program InfoLog:\n%s\n", infoLog);
			delete[] infoLog;
		}
		glCheckErrors();
	}

}
