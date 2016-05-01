#pragma once
#include"Entity.cpp"
#include"../block/Blocks.cpp"
#define GetBlockFromFallingBlock(var) Blocks::GetBlockFromId(var->Data)
class EntityFallingBlock : public Entity
{
	public:
		EntityFallingBlock(Block *b=Blocks::sand,int id=1)
		{
			Id=id;
			SetEntityBlock(this,b);
		}
		static void SetEntityBlock(EntityFallingBlock *e,Block *b)
		{
			e->TextureX=0,e->TextureY=0;
			e->TextureWidth=1,e->TextureHeight=1;
			e->Height=1,e->Width=1;
			e->TextureName = "../blocks/"+b->TextureName;
			e->Name = "Falling"+b->Name;
			e->Data=b->Id;
		}
};
