#pragma once
#include <glad/glad.h>
#include <SDL_opengl.h>
#include <SDL.h>
#include <string>
#include <fstream>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
class DirectionalLight;
class PointLight;
class Shader
{
	public:
		Shader();
		~Shader();
		bool ReadFragmentShader(std::string location);
		bool ReadVertexShader(std::string location);
		GLuint GetShaderID();
		bool LinkShaders();
		void SetVec3(std::string name, float x, float y, float z);
		void SetVec3(std::string name, glm::vec3 value);
		void SetVec4(std::string name, float x, float y, float z, float w);
		void SetVec4(std::string name, glm::vec4 value);
		void SetMat4(std::string name, glm::mat4 value);
		void SetFloat(std::string name, float value);
		void SetInt(std::string name, int value);
		void SetDirectionalLight(DirectionalLight* light);
	private:
		GLuint shaderID;
		GLuint vertexShader;
		GLuint fragmentShader;
		std::string ReadShader(std::string location);
};
