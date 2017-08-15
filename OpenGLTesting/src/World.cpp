#include "World.h"
World::World(int chunkWidth, int chunkHeight, int chunkLength, float blockWidth, float blockHeight, float blockLength)
{
	this->chunkWidth = chunkWidth;
	this->chunkHeight = chunkHeight;
	this->chunkLength = chunkLength;
	this->blockWidth = blockWidth;
	this->blockHeight = blockHeight;
	this->blockLength = blockLength;
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
	CreateChunkAtPosition(0, -chunkHeight, 0);
	CreateChunkAtPosition(chunkWidth, -chunkHeight, 0);
}

void World::CreateChunkAtPosition(int x, int y, int z)
{
	chunkMap[x][y][z] = new Chunk(glm::vec3(x, y, z), chunkWidth, chunkHeight, chunkLength, blockWidth, blockHeight, blockLength);
}
