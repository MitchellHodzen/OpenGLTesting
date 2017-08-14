#pragma once
#include "Vertex.h"
#include <vector>
#include <glad/glad.h>
#include <SDL_opengl.h>
#include <SDL.h>

class Mesh
{
	public:
		Mesh();
		void AddVertex(Vertex vertex);
		void Draw();
		void BuildVBO();
	private:
		std::vector<Vertex>* vertices;
		GLuint VAO, VBO;
};
