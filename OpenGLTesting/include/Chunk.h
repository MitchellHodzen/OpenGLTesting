#pragma once
#include <vector>
#include "BlockTypes.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Chunk
{
	public:
		Chunk(glm::vec3 chunkPosition, int width, int height, int length, float blockWidth, float blockHeight, float blockLength);
		~Chunk();
		Block*** chunkData;
		glm::vec3 GetBlockPosition(int x, int y, int z);
		void GenerateModelMatricies();
		std::vector<glm::mat4>* GetModelMatricies();
		int GetChunkWidth();
		int GetChunkHeight();
		int GetChunkLength();
		int GetChunkSize();
	private:
		void GenerateChunk();
		Block GetBlockType(int x, int y, int z);
		bool CheckBlockVisible(int x, int y, int z);
		int chunkLength, chunkWidth, chunkHeight;
		float blockWidth, blockHeight, blockLength;
		glm::vec3 chunkPosition;
		//glm::mat4* modelMatricies;
		std::vector<glm::mat4>* modelMatricies;
};
