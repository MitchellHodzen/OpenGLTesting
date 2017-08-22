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
	glm::vec3 chunkPosition((float)x * (float)chunkWidth * blockSize, (float)y * (float)chunkHeight * blockSize, (float)z * (float)chunkLength * blockSize);
	float* heightArray = new float[chunkWidth * chunkLength];
	for (int noiseX = 0; noiseX < chunkWidth; ++noiseX)
	{
		for (int noiseY = 0; noiseY < chunkLength; ++noiseY)
		{
			float positionX = chunkPosition.x + (noiseX * blockSize);
			float positionY = chunkPosition.z + (noiseY * blockSize);
			heightArray[noiseX + (noiseY * chunkWidth)] = (noiseGenerator->GetNoise(positionX, positionY)) * 32;
		}
	}
	chunkMap[x][y][z] = new Chunk(chunkPosition, this, chunkWidth, chunkHeight, chunkLength, blockSize, heightArray);
	delete[] heightArray;
}
//bool test = true;
Block* World::GetBlockAtPosition(glm::vec3 blockPosition)
{
	//Chunk position is consistent
	int chunkX = floor((float)blockPosition.x/(chunkWidth * blockSize));
	int chunkY = floor((float)blockPosition.y/(chunkHeight * blockSize));
	int chunkZ = floor((float)blockPosition.z/(chunkLength * blockSize));
	//std::cout<<chunkX<<" "<<chunkY<<" "<<chunkZ<<std::endl;
	Chunk* chunk = GetChunkAtPosition(chunkX, chunkY, chunkZ);
	glm::vec3 chunkPosition = chunk->GetChunkPosition();
	/*
	int blockIndexX = (int)floor((blockPosition.x  - chunkPosition.x + chunkWidth))%chunkWidth;
	int blockIndexY = (int)floor((blockPosition.y - chunkPosition.y + chunkHeight))%chunkHeight;
	int blockIndexZ = (int)floor((blockPosition.z  - chunkPosition.z + chunkLength))%chunkLength;

	int blockIndexX = (int)(((blockPosition.x  - chunkPosition.x)/blockSize) + chunkWidth)%chunkWidth;
	int blockIndexY = (int)(((blockPosition.y - chunkPosition.y)/blockSize) + chunkHeight)%chunkHeight;
	int blockIndexZ = (int)(((blockPosition.z  - chunkPosition.z)/blockSize) + chunkLength)%chunkLength;
	*/
	int blockIndexX = (blockPosition.x  - chunkPosition.x)/blockSize;
	int blockIndexY = (blockPosition.y - chunkPosition.y)/blockSize;
	int blockIndexZ = (blockPosition.z  - chunkPosition.z)/blockSize;
	//std::cout<<blockPosition.x<<" - "<<chunkPosition.x<<" / "<<blockSize<<" = "<<(blockPosition.x - chunkPosition.x)/blockSize<<std::endl;
	//std::cout<<blockIndexX<<" "<<blockIndexY<<" "<<blockIndexZ<<std::endl;

	//std::cout<<((int)(x * blockSize) - (int)chunkPosition.x + chunkWidth)%chunkWidth<<" "<<((int)(y * blockSize) - (int)chunkPosition.y + chunkHeight)%chunkHeight<<" "<<((int)(z*blockSize) - (int)chunkPosition.z + chunkLength)%chunkLength<<std::endl;

	return chunk->GetBlockAtPosition(blockIndexX, blockIndexY, blockIndexZ);
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
