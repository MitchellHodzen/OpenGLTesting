#include "BlockData.h"
#include <iostream>

std::unordered_map<BlockData::BlockName, BlockData*> BlockData::BlockTypes;

BlockData::BlockData(BlockName name, BlockVisibility visibility)
{
	this->name = name;
	this->visibility = visibility;
}
void BlockData::CreateBlock(BlockName name, BlockVisibility visibility)
{
	if (BlockTypes.count(name))
	{
		std::cout<<"Block already exists in BlockTypes map"<<std::endl;
	}
	else
	{
		BlockTypes[name] = new BlockData(name, visibility);
	}
}
