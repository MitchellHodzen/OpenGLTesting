#include "ChunkManager.h"
#include <iostream>

ChunkManager::ChunkManager(int chunkWidth, int chunkHeight, int chunkLength, float blockWidth, float blockHeight, float blockLength)
{
	this->chunkWidth = chunkWidth;
	this->chunkHeight = chunkHeight;
	this->chunkLength = chunkLength;
	this->blockWidth = blockWidth;
	this->blockHeight = blockHeight;
	this->blockLength = blockLength;
	currentChunks = new std::vector<Chunk*>;
	GenerateChunks();
}
ChunkManager::~ChunkManager()
{
}
void ChunkManager::GenerateChunks()
{
	CreateChunkAtPosition(0, -chunkHeight, 0);
	CreateChunkAtPosition(chunkWidth, -chunkHeight, 0);
}
std::vector<Chunk*>* ChunkManager::QueryChunks(glm::vec3 playerPosition)
{
	currentChunks->clear();
	currentChunks->push_back(chunkMap[0][-chunkHeight][0]);
	currentChunks->push_back(chunkMap[chunkWidth][-chunkHeight][0]);
	return currentChunks;
}
void ChunkManager::CreateChunkAtPosition(int x, int y, int z)
{
	chunkMap[x][y][z] = new Chunk(glm::vec3(x, y, z), chunkWidth, chunkHeight, chunkLength, blockWidth, blockHeight, blockLength);
}
