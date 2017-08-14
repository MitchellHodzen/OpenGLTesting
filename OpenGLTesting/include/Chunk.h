#pragma once
#include <vector>
#include "Block.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Vertex.h"
#include "Mesh.h"
class Chunk
{
	public:
		Chunk(glm::vec3 chunkPosition, int width, int height, int length, float blockWidth, float blockHeight, float blockLength);
		~Chunk();
		enum BlockFace {FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM};
		glm::vec3 GetChunkPosition();
		void GenerateChunkMesh();
		Mesh* GetChunkMesh();
		int GetChunkWidth();
		int GetChunkHeight();
		int GetChunkLength();
		int GetChunkSize();
	private:
		BlockVisibility*** chunkData;
		glm::vec3 GetBlockPosition(int x, int y, int z);
		void AddBlockFace(BlockFace face, glm::vec3 blockPosition);
		void GenerateChunk();
		BlockVisibility GetBlockVisibility(int x, int y, int z);
		bool CheckVisibleFaces(int x, int y, int z);
		int chunkLength, chunkWidth, chunkHeight;
		float blockWidth, blockHeight, blockLength;
		glm::vec3 chunkPosition;
		Mesh* chunkMesh;
};
