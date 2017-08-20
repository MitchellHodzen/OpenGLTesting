#include "World.h"
#include "BlockData.h"
#include <iostream>
#include "FastNoise.h"
#include "Chunk.h"

World::World(int chunkWidth, int chunkHeight, int chunkLength, float blockSize)
{
	this->chunkWidth = chunkWidth;
	this->chunkHeight = chunkHeight;
	this->chunkLength = chunkLength;
	this->blockSize = blockSize;
	noiseGenerator = new FastNoise();
	GenerateBlockColors();
	GenerateBlockData();
	SetUpNoise();
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
	//if (chunkMap[x][y][z]->GetChunkMesh() == NULL)
	//{
		//chunkMap[x][y][z]->GenerateChunkMesh();
	//}
	return chunkMap[x][y][z];
}
void World::SetUpNoise()
{
	noiseGenerator->SetNoiseType(FastNoise::SimplexFractal);
}

void World::CreateChunkAtPosition(int x, int y, int z)
{
	glm::vec3 chunkPosition(x * chunkWidth * blockSize, y * chunkHeight * blockSize, z * chunkLength * blockSize);
	int* heightArray = new int[chunkWidth * chunkLength];
	for (int noiseX = 0; noiseX < chunkWidth; ++noiseX)
	{
		for (int noiseY = 0; noiseY < chunkLength; ++noiseY)
		{
			int positionX = chunkPosition.x + (noiseX * blockSize);
			int positionY = chunkPosition.z + (noiseY * blockSize);
			heightArray[noiseX + (noiseY * chunkWidth)] = (noiseGenerator->GetNoise(positionX, positionY)) * 32;
		}
	}
	chunkMap[x][y][z] = new Chunk(chunkPosition, this, chunkWidth, chunkHeight, chunkLength, blockSize, heightArray);
	delete[] heightArray;
}
//bool test = true;
Block* World::GetBlockAtPosition(int x, int y, int z)
{
	/*
	if (test)
	{
		std::cout<<x/chunkWidth<<" "<<y/chunkHeight<<" "<<z/chunkLength<<std::endl;
		std::cout<<floor(x/chunkWidth)<<" "<<floor(y/chunkHeight)<<" "<<floor(z/chunkLength)<<std::endl;
		test = false;
	}
	*/
	//std::cout<<x<<" "<<y<<" "<<z<<std::endl;
	int chunkX = floor((float)x/chunkWidth);
	int chunkY = floor((float)y/chunkHeight);
	int chunkZ = floor((float)z/chunkLength);
	Chunk* chunk = GetChunkAtPosition(chunkX, chunkY, chunkZ);
	glm::vec3 chunkPosition = chunk->GetChunkPosition();
	int blockX =(x - (int)chunkPosition.x + chunkWidth)%chunkWidth;
	int blockY =(y - (int)chunkPosition.y + chunkHeight)%chunkHeight;
	int blockZ =(z - (int)chunkPosition.z + chunkLength)%chunkLength;

	//std::cout<<chunkPosition.x<<" "<<chunkPosition.y<<" "<<chunkPosition.z<<".   "<< chunkX << " "<<chunkY<<" "<<chunkZ<<".   "<<x<<" "<<y<<" "<<z<<".   "<<blockX<<", "<<blockY<<", "<<blockZ<<std::endl;
	return chunk->GetBlockAtPosition(blockX, blockY, blockZ);
}
void World::GenerateBlockData()
{
	BlockData::CreateBlock(BlockData::BlockName::DIRT, BlockData::BlockVisibility::VISIBLE, BlockData::BlockColor::BROWN);
	BlockData::CreateBlock(BlockData::BlockName::GRASS, BlockData::BlockVisibility::VISIBLE, BlockData::BlockColor::GREEN);
	BlockData::CreateBlock(BlockData::BlockName::AIR, BlockData::BlockVisibility::INVISIBLE, BlockData::BlockColor::WHITE);
}
void World::GenerateBlockColors()
{
	BlockData::SetColor(BlockData::BlockColor::GREEN, glm::vec3(0.0f, 0.6f, 0.1f));
	BlockData::SetColor(BlockData::BlockColor::BROWN, glm::vec3(0.8f, 0.4f, 0.0f));
	BlockData::SetColor(BlockData::BlockColor::WHITE, glm::vec3(1.0f, 1.0f, 1.0f));
}
float World::GetBlockSize()
{
	return blockSize;
}
