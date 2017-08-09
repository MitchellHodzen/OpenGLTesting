#pragma once
#include <vector>
#include "BlockTypes.h"
#include <glm/vec3.hpp>

class Chunk
{
	public:
		Chunk(glm::vec3 chunkPosition, int width, int height, int length, float blockWidth, float blockHeight, float blockLength);
		~Chunk();
		Block*** chunkData;
		glm::vec3 GetBlockPosition(int x, int y, int z);
		int GetChunkWidth();
		int GetChunkHeight();
		int GetChunkLength();
	private:
		void GenerateChunk();
		int chunkLength, chunkWidth, chunkHeight;
		float blockWidth, blockHeight, blockLength;
		glm::vec3 chunkPosition;
};
