#include "Shader.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"
#include "Texture.h"
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
	glUniform3f(uniformLocations[name], x, y, z);
}
void Shader::SetVec3(std::string name, glm::vec3 value)
{
	glUniform3f(uniformLocations[name], value.x, value.y, value.z);
}
void Shader::SetVec4(std::string name, float x, float y, float z, float w)
{
	glUniform4f(uniformLocations[name], x, y, z, w);
}
void Shader::SetVec4(std::string name, glm::vec4 value)
{
	glUniform4f(glGetUniformLocation(shaderID, name.c_str()), value.x, value.y, value.z, value.w);
}
void Shader::SetMat4(std::string name, glm::mat4 value)
{
	//glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	glUniformMatrix4fv(uniformLocations[name], 1, GL_FALSE, &value[0][0]);
}
void Shader::SetFloat(std::string name, float value)
{
	glUniform1f(uniformLocations[name], value);
}
void Shader::SetInt(std::string name, int value)
{
	glUniform1i(uniformLocations[name], value);
}
void Shader::SetDirectionalLight(DirectionalLight* light)
{
	//Work with the assumption there is only one directional light in the scene
	SetVec3("directionalLight.ambient", light->ambient);
	SetVec3("directionalLight.diffuse", light->diffuse);
	SetVec3("directionalLight.specular", light->specular);
	SetVec3("directionalLight.direction", light->direction);
}
void Shader::SetMaterial(Material* material)
{
	SetVec3("material.specular", material->specular);
	SetFloat("material.shininess", material->shininess);
	SetInt("material.diffuse", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, material->diffuseTextureID);
}
void Shader::SetUniformLocation(std::string name)
{
	uniformLocations[name] = glGetUniformLocation(shaderID, name.c_str());
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
