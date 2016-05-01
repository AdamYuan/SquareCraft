#pragma once
#include<iostream>
#include<algorithm>
#include<cmath>
#include<map>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include"../base/Window.cpp"
#include"../base/Texture.cpp"
#include"../base/Data.cpp" 
#include"../block/Block.cpp"
#include"../block/Blocks.cpp"
#include"../entity/Entitys.cpp"
using namespace std;
class GameMap
{
	private:	
		static Block *gmap[MAP_WIDTH+1][MAP_HEIGHT+1];
		static vector<Entity> ents;
		static void drawBlock(int x,int y,Block* block)
		{
			int sx,sy;
			GetScreenXyFromMapXy(x,y,&sx,&sy);
			if(sx <= -BLOCK_SIZE || sx >= ScreenW)
				return;
			if(sy <= -BLOCK_SIZE || sy >= ScreenH)
				return;
			SDL_Texture *tex=TextureManager::GetBlockTexture(block);
			Window::Draw(tex,sx,sy,BLOCK_SIZE,BLOCK_SIZE);
			if(DestroyBlockState == 0 || x!=SelectedX || y!=SelectedY)return;
			SDL_Texture *des_tex=TextureManager::GetGameTexture(DESTROY_TEXTURE(DestroyBlockState));
			Window::Draw(des_tex,sx,sy,BLOCK_SIZE,BLOCK_SIZE);
		}
		static void drawEntity(Entity *ent)
		{
			int sx,sy;
			GetScreenXyFromMapXy(ent->X+ent->TextureX,ent->Y+ent->TextureHeight-1+ent->TextureY,&sx,&sy);
			if(sx <= -BLOCK_SIZE-ent->TextureWidth*BLOCK_SIZE || sx >= ScreenW+ent->TextureWidth*BLOCK_SIZE)
				return;
			if(sy <= -BLOCK_SIZE-ent->TextureHeight*BLOCK_SIZE || sy >= ScreenH+ent->TextureHeight*BLOCK_SIZE)
				return;
			SDL_Texture *tex=TextureManager::GetEntityTexture(ent);
			Window::Draw(tex,sx,sy,ent->TextureWidth*BLOCK_SIZE,ent->TextureHeight*BLOCK_SIZE);
		}
		static void drawPlayerHealth()
		{
			SDL_Texture *health=TextureManager::GetGameTexture(HEART_TEXTURE);
			SDL_Texture *health_bg=TextureManager::GetGameTexture(HEART_BG_TEXTURE);
			for(int i=0;i<Player.HealthMax;i++)
			{
				Window::Draw(health_bg,i*16,0,16,16);
				if(i<Player.Health)
					Window::Draw(health,i*16,0,16,16);
			}
		}
	public:
#include"../entity/EntitysAi.cpp"
#include"../entity/EntityTools.cpp"
#include"../block/BlocksUpdate.cpp"
		static int SelectedX,SelectedY,ScreenW,ScreenH;
		static double DestroyBlockState;
		static vector<Entity*> LoadedEntitys;
		static EntityPlayer Player;
		//
		///////////////BASE
		//
		static void Init()
		{
			std::uninitialized_fill(&gmap[0][0],&gmap[MAP_WIDTH][MAP_HEIGHT],Blocks::air);
			Player.X=1,Player.Y=70;
		}
		static void Quit()
		{
			std::uninitialized_fill(&gmap[0][0],&gmap[MAP_WIDTH][MAP_HEIGHT],nullptr);
		}
		static bool CanChangeBlock(int x=SelectedX,int y=SelectedY)
		{
			if(x < 1 || x > MAP_WIDTH)return false;
			if(y < 1 || y > MAP_HEIGHT)return false;
			return	GetBlock(x , y) ->HaveHitBox ||
				GetBlock(x-1,y) ->HaveHitBox||
				GetBlock(x+1,y) ->HaveHitBox||
				GetBlock(x,y-1) ->HaveHitBox||
				GetBlock(x,y+1) ->HaveHitBox; 
		}
		static void RefreshScreenSize()
		{
			SDL_GetWindowSize(Window::GetWindow(),&ScreenW,&ScreenH);
		}
		static void ShowBackground()
		{
			Window::Draw(TextureManager::GetGameTexture(BG_TEXTURE),0,0,ScreenW,ScreenH);
		}
		static void ShowGui()
		{
			drawPlayerHealth();
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
			int cx=ScreenW/2-BLOCK_SIZE/2;
			int cy=ScreenH/2-BLOCK_SIZE/2;
			sx+=(int)((Player.X-1)*BLOCK_SIZE)-cx;
			sy+=(int)(((MAP_HEIGHT-Player.Y+1)-1)*BLOCK_SIZE)-cy;
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
			double cx=ScreenW/2-BLOCK_SIZE/2;
			double cy=ScreenH/2-BLOCK_SIZE/2;
			(*sx)=cx-(Player.X-bx)*BLOCK_SIZE;
			(*sy)=cy-(MAP_HEIGHT-Player.Y+1-by)*BLOCK_SIZE+0.5;
		}
		static void ShowMap()
		{
			double bxs,bys,bxe,bye;
			GetMapXyFromScreenXy(0,0,&bxs,&bys);
			GetMapXyFromScreenXy(ScreenW+BLOCK_SIZE+1,ScreenH+BLOCK_SIZE+1,&bxe,&bye);
			for(int bx=bxs;bx<=bxe;bx++)
				for(int by=0;by<=MAP_HEIGHT;by++)
				{
					BlocksUpdate::UpdateBlock(bx,by);
					if(GetBlock(bx,by)!=Blocks::air)
						drawBlock(bx,by,gmap[bx][by]);
				}
			UpdateLoadedEntity();
			for (int i = 0; i < LoadedEntitys.size();i++)
			{
				EntitysAi::EntityDo(LoadedEntitys[i]);
				drawEntity(LoadedEntitys[i]);
			}
			EntitysAi::EntityDo(&Player);
			drawEntity(&Player);

			cout << Player.Y << endl;
		}
		//
		///////////////BLOCK
		//
		static void SetBlock(Block *block,int x=SelectedX,int y=SelectedY)
		{
			if(x < 1 || x > MAP_WIDTH)return;
			if(y < 1 || y > MAP_HEIGHT)return;
			gmap[x][y]=block;
		}
		static Block *GetBlock(int x=SelectedX,int y=SelectedY)
		{
			if(x < 1 || x > MAP_WIDTH)return Blocks::air;
			if(y < 1 || y > MAP_HEIGHT)return Blocks::air;
			return gmap[x][y];
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
			ents.push_back(ent);
			return &ents[ents.size()-1];
		}	
		static void UpdateLoadedEntity()
		{
			double x=Player.X,y=Player.Y,d_level=ENTITYLOAD_LIMIT;
			vector<Entity*> vec;
			d_level=1/d_level;
			x=(int)(x*d_level)/d_level;
			y=(int)(y*d_level)/d_level;
			for(int i=0;i<ents.size();i++)
			{
				double ex=(int)(ents[i].X*d_level)/d_level;
				double ey=(int)(ents[i].Y*d_level)/d_level;
				if((ex<=x && x<ex+ents[i].Width) && (ey<=y && y<ey+ents[i].Height))
					vec.push_back(&ents[i]);
			}
			LoadedEntitys=vec;
		}
		static vector<Entity*> GetEntitys(double d_level,double x,double y)
		{
			vector<Entity*> vec;
			d_level=1/d_level;
			x=(int)(x*d_level)/d_level;
			y=(int)(y*d_level)/d_level;
			for(int i=0;i<LoadedEntitys.size();i++)
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
			vector<Entity>::iterator it = find(ents.begin(),ents.end(),*ent);
			ents.erase(it);
		}
};
//
//GameMap
//
Block *GameMap::gmap[MAP_WIDTH+1][MAP_HEIGHT+1];
vector<Entity> GameMap::ents;
vector<Entity*> GameMap::LoadedEntitys;
int GameMap::SelectedX=1,GameMap::SelectedY=1,GameMap::ScreenW=100,GameMap::ScreenH=100;
double GameMap::DestroyBlockState=0;
EntityPlayer GameMap::Player = EntityPlayer();
//
//EntitysAi
//
bool GameMap::EntitysAi::jumping = false;
double GameMap::EntitysAi::jump_state=0;
int GameMap::EntitysAi::jump_delay=0;
