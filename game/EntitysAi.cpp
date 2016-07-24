#pragma once
#include"../game/GameMap.cpp"
#include"../base/Data.cpp"
#include<algorithm>
class EntitysAi
{
	private:
		static void EntityFall(Entity *ent)
		{
			if(ent->_moving_up_or_down)
			{
				ent->_moving_up_or_down=false;
				return;
			}
			double times=10000.0;
			for(int x=ent->X;x<=ent->X+ent->Width;x++)
			{
				for(int y=ent->Y;y<=ent->Y+ent->Height;y++)
					if(GameMap::EntityTools::EntityBlockCoincident(ent,x,y,true))
						times=min(times,GameMap::GetBlock(x,y)->MoveSpeedTimes);
			}
			ent->Y -= (double)GRAVITY*times;
			GameMap::EntityTools::EntityHitTest(ent,_DOWN/*,hitEntity*/);
		}
	public:
		static void MoveEntity(Entity *ent,short direct,bool absolute=false,double dist=-1)
		{
			double times=10000.0,move_dis;
			if(!absolute)
				for(int x=ent->X;x<=ent->X+ent->Width;x++)
				{
					if(ent->Y-(int)ent->Y<=0.1)
						times=min(times,GameMap::GetBlock(x,ent->Y-1)->MoveSpeedTimes);
					for(int y=ent->Y;y<=ent->Y+ent->Height;y++)
						if(GameMap::EntityTools::EntityBlockCoincident(ent,x,y,true))
							times=min(times,GameMap::GetBlock(x,y)->MoveSpeedTimes);
				}
			else
				times=1.0;
			move_dis=(double)times*(double)((dist == -1)?ent->MoveSpeed : dist);
			if(direct==_LEFT)
				ent->X-=move_dis;
			if(direct==_RIGHT)
				ent->X+=move_dis;
			if(direct==_DOWN)
				ent->Y-=move_dis;
			if(direct==_UP)
				ent->Y+=move_dis;
			if(direct==_LEFT || direct==_RIGHT)
			{
				ent->Walking=!GameMap::EntityTools::EntityHitTest(ent,direct);
				ent->Facing=direct;
			}
			else
			{
				ent->_moving_up_or_down=true;
				bool hit=GameMap::EntityTools::EntityHitTest(ent,direct);
				if(direct == _UP && hit)ent->Jump_state=0;
			}
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
				MoveEntity(ent,_UP,true,(ent->Jump_state=fabs(ent->Jump_state)));
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
		static void Swimming(Entity *ent)
		{
			ent->Jumping=false;
			int x=ent->X+ent->Width/2.0;
			Block *b=GameMap::GetBlock(x,ent->Y);
			if(!b->HaveHitBox && b->UpdateType!=BlockUpdateType::Liquid &&	GameMap::GetBlock(x,ent->Y-1.0)->UpdateType == BlockUpdateType::Liquid)
				ent->_swim_up=false;
			if(GameMap::GetBlock(x,ent->Y+1.0)->UpdateType==BlockUpdateType::Liquid)
				ent->_swim_up=true;
			if(ent->_swim_up)
				MoveEntity(ent,_UP,false,ent->MoveSpeed);
		}
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
//			if(GameMap::EntityTools::EntityWillHit(ent,_UP,0.1))
//				return;
			bool swim=false;
			for(int x=ent->X;x<=(ent->X+ent->Width);x++)
			{
				if(GameMap::GetBlock(x,ent->Y-1)->HaveHitBox && (!GameMap::GetBlock(x,ent->Y+1)->HaveHitBox && GameMap::GetBlock(x,ent->Y+1)->UpdateType!=BlockUpdateType::Liquid))//Block on the bottom of ent
					break;
				if(GameMap::GetBlock(x,ent->Y-1)->UpdateType == BlockUpdateType::Liquid && ent->Y-(int)ent->Y <=0.1)//Liquid on the bottom of ent
				{
					swim=true;
					break;
				}
				for(int y=ent->Y-1;y<=(ent->Y+ent->Height);y++)
					if(GameMap::GetBlock(x,y)->UpdateType==BlockUpdateType::Liquid && GameMap::EntityTools::EntityBlockCoincident(ent,x,y,true))
					{
						swim=true;
						break;
					}
			}
			if(!swim)
			{
				if(!GameMap::EntityTools::EntityWillHit(ent,_DOWN,0.1))
					return;
				if(!ent->Jumping)
				{
					ent->Jump_state=-JUMP_FUNC(ent->Jump_height);
					ent->Jumping=true;
				}
			}
			else
				Swimming(ent);
		}
};
