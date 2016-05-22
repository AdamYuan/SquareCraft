#pragma once
#include"../game/GameMap.cpp"
#include"../base/Data.cpp"
class EntitysAi
{
	private:
		static void EntityFall(Entity *ent)
		{
			ent->Y -= GRAVITY;
			//bool hitEntity=(ent->TextureName != Entitys::player.TextureName);
			GameMap::EntityTools::EntityHitTest(ent,_DOWN/*,hitEntity*/);
		}
		static void FallingBlockDo(Entity *ent)
		{
			if((int)ent->Y == ent->Y && GameMap::GetBlock(ent->X,ent->Y-1)->HaveHitBox)
			{
				GameMap::SetBlock(GetBlockFromFallingBlock(ent),ent->X,ent->Y);
				GameMap::RemoveEntity(ent);
			}
		}
		static void Jumping(Entity *ent)
		{
			if(ent->Jump_state != 0 && ent->Jump_state < ent->Jump_height-0.05)
			{
				double swp = ent->Jump_state;
				if(swp>0)
				{
					ent->Y-=swp;
					ent->Jump_state+=JUMP_FUNC(ent->Jump_height-swp);
				}
				ent->Y+=(ent->Jump_state=fabs(ent->Jump_state));
				if(GameMap::EntityTools::EntityHitTest(ent,_UP))ent->Jump_state=0;
			}
			else 
			{
				if(++ent->Jump_delay >= 10)
				{
					ent->Jump_delay=0;
					ent->Jumping=false;
				}
				ent->Jump_state=0;
				EntityFall(ent);
			}
			return;
		}
	public:
		static void EntityDo(Entity *ent)
		{
			if(ent->Jumping)
			{
				Jumping(ent);
				return;
			}
			if(ent->Id==Entitys::fallingSand.Id)
				FallingBlockDo(ent);
			EntityFall(ent);
		}
		static void EntityJump(Entity *ent)
		{
			if(!GameMap::EntityTools::EntityWillHit(ent,_DOWN,0.01) || GameMap::EntityTools::EntityWillHit(ent,_UP,0.01))
				return;
			if(!ent->Jumping)
			{
				ent->Jump_state=-JUMP_FUNC(ent->Jump_height);
				ent->Jumping=true;
			}
		}
};

