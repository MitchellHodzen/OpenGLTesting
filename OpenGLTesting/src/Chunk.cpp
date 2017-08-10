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
	//modelMatricies = new glm::mat4[width * height * length];
	modelMatricies = new std::vector<glm::mat4>;
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
	//delete[] modelMatricies;
	delete modelMatricies;
}

void Chunk::GenerateChunk()
{
	chunkData = new Block**[chunkWidth];
	for (int x = 0; x < chunkWidth; ++x)
	{
		chunkData[x] = new Block*[chunkHeight];
		for (int y = 0; y < chunkHeight; ++y)
		{
			chunkData[x][y] = new Block[chunkLength];
			for (int z = 0; z < chunkLength; ++z)
			{
				chunkData[x][y][z] = Block::DIRT;
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
					modelMatricies->push_back(glm::translate(glm::mat4(), GetBlockPosition(x, y, z)));
				}
			}
		}
	}
}
std::vector<glm::mat4>* Chunk::GetModelMatricies()
{
	return modelMatricies;
}
bool Chunk::CheckBlockVisible(int x, int y, int z)
{
	int count = 6;
	if (GetBlockType(x - 1, y, z) == Block::DIRT) {--count;}
	if (GetBlockType(x, y - 1, z) == Block::DIRT) {--count;}
	if (GetBlockType(x, y, z - 1) == Block::DIRT) {--count;}
	if (GetBlockType(x + 1, y, z) == Block::DIRT) {--count;}
	if (GetBlockType(x, y + 1, z) == Block::DIRT) {--count;}
	if (GetBlockType(x, y, z + 1) == Block::DIRT) {--count;}

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
Block Chunk::GetBlockType(int x, int y, int z)
{
	if (x < 0 || y < 0 || z < 0 || x >= chunkWidth || y >= chunkHeight || z >= chunkLength)
	{
		return Block::AIR;
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
