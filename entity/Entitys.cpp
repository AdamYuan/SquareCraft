#pragma once
#include"EntityFallingBlock.cpp"
#include"EntityPlayer.cpp"
class Entitys
{
	public:
		static const EntityFallingBlock	fallingSand;
		static const EntityPlayer			player;
};
const EntityFallingBlock Entitys::fallingSand = EntityFallingBlock(Blocks::sand,1);
const EntityPlayer Entitys::player = EntityPlayer(2);
