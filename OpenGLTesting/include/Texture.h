#pragma once
#include <glad/glad.h>
#include <SDL_opengl.h>
#include <iostream>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();
	bool LoadTexture(std::string path, GLenum sWrap, GLenum tWrap, GLenum minFilter, GLenum magFilter);
	void FreeTexture();

	int GetHeight();
	int GetWidth();
	GLuint GetTextureID();

private:
	GLuint textureID;
};

