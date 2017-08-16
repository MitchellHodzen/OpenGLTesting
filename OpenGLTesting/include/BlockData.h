#pragma once
#include <unordered_map>
struct BlockData
{
	enum BlockVisibility {VISIBLE, INVISIBLE};
	enum BlockName {DIRT, AIR};
	static std::unordered_map<BlockName, BlockData*> BlockTypes;
	static void CreateBlock(BlockName name, BlockVisibility visibility);
	BlockData(BlockName name, BlockVisibility visibility);
	BlockName name;
	BlockVisibility visibility;
};


