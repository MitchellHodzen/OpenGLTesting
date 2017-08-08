#pragma once
#include <glad/glad.h>
#include <SDL_opengl.h>
#include <SDL.h>
#include <iostream>
#include <glm/vec3.hpp>
class Texture;
class Shader;
class Camera;
class Cube;
class DirectionalLight;
class Renderer
{
public:
	Renderer(int screenWidth, int screenHeight, bool debug);
	~Renderer();
	void Draw();
	bool Initialize();
	SDL_Window* GetWindow();
	Camera* camera;
private:
	bool debug;
	SDL_Window* sdlWindow;
	int screenWidth;
	int screenHeight;
	bool InitOpenGL();
	SDL_GLContext gContext;	
	GLuint gProgramID;
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	Shader* shader;
	Texture* texture;
	DirectionalLight* directionalLight;
	glm::vec3* target;
	Cube* cubeArray;
	int cubeAmount;
};

