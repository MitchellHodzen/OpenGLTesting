#pragma once
#include <vector>
#include "BlockTypes.h"

class Chunk
{
	public:
		Chunk(int width, int height, int length);
		Block*** chunkData;
	private:
		void GenerateChunk();
		int chunkLength;
		int chunkWidth;
		int chunkHeight;
};
