#pragma once
#include"../game/GameMap.cpp"
class EntityTools
{
	public:
		static bool EntityCoincident(Entity *n1,Entity *n2)
		{
			return (n1->X + n1->Width  > n2->X &&
					n2->X + n2->Width  > n1->X &&
					n1->Y + n1->Height > n2->Y &&
					n2->Y + n2->Height > n1->Y);
		}
		static bool EntityBlockCoincident(Entity *n1,int bx,int by,bool allowNoHitboxBlock=false)
		{
			if(!GameMap::GetBlock(bx,by)->HaveHitBox && !allowNoHitboxBlock)return false;
			Entity bn=Entity(0,1,1);
			bn.X=bx,bn.Y=by;
			return EntityCoincident(n1,&bn);
		}
		static vector<Entity*> GetCoincidentEntitys(Entity *n)
		{
			vector<Entity*> vec;
			for(int i=0;i<(int)GameMap::LoadedEntitys.size();i++)
			{
				//int j=ents.size()-i-1;
				if(GameMap::LoadedEntitys[i]==n)continue;
				if(EntityTools::EntityCoincident(n,GameMap::LoadedEntitys[i]))
					vec.push_back(GameMap::LoadedEntitys[i]);
				//if(EntityCoincident(n,&ents[j]) && i!=j)vec.push_back(&ents[j]);
			}
			return vec;
		}
		static bool EntityHitTest(Entity *ent,short direct,bool hitEntity=true)
		{
			vector<Entity*> vec = GetCoincidentEntitys(ent);
			bool return_v=false;
			if(direct == _UP || direct == _DOWN)
			{
				double yDirect=direct==_UP?1:-1;
				for(int X=ent->X;X<=(int)(ent->X+ent->Width+0.999);X++)
					if(EntityTools::EntityBlockCoincident(ent,X,yDirect<0 ? (int)ent->Y : (int)(ent->Y+ent->Height)))
					{
						ent->Y=(yDirect<0 ? (int)ent->Y+1 : (int)(ent->Y+ent->Height)-ent->Height);
						return_v=true;
						break;
					}	
				//vec = yDirect<0 ? GetEntitys(1,ent->X,ent->Y+yDirect) : GetEntitys(1,ent->X,ent->Y+ent->Height+yDirect);
				if(hitEntity)
				{
					vec=GetCoincidentEntitys(ent);
					for(int i=0;i<(int)vec.size();i++)
					{
						double Y = yDirect<0 ? vec[i]->Y+vec[i]->Height : vec[i]->Y-ent->Height;
						bool b=yDirect<0 ? (ent->Y < Y) && (Y < ent->Y+ent->Height) : (ent->Y > Y) && (Y > ent->Y-ent->Height);
						if(b)
						{
							ent->Y = Y;
							return_v=true;
						}
					}
				}
			}
			else if(direct==_LEFT || direct==_RIGHT)
			{
				double xDirect=direct==_LEFT?-1:1;
				for(int Y=ent->Y;Y<=(int)(ent->Y+ent->Height+0.999);Y++)
					if(EntityTools::EntityBlockCoincident(ent,xDirect<0 ? (int)ent->X : (int)(ent->X+ent->Width),Y))
					{
						ent->X=(xDirect<0 ? (int)ent->X+1 : (int)(ent->X+ent->Width)-ent->Width);
						return_v=true;
						break;
					}
				if(hitEntity)
					for(int i=0;i<(int)vec.size();i++)
					{
						double X = xDirect<0 ? vec[i]->X+vec[i]->Width : vec[i]->X-ent->Width;
						bool b=xDirect<0 ? (ent->X < X) && (X < ent->X+ent->Width) : (ent->X > X) && (X > ent->X-ent->Width);
						if(b)
						{
							ent->X = X;
							return_v=true;
						}
					}
			}
			return return_v;
		}
		static bool EntityWillHit(Entity *ent,short direct,double dist,bool hitEntity=true)
		{
			bool rv=false;
			double tmp;
			if(direct==_LEFT || direct==_RIGHT)
			{
				tmp=ent->X;
				ent->X+=dist*(direct==_LEFT?-1:1);
				rv=EntityHitTest(ent,direct,hitEntity);
				ent->X=tmp;
			}
			else if(direct==_UP || direct==_DOWN)
			{
				tmp=ent->Y;
				ent->Y+=dist*(direct==_DOWN?-1:1);
				rv=EntityHitTest(ent,direct,hitEntity);
				ent->Y=tmp;
			}
			return rv;
		}
};
