#pragma once
#include"../game/GameMap.cpp"
class BlocksUpdate
{
	public:
		static void BlockFall(int x,int y)
		{
			if(GameMap::GetBlock(x,y-1)->HaveHitBox)return;
			Block *b=GameMap::GetBlock(x,y);
			GameMap::SetBlock(Blocks::air,x,y);
			EntityFallingBlock ef=EntityFallingBlock(b);
			ef.X=x,ef.Y=y;
			GameMap::SetEntity(ef);
		}
		static void BlockRemoveIfHang(int x,int y)
		{
			if(!GameMap::GetBlock(x,y-1)->HaveHitBox)
				GameMap::SetBlock(Blocks::air,x,y);
		}
		static void UpdateBlock(int x,int y)
		{
			Block *b=GameMap::GetBlock(x,y);
			if(b->UpdateType==BlockUpdateType::None)return;
			switch(b->UpdateType)
			{
				case BlockUpdateType::Fall:
					BlockFall(x,y);
					break;
				case BlockUpdateType::RemoveIfHang:
					BlockRemoveIfHang(x,y);
					break;
			}
		}
};
