#include "World.h"
#include "BlockData.h"
#include <iostream>
World::World(int chunkWidth, int chunkHeight, int chunkLength, float blockWidth, float blockHeight, float blockLength)
{
	this->chunkWidth = chunkWidth;
	this->chunkHeight = chunkHeight;
	this->chunkLength = chunkLength;
	this->blockWidth = blockWidth;
	this->blockHeight = blockHeight;
	this->blockLength = blockLength;
	GenerateBlockData();
	GenerateChunks();
}
World::~World()
{
}
Chunk* World::GetChunkAtPosition(int x, int y, int z)
{
	return chunkMap[x][y][z];
}
void World::GenerateChunks()
{
	CreateChunkAtPosition(0, -1, 0);
	CreateChunkAtPosition(1, -1, 0);
	CreateChunkAtPosition(-1, -1, 0);
	CreateChunkAtPosition(0, -1, -1);
	CreateChunkAtPosition(0, -1, 1);
}

void World::CreateChunkAtPosition(int x, int y, int z)
{
	chunkMap[x][y][z] = new Chunk(glm::vec3(x * chunkWidth * blockWidth, y * chunkHeight * blockHeight, z * chunkLength * blockLength), chunkWidth, chunkHeight, chunkLength, blockWidth, blockHeight, blockLength);
}
void World::GenerateBlockData()
{
	BlockData::CreateBlock(BlockData::BlockName::DIRT, BlockData::BlockVisibility::VISIBLE);
}
