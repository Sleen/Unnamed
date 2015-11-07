#include <iostream>
#include <iomanip>
#include <cmath>

#include "Unnamed.hpp"
#include "String.hpp"
#include "Base/System.hpp"
#include "Base/Log.hpp"
#include "Render/GL.hpp"
#include "Render/Program.hpp"
#include "Render/Transform.hpp"

using namespace me;
using namespace unnamed;

void dump(const String& str) {
    std::cout<<str.Utf8String()<<" {"<<str.length()<<"}  ";
    for (int i=0;i<str.length();i++) {
        std::cout<<std::hex<<std::uppercase<<std::setw((int)ceil(log2(str.CharAt(i))/8)*2)<<std::setfill('0')<<str.CharAt(i)<<" ";
    }
    std::cout<<std::dec<<std::nouppercase<<std::endl;
}

class TestApp : Application
{
public:
	TestApp() {}
	~TestApp() {}
    
	void OnStart() {
		std::cout<<"OnStart"<<std::endl;
        
        dump(String(1));
        dump(String((int8_t)1));
        dump(String((uint8_t)1));
        dump(String('1'));
        dump(String(String("123")==String("12")+"3"));
        dump(String(String("123")==String("1234")));
        dump(String(String("12345").StartsWith(String("1234"))));
        dump(String(String("12345") == String(1123456).Substring(1, 5)));
        dump(String("   ").Trim());
        std::cout<<String("abcdef").IndexOf('c')<<std::endl;
        std::cout<<String("123测试文字").IndexOf(U'文')<<std::endl;
        std::cout<<String("aabbababaaababbba").IndexOf(String("aab"), 1)<<std::endl;
	}
    
	void OnExit() {
        std::cout<<"OnExit"<<std::endl;
    }
    
    void OnDraw() {
        //    Graphics g;
        //    g.Begin();
        //    g.DrawLine(Color::Green, Vector2(10, 10), Vector2(100, 100));
        //    g.FillOval(Color::Blue, 500, 20, 300, 200);
        
        test();
        glCheckErrors();
    }
    
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
    
    void printShaderLog(GLuint id) {
        int infoLogLength = 0;
        int charsWritten = 0;
        GLchar *infoLog;
        
        glCheckErrors();
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
        glCheckErrors();
        
        if (infoLogLength > 0) {
            infoLog = (GLchar*)malloc(infoLogLength);
            if (infoLog == NULL) {
                Log::E("ERROR: Cound not allocate InfoLog buffer");
                exit(1);
            }
            glGetShaderInfoLog(id, infoLogLength, &charsWritten, infoLog);
            Log::I("Shader ID: %d\n", id);
            Log::I("Log: %s\n\n", infoLog);
            free(infoLog);
        }
        glCheckErrors();
    }
    
    void printProgramLog(GLuint program) {
        int infoLogLength = 0;
        int charsWritten = 0;
        GLchar *infoLog;
        
        glCheckErrors();
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        glCheckErrors();
        
        if (infoLogLength > 0) {
            infoLog = (GLchar*)malloc(infoLogLength);
            if (infoLog == NULL) {
                Log::E("ERROR: Cound not allocate InfoLog buffer");
                exit(1);
            }
            glGetProgramInfoLog(program, infoLogLength, &charsWritten, infoLog);
            Log::I("Program InfoLog:\n%s\n", infoLog);
            free(infoLog);
        }
        glCheckErrors();
    }
    
    GLint getUniLoc(GLuint program, const GLchar *name) {
        GLint loc = glGetUniformLocation(program, name);
        if (loc == -1)
            Log::W("No such uniform named \"%s\"", name);
        glCheckErrors();
        return loc;
    }
    
    void test() {
        const char* vertexShader = R"(
        
        uniform mat4 uMvp;
        attribute vec3 aPosition;
        varying vec3 vPosition;
        
        void main(){
            gl_Position = uMvp * vec4(aPosition, 1.0);
            vPosition = aPosition;
        }
        
        )";
        
        const char* fragmentShader = R"(
        
        varying vec3 vPosition;
        
        void main() {
            gl_FragColor = vec4(1.0, mod(vPosition.x/100.0, 1.0), mod(vPosition.y/100.0, 1.0), mod(vPosition.y/100.0, 1.0));
        }
        
        )";
        
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        
        if (!vs || !fs) {
            Log::E("failed to create shader");
        }
        
        GLint result;
        
        glShaderSource(vs, 1, &vertexShader, NULL);
        glCompileShader(vs);
        glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
        
        if (!result) {
            Log::E("failed to compile vertex shader");
        }
        
        printShaderLog(vs);
        
        glShaderSource(fs, 1, &fragmentShader, NULL);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
        
        if (!result) {
            Log::E("failed to compile fragment shader");
        }
        
        printShaderLog(fs);
        
        GLuint program = glCreateProgram();
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        // bind location of attributes
        glBindAttribLocation(program, POSITION_ATTRIB_LOC, "aPosition");
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &result);
        if (!result) {
            Log::E("failed to link shaders");
        }
        printProgramLog(program);
        
        glUseProgram(program);
        // get location of uniforms
        GLint uMvp = getUniLoc(program, "uMvp");
        
        glUniformMatrix4fv(uMvp, 1, false, MVPMatrix());
        
        glEnableVertexAttribArray(POSITION_ATTRIB_LOC);
        float points[] = {10, 10, 0, 500, 10, 0, 10, 500, 0};
        glVertexAttribPointer(POSITION_ATTRIB_LOC, 3, GL_FLOAT, GL_FALSE, 0, points);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(POSITION_ATTRIB_LOC);
    }

};

TestApp app;
