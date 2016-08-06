#pragma once
#include<iostream>
#include<algorithm>
#include<cmath>
#include<map>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include"../base/Texture.cpp"
#include"../base/Data.cpp"
#include"../base/Tools.cpp"
#include"../block/Block.cpp"
#include"../block/Blocks.cpp"
#include"../entity/Entitys.cpp"
using namespace std;
class GameMap
{
	private:
		static Block *MapBlocks[MAP_WIDTH+1][MAP_HEIGHT+1];
		static vector<Entity> MapEntitys;
		static void drawBlock(int x,int y,Block* block)
		{
			int sx,sy;
			GetScreenXyFromMapXy(x,y,&sx,&sy);
			if(sx <= -BLOCK_SIZE || sx >= Window::ScreenW)
				return;
			if(sy <= -BLOCK_SIZE || sy >= Window::ScreenH)
				return;
			SDL_Texture *tex=TextureManager::GetBlockTexture(block);
			Window::Draw(tex,sx,sy,BLOCK_SIZE,BLOCK_SIZE);
			if(DestroyBlockState == 0 || x!=SelectedX || y!=SelectedY)return;
			SDL_Texture *des_tex=TextureManager::GetGameTexture(DESTROY_TEXTURE(DestroyBlockState));
			Window::Draw(des_tex,sx,sy,BLOCK_SIZE,BLOCK_SIZE);
		}
	public:
#include"EntitysAi.cpp"
#include"EntitysDrawer.cpp"
#include"EntityTools.cpp"
#include"Gui.cpp"
#include"../block/BlocksUpdate.cpp"
		static int SelectedX,SelectedY;
		static double DestroyBlockState;
		static vector<Entity*> LoadedEntitys;
		static Entity* Player;
		//
		///////////////BASE
		//
		static void Init()
		{
			MapEntitys.reserve(ENTITY_MAX*(sizeof(Entity)));
			std::uninitialized_fill(&MapBlocks[0][0],&MapBlocks[MAP_WIDTH][MAP_HEIGHT],Blocks::air);
			Player=SetEntity(EntityPlayer());
			Player->X=MAP_WIDTH/2,Player->Y=MAP_HEIGHT;
		}
		static void Quit()
		{
			std::uninitialized_fill(&MapBlocks[0][0],&MapBlocks[MAP_WIDTH][MAP_HEIGHT],nullptr);
		}
		static bool CanChangeBlock(int x=SelectedX,int y=SelectedY)
		{
			if(x < 1 || x > MAP_WIDTH)return false;
			if(y < 1 || y > MAP_HEIGHT)return false;
			return (!EntityTools::EntityBlockCoincident(Player,x,y,true)) && 
				(GetBlock(x , y) ->HaveHitBox ||
				 GetBlock(x-1,y) ->HaveHitBox||
				 GetBlock(x+1,y) ->HaveHitBox||
				 GetBlock(x,y-1) ->HaveHitBox||
				 GetBlock(x,y+1) ->HaveHitBox); 
		}
		static void ShowBackground()
		{
			Window::Draw(TextureManager::GetGameTexture(BG_TEXTURE),0,0,Window::ScreenW,Window::ScreenH);
		}
		static void GetSelectedXyFromMouseXy(int mx,int my)
		{
			double sx,sy;
			GetMapXyFromScreenXy(mx,my,&sx,&sy);
			if(sx != SelectedX || sy != SelectedY)
				DestroyBlockState=0;
			SelectedX=sx;
			SelectedY=sy;
		}
		static void GetMapXyFromScreenXy(int sx,int sy,double *bx,double *by)
		{
			int cx=Window::ScreenW/2-BLOCK_SIZE/2;
			int cy=Window::ScreenH/2-BLOCK_SIZE/2;
			sx+=(int)((Player->X-1)*BLOCK_SIZE)-cx;
			sy+=(int)(((MAP_HEIGHT-Player->Y+1)-1)*BLOCK_SIZE)-cy;
			(*bx)=(sx/BLOCK_SIZE)+1;
			(*by)=MAP_HEIGHT-(sy/BLOCK_SIZE);
			if((*bx)<1)(*bx)=1;
			if((*by)<1)(*by)=1;
			if((*bx)>MAP_WIDTH)(*bx)=MAP_WIDTH;
			if((*by)>MAP_HEIGHT)(*by)=MAP_HEIGHT;
		}
		static void GetScreenXyFromMapXy(double bx,double by,int *sx,int *sy)
		{
			by=MAP_HEIGHT-by+1;
			double cx=Window::ScreenW/2-BLOCK_SIZE/2;
			double cy=Window::ScreenH/2-BLOCK_SIZE/2;
			(*sx)=cx-(Player->X-bx)*BLOCK_SIZE;
			(*sy)=cy-(MAP_HEIGHT-Player->Y+1-by)*BLOCK_SIZE+0.5;
		}
		static void UpdateDisplayMap()
		{
			double bxs,bys,bxe,bye;
			GetMapXyFromScreenXy(0,0,&bxs,&bys);
			GetMapXyFromScreenXy(Window::ScreenW+BLOCK_SIZE+1,Window::ScreenH+BLOCK_SIZE+1,&bxe,&bye);
			for(int bx=bxs;bx<=bxe;bx++)
				for(int by=0;by<=MAP_HEIGHT;by++)
				{
					BlocksUpdate::UpdateBlock(bx,by);
					if(GetBlock(bx,by)!=Blocks::air)
						drawBlock(bx,by,MapBlocks[bx][by]);
				}
			UpdateLoadedEntity();
			for (int i = LoadedEntitys.size()-1; i >= 0;i--)
			{
				EntitysAi::EntityDo(LoadedEntitys[i]);
				EntitysDrawer::DrawEntity(LoadedEntitys[i]);
			}
			//cout << MapEntitys.size() << endl;
		}
		//
		///////////////BLOCK
		//
		static void SetBlock(Block *block,int x=SelectedX,int y=SelectedY)
		{
			if(x < 1 || x > MAP_WIDTH)return;
			if(y < 1 || y > MAP_HEIGHT)return;
			MapBlocks[x][y]=block;
		}
		static Block *GetBlock(int x=SelectedX,int y=SelectedY)
		{
			if(x < 1 || x > MAP_WIDTH)return Blocks::air;
			if(y < 1 || y > MAP_HEIGHT)return Blocks::air;
			return MapBlocks[x][y];
		}		
		static void SelectBlock(int x,int y)
		{
			int sx,sy;
			GetScreenXyFromMapXy(x,y,&sx,&sy);
			if(CanChangeBlock(x,y))Window::Draw(TextureManager::GetGameTexture(SELECTOR_TEXTURE),sx,sy,BLOCK_SIZE,BLOCK_SIZE);
		}	
		//
		///////////////ENTITY
		//
		static Entity *SetEntity(Entity ent)
		{
			MapEntitys.push_back(ent);
			return &MapEntitys[MapEntitys.size()-1];
		}	
		static void UpdateLoadedEntity()
		{
			LoadedEntitys.clear();
			double x=Player->X,d_level=ENTITYLOAD_LIMIT;
			for(int i=0;i<(int)MapEntitys.size();i++)
			{
				double ex=(int)(MapEntitys[i].X*d_level)/d_level;
				//double ey=(int)(MapEntitys[i].Y*d_level)/d_level;
				if(x-d_level <= ex && ex <= x+d_level)
					LoadedEntitys.push_back(&MapEntitys[i]);
			}
		}
		static vector<Entity*> GetEntitys(double d_level,double x,double y)
		{
			vector<Entity*> vec;
			d_level=1/d_level;
			x=(int)(x*d_level)/d_level;
			y=(int)(y*d_level)/d_level;
			for(int i=0;i<(int)LoadedEntitys.size();i++)
			{
				double ex=(int)(LoadedEntitys[i]->X*d_level)/d_level;
				double ey=(int)(LoadedEntitys[i]->Y*d_level)/d_level;
				if((ex<=x && x<ex+LoadedEntitys[i]->Width) && (ey<=y && y<ey+LoadedEntitys[i]->Height))
					vec.push_back(LoadedEntitys[i]);
			}
			return vec;
		}
		static void RemoveEntity(Entity *ent)
		{
			vector<Entity*>::iterator itp = find(LoadedEntitys.begin(),LoadedEntitys.end(),ent);
			LoadedEntitys.erase(itp);
			vector<Entity>::iterator it = find(MapEntitys.begin(),MapEntitys.end(),*ent);
			MapEntitys.erase(it);
		}
};
//
//GameMap
//
Block *GameMap::MapBlocks[MAP_WIDTH+1][MAP_HEIGHT+1];
vector<Entity> GameMap::MapEntitys;
vector<Entity*> GameMap::LoadedEntitys;
int GameMap::SelectedX=1,GameMap::SelectedY=1;
double GameMap::DestroyBlockState=0;
Entity *GameMap::Player = new EntityPlayer();
