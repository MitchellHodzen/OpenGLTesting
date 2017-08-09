#include "Chunk.h"

Chunk::Chunk(int width, int height, int length)
{
	chunkWidth = width;
	chunkHeight = height;
	chunkLength = length;
	GenerateChunk();
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
}
