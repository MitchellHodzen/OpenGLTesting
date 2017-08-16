#pragma once
#include "BlockData.h"
struct Block
{
	Block(BlockData::BlockName name);
	Block();
	BlockData* type;
};
