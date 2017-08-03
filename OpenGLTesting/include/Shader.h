#pragma once
#include <glad/glad.h>
#include <SDL_opengl.h>
#include <SDL.h>
#include <string>
#include <fstream>
#include <iostream>

class Shader
{
	public:
		Shader();
		~Shader();
		bool ReadFragmentShader(std::string location);
		bool ReadVertexShader(std::string location);
		GLuint GetShaderID();
		bool LinkShaders();
	private:
		GLuint shaderID;
		GLuint vertexShader;
		GLuint fragmentShader;
		std::string ReadShader(std::string location);
};
