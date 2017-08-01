#pragma once
//#include <glad/glad.h>
//#include <SDL_opengl.h>
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include "Texture.h"
#include "Renderer.h"
#include "InputManager.h"
class Game
{
public:
	Game();
	~Game();
	void Start();
private:
	void printProgramLog(GLuint program);
	void printShaderLog(GLuint shader);
	bool Initialize();
	int screenWidth;
	int screenHeight;
	int levelWidth;
	int levelHeight;

	Renderer* renderer;
	InputManager* inputManager;

};

