#include "Shader.h"
Shader::Shader()
{
}
Shader::~Shader()
{
}
bool Shader::LinkShaders()
{
	bool success = true;
	shaderID = glCreateProgram();	
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);
	GLint programLinked = GL_FALSE;
	glGetProgramiv(shaderID, GL_LINK_STATUS, &programLinked);
	if (programLinked != GL_TRUE)
	{
		std::cout<<"Unable to link program"<<std::endl;
		success = false;
	}	
	else
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	return success;
	
}
bool Shader::ReadFragmentShader(std::string location)
{
	bool success = true;
	std::string fragmentShaderSourceString = ReadShader(location);
	const char* fragmentShaderSource = fragmentShaderSourceString.c_str();
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	GLint fragmentShaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompiled);
	if (fragmentShaderCompiled != GL_TRUE)
	{
		std::cout<<"Unable to compile fragment shader"<<std::endl;
		success = false;
	}
	return success;
}

bool Shader::ReadVertexShader(std::string location)
{
	bool success = true;
	std::string vertexShaderSourceString = ReadShader(location);
	const char* vertexShaderSource = vertexShaderSourceString.c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint vertexShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompiled);
	if (vertexShaderCompiled != GL_TRUE)
	{
		std::cout<<"Unable to compile vertex shader"<<std::endl;
		success = false;
	}
	return success;
}
void Shader::SetVec3(std::string name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);
}
void Shader::SetVec3(std::string name, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(shaderID, name.c_str()), value.x, value.y, value.z);
}
void Shader::SetVec4(std::string name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);
}
void Shader::SetVec4(std::string name, glm::vec4 value)
{
	glUniform4f(glGetUniformLocation(shaderID, name.c_str()), value.x, value.y, value.z, value.w);
}
void Shader::SetMat4(std::string name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
void Shader::SetFloat(std::string name, float value)
{
	glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}
void Shader::SetInt(std::string name, int value)
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

std::string Shader::ReadShader(std::string location)
{
	std::ifstream shaderStream(location, std::ios::in);
	std::string shaderString{ std::istreambuf_iterator<char>(shaderStream), std::istreambuf_iterator<char>()};
	return shaderString;
}
GLuint Shader::GetShaderID()
{
	return shaderID;
}
