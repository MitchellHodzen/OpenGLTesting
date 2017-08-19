#include "World.h"
#include "BlockData.h"
#include <iostream>
World::World(int chunkWidth, int chunkHeight, int chunkLength, float blockSize)
{
	this->chunkWidth = chunkWidth;
	this->chunkHeight = chunkHeight;
	this->chunkLength = chunkLength;
	this->blockSize = blockSize;
	GenerateBlockData();
	GenerateChunks();
}
World::~World()
{
}
Chunk* World::GetChunkAtPosition(int x, int y, int z)
{
	//If the chunk at that position doesn't exist, create it
	if (chunkMap.count(x) == 0 || chunkMap[x].count(y) == 0 || chunkMap[x][y].count(z) == 0)
	{
		CreateChunkAtPosition(x, y, z);
		return chunkMap[x][y][z];
	}
	return chunkMap[x][y][z];
}
void World::GenerateChunks()
{
	//Temporarily useless, as chunks are loaded as needed. Remove?
	/*
	for (int x = -2; x <= 2; ++x)
	{
		for(int y = -2; y <= 2; ++y)
		{
			for(int z = -2; z <= 2; ++z)
			{
				CreateChunkAtPosition(x, y, z);
			}
		}
	}
	*/
	/*
	CreateChunkAtPosition(0, -1, 0);
	CreateChunkAtPosition(1, -1, 0);
	CreateChunkAtPosition(-1, -1, 0);
	CreateChunkAtPosition(0, -1, -1);
	CreateChunkAtPosition(0, -1, 1);
	*/
}

void World::CreateChunkAtPosition(int x, int y, int z)
{
	chunkMap[x][y][z] = new Chunk(glm::vec3(x * chunkWidth * blockSize, y * chunkHeight * blockSize, z * chunkLength * blockSize), chunkWidth, chunkHeight, chunkLength, blockSize);
}
void World::GenerateBlockData()
{
	BlockData::CreateBlock(BlockData::BlockName::DIRT, BlockData::BlockVisibility::VISIBLE);
}
float World::GetBlockSize()
{
	return blockSize;
}
