#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture()
{
}

Texture::~Texture()
{
}

GLuint Texture::GetTextureID()
{
	return textureID;
}

bool Texture::LoadTexture(std::string path, GLenum sWrap, GLenum tWrap, GLenum minFilter, GLenum magFilter)
{
	unsigned char* data;
	int width;
	int height;
	int nrChannels;
	data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);	
	if (data)
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);	
		return true;
	}
	std::cout<<"Failed to load texture"<<std::endl;
	return false;
}

