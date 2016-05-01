#pragma once
#include"../game/GameMap.cpp"
#include"../base/Data.cpp"
class EntitysAi
{
	private:
		static double jump_state;
		static bool jumping;
		static int jump_delay;
		static void EntityFall(Entity *ent)
		{
			ent->Y -= GRAVITY;
			GameMap::EntityTools::EntityHitTest(ent,_Y,-GRAVITY);
		}
		static void FallingBlockDo(Entity *ent)
		{
			if((int)ent->Y == ent->Y && GameMap::GetBlock(ent->X,ent->Y-1)->HaveHitBox)
			{
				GameMap::SetBlock(GetBlockFromFallingBlock(ent),ent->X,ent->Y);
				GameMap::RemoveEntity(ent);
			}
		}
		static void PlayerDo(Entity *ent)
		{
			if(jump_state != 0 && jump_state < JUMP_HEIGHT-0.05)
			{
				double swp = jump_state;
				if(swp>0)
				{
					ent->Y-=swp;
					jump_state+=JUMP_FUNC(JUMP_HEIGHT-swp);
				}
				ent->Y+=(jump_state=fabs(jump_state));
				if(GameMap::EntityTools::EntityHitTest(ent,_Y,0.1))jump_state=0;
			}
			else 
			{
				if(++jump_delay >= 10)
				{
					jump_delay=0;
					jumping=false;
				}
				jump_state=0;
				EntityFall(ent);
			}
			return;
		}
	public:
		static void EntityDo(Entity *ent)
		{
			if(*ent==Entitys::player)
			{
				PlayerDo(ent);
				return;
			}
			if(*ent==Entitys::fallingSand)
				FallingBlockDo(ent);
			EntityFall(ent);
		}
		static void PlayerJump(Entity *ent=&GameMap::Player)
		{
			if(!GameMap::EntityTools::EntityWillHit(ent,_Y,-0.01) || GameMap::EntityTools::EntityWillHit(ent,_Y,0.01))
				return;
			if(!jumping)
			{
				jump_state=-JUMP_FUNC(JUMP_HEIGHT);
				jumping=true;
			}
		}
};

