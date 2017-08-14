#include "Chunk.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


Chunk::Chunk(glm::vec3 chunkPosition, int width, int height, int length, float blockWidth, float blockHeight, float blockLength)
{
	this->chunkPosition = chunkPosition;
	chunkWidth = width;
	chunkHeight = height;
	chunkLength = length;
	this->blockWidth = blockWidth;
	this->blockHeight = blockHeight;
	this->blockLength = blockLength;
	modelMatricies = new std::vector<glm::mat4>;
	chunkMesh = new Mesh();
	GenerateChunk();
}
Chunk::~Chunk()
{
	for (int x = 0; x < chunkWidth; ++x)
	{
		for (int y = 0; y < chunkHeight; ++y)
		{
			delete[] chunkData[x][y];
		}
		delete[] chunkData[x];
	}
	delete[] chunkData;
	delete chunkMesh;
	delete modelMatricies;
}

void Chunk::GenerateChunk()
{
	chunkData = new BlockType**[chunkWidth];
	for (int x = 0; x < chunkWidth; ++x)
	{
		chunkData[x] = new BlockType*[chunkHeight];
		for (int y = 0; y < chunkHeight; ++y)
		{
			chunkData[x][y] = new BlockType[chunkLength];
			for (int z = 0; z < chunkLength; ++z)
			{
				chunkData[x][y][z] = BlockType::DIRT;
			}
		}
	}
	GenerateModelMatricies();
}

void Chunk::GenerateModelMatricies()
{
	for (int x = 0; x < chunkWidth; ++x)
	{
		for (int y = 0; y < chunkHeight; ++y)
		{
			for (int z = 0; z < chunkLength; ++z)
			{
				if (CheckBlockVisible(x, y, z))
				{
					//modelMatricies[x*chunkHeight*chunkLength + y*chunkLength + z] = glm::translate(glm::mat4(), GetBlockPosition(x, y, z));
					glm::vec3 position = GetBlockPosition(x, y, z);
					/*
					modelMatricies->push_back(glm::translate(glm::mat4(), GetBlockPosition(x, y, z)));
					Vertex vert1, vert2, vert3, vert4, vert5, vert6;
					vert1.position = glm::vec3(-0.5f, -0.5f, -0.5f);
					vert1.normal = glm::vec3(0.0f, 0.0f, -1.0f);
					vert1.textureCoordinates = glm::vec2(0.0f, 0.0f);
					vert2.position = glm::vec3(0.5f, 0.5f, -0.5f);
					vert2.normal = glm::vec3(0.0f, 0.0f, -1.0f);
					vert2.textureCoordinates = glm::vec2(1.0f, 1.0f);
					vert3.position = glm::vec3(0.5f, -0.5f, -0.5f);
					vert3.normal = glm::vec3(0.0f, 0.0f, -1.0f);
					vert3.textureCoordinates = glm::vec2(1.0f, 0.0f);
					vert4.position = glm::vec3(0.5f, 0.5f, -0.5f);
					vert4.normal = glm::vec3(0.0f, 0.0f, -1.0f);
					vert4.textureCoordinates = glm::vec2(1.0f, 1.0f);
					vert5.position = glm::vec3(-0.5f, -0.5f, -0.5f);
					vert5.normal = glm::vec3(0.0f, 0.0f, -1.0f);
					vert5.textureCoordinates = glm::vec2(0.0f, 0.0f);
					vert6.position = glm::vec3(-0.5f, 0.5f, -0.5f);
					vert6.normal = glm::vec3(0.0f, 0.0f, -1.0f);
					vert6.textureCoordinates = glm::vec2(0.0f, 1.0f);
					chunkMesh->AddVertex(vert1);
					chunkMesh->AddVertex(vert2);
					chunkMesh->AddVertex(vert3);
					chunkMesh->AddVertex(vert4);
					chunkMesh->AddVertex(vert5);
					chunkMesh->AddVertex(vert6);
					*/
				}
			}
		}
	}
	chunkMesh->BuildVBO();
}

Mesh* Chunk::GetChunkMesh()
{
	return chunkMesh;
}
std::vector<glm::mat4>* Chunk::GetModelMatricies()
{
	return modelMatricies;
}
bool Chunk::CheckBlockVisible(int x, int y, int z)
{
	int count = 6;
	if (GetBlockType(x - 1, y, z) == BlockType::DIRT) {--count;}
	if (GetBlockType(x, y - 1, z) == BlockType::DIRT) {--count;}
	if (GetBlockType(x, y, z - 1) == BlockType::DIRT) {--count;}
	if (GetBlockType(x + 1, y, z) == BlockType::DIRT) {--count;}
	if (GetBlockType(x, y + 1, z) == BlockType::DIRT) {--count;}
	if (GetBlockType(x, y, z + 1) == BlockType::DIRT) {--count;}

	if (count == 0)
	{

		return false;
	}
	return true;
}
glm::vec3 Chunk::GetBlockPosition(int x, int y, int z)
{
	return glm::vec3(chunkPosition.x + (x * blockWidth) , chunkPosition.y + (y * blockHeight), chunkPosition.z + (z * blockLength));
}
glm::vec3 Chunk::GetChunkPosition()
{
	return chunkPosition;
}
BlockType Chunk::GetBlockType(int x, int y, int z)
{
	if (x < 0 || y < 0 || z < 0 || x >= chunkWidth || y >= chunkHeight || z >= chunkLength)
	{
		return BlockType::AIR;
	}
	return chunkData[x][y][z];
}
int Chunk::GetChunkWidth()
{
	return chunkWidth;
}
int Chunk::GetChunkHeight()
{
	return chunkHeight;
}
int Chunk::GetChunkLength()
{
	return chunkLength;
}
int Chunk::GetChunkSize()
{
	return chunkWidth * chunkHeight * chunkLength;
}
