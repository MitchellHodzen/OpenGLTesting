#include "World.h"
#include "BlockData.h"
#include <iostream>
#include "FastNoise.h"

World::World(int chunkWidth, int chunkHeight, int chunkLength, float blockSize)
{
	this->chunkWidth = chunkWidth;
	this->chunkHeight = chunkHeight;
	this->chunkLength = chunkLength;
	this->blockSize = blockSize;
	noiseGenerator = new FastNoise();
	GenerateBlockData();
	GenerateChunks();
}
World::~World()
{
	delete noiseGenerator;
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
	noiseGenerator->SetNoiseType(FastNoise::SimplexFractal);
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
	glm::vec3 chunkPosition(x * chunkWidth * blockSize, y * chunkHeight * blockSize, z * chunkLength * blockSize);
	//int heightArray[chunkWidth * chunkLength];
	int* heightArray = new int[chunkWidth * chunkLength];
	for (int noiseX = 0; noiseX < chunkWidth; ++noiseX)
	{
		for (int noiseY = 0; noiseY < chunkLength; ++noiseY)
		{
			int positionX = chunkPosition.x + (noiseX * blockSize);
			int positionY = chunkPosition.z + (noiseY * blockSize);
			heightArray[noiseX + (noiseY * chunkWidth)] = (noiseGenerator->GetNoise(positionX, positionY)) * 32;
			//std::cout<<heightArray[x + (y * chunkWidth)]<<std::endl;
		}
	}
	chunkMap[x][y][z] = new Chunk(chunkPosition, chunkWidth, chunkHeight, chunkLength, blockSize, heightArray);
	delete[] heightArray;
}
void World::GenerateBlockData()
{
	BlockData::CreateBlock(BlockData::BlockName::DIRT, BlockData::BlockVisibility::VISIBLE);
	BlockData::CreateBlock(BlockData::BlockName::AIR, BlockData::BlockVisibility::INVISIBLE);
}
float World::GetBlockSize()
{
	return blockSize;
}
