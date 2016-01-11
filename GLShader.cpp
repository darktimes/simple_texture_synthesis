#include "GLShader.hpp"

void Shader::Use() {
	glUseProgram(this->Program);
}

Shader::Shader(const GLchar* vertex_shader_path, const GLchar* fragment_shader_path)
{
	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertex_shader_path);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragment_shader_path);
	
	GLint success;
	GLchar infoLog[512];
	this->Program = glCreateProgram();
	
	glAttachShader(this->Program, vertexShader);
	glAttachShader(this->Program, fragmentShader);

	glLinkProgram(this->Program);
	// Print linking errors if any
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint Shader::createShader(GLenum eShaderType, const GLchar *file_path)
{
	std::string shaderStr = readFile(file_path);
	const GLchar* shaderCode = shaderStr.c_str();
    GLint success;
    GLchar infoLog[512];
    
    GLuint shader = glCreateShader(eShaderType);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	// Print compile errors if any
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

std::string Shader::readFile(const GLchar *file_path)
{
	std::string result;
	std::ifstream shaderFile;	
	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		shaderFile.open(file_path);
		std::stringstream shaderStream;
		// Read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// Convert stream into string
		result = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return result;
}
