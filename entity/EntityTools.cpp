#pragma once
#include"../game/GameMap.cpp"
class EntityTools
{
	public:
		static bool EntityCoincident(Entity *n1,Entity *n2)
		{
			double n1x[5],n1y[5],n2x[5],n2y[5];
			n1x[1]=n1->X,n1y[1]=n1->Y;
			n1x[2]=n1->X,n1y[2]=n1->Y+n1->Height;
			n1x[3]=n1->X+n1->Width,n1y[3]=n1->Y;
			n1x[4]=n1->X+n1->Width,n1y[4]=n1->Y+n1->Height;
			////////////////////////////
			n2x[1]=n2->X,n2y[1]=n2->Y;
			n2x[2]=n2->X,n2y[2]=n2->Y+n2->Height;
			n2x[3]=n2->X+n2->Width,n2y[3]=n2->Y;
			n2x[4]=n2->X+n2->Width,n2y[4]=n2->Y+n2->Height;
			for(int i=1;i<=4;i++)
			{
				if(n1x[i]==n2x[5-i] || n1y[i]==n2y[5-i])return false;
				if(n2x[1]<=n1x[i] && n1x[i]<n2x[3] && n2y[1]<=n1y[i] && n1y[i]<n2y[2])
					return true;
				if(n1x[1]<=n2x[i] && n2x[i]<n1x[3] && n1y[1]<=n2y[i] && n2y[i]<n1y[2])
					return true;
			}
			return false;
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
			for(int i=0;i<GameMap::LoadedEntitys.size();i++)
			{
				//int j=ents.size()-i-1;
				if(GameMap::LoadedEntitys[i]==n)continue;
				if(EntityTools::EntityCoincident(n,GameMap::LoadedEntitys[i]))
					vec.push_back(GameMap::LoadedEntitys[i]);
				//if(EntityCoincident(n,&ents[j]) && i!=j)vec.push_back(&ents[j]);
			}
			return vec;
		}
		static bool EntityHitTest(Entity *ent,string direct,double dist,bool hitEntity=true)
		{
			vector<Entity*> vec = GetCoincidentEntitys(ent);
			bool return_v=false;
			if(direct == _Y)
			{
				double yDirect=dist;
				for(int X=ent->X;X<=(int)(ent->X+ent->Width+0.999);X++)
					if(EntityTools::EntityBlockCoincident(ent,X,yDirect<0 ? ent->Y+yDirect : ent->Y+ent->Height+yDirect))
					{
						ent->Y=(yDirect<0 ? (int)(ent->Y+yDirect) : (int)(ent->Y+yDirect+ent->Height)-(ent->Height-1))-(int)(yDirect/fabs(yDirect));
						return_v=true;
						break;
					}	
				//vec = yDirect<0 ? GetEntitys(1,ent->X,ent->Y+yDirect) : GetEntitys(1,ent->X,ent->Y+ent->Height+yDirect);
				if(hitEntity)
					for(int i=0;i<vec.size();i++)
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
			else if(direct==_X)
			{
				double xDirect=dist;
				for(int Y=ent->Y;Y<=(int)(ent->Y+ent->Height+0.999);Y++)
					if(EntityTools::EntityBlockCoincident(ent,xDirect<0 ? (int)(ent->X+xDirect) : (int)(ent->X+xDirect+ent->Width),Y))
					{
						ent->X=(xDirect<0 ? (int)(ent->X+xDirect) : (int)(ent->X+xDirect+ent->Width)-(ent->Width-1))-(int)(xDirect/fabs(xDirect));
						return_v=true;
						break;
					}
				if(hitEntity)
					for(int i=0;i<vec.size();i++)
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
		static bool EntityWillHit(Entity *ent,string direct,double dist)
		{
			bool rv=false;
			if(direct==_X)
			{
				ent->X+=dist;
				rv=EntityHitTest(ent,_X,dist);
				ent->X-=dist;
			}
			else if(direct==_Y)
			{
				ent->Y+=dist;
				rv=EntityHitTest(ent,_Y,dist);
				ent->Y-=dist;
			}
			return rv;
		}	
};
