#ifndef GLSHADER_HPP
#define GLSHADER_HPP

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <GL/glew.h>
class Shader {
	/* Creates a handle to manage a shader*/
	public:
		GLuint Program;
		
		Shader(const GLchar* vertex_shader_path, const GLchar* fragment_shader_path);
		void Use();
	private: 
		GLuint createShader(GLenum eShaderType, const char *file_path);
		std::string readFile(const GLchar* path);
};
#endif
