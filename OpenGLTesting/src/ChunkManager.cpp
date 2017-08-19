#include "ChunkManager.h"
#include "World.h"
#include <iostream>

ChunkManager::ChunkManager(World* world, int chunkWidth, int chunkHeight, int chunkLength)
{
	this->chunkWidth = chunkWidth;
	this->chunkHeight = chunkHeight;
	this->chunkLength = chunkLength;
	this->world = world;
}
ChunkManager::~ChunkManager()
{
}

std::vector<Chunk*> ChunkManager::QueryChunks(glm::vec3 playerPosition)
{
	//We add an offset of one half the block size because a block's origin is its center. May be easier to change blocks origin to corner
	int chunkX = floor((playerPosition.x + world->GetBlockSize()/2) / world->GetBlockSize() / chunkWidth);
	int chunkY = floor((playerPosition.y + world->GetBlockSize()/2) / world->GetBlockSize() / chunkHeight);
	int chunkZ = floor((playerPosition.z + world->GetBlockSize()/2) / world->GetBlockSize() / chunkLength);
	//std::cout<<chunkX << ", " << chunkY << ", " << chunkZ << std::endl;
	std::vector<Chunk*> chunks;
	int amount = 1;
	for(int x = chunkX - amount; x <= chunkX + amount; ++x)
	{
		for(int z = chunkZ - amount; z <= chunkZ + amount; ++z)
		{
			chunks.push_back(world->GetChunkAtPosition(x, chunkY - 1, z));
		}
	}
	return chunks;
}

