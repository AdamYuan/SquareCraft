#pragma once 
#include"../game/GameMap.cpp"
class EntitysDrawer
{
	public:
		static void DrawPlayer(Entity* ent)
		{
			static int rotate_angle=0,direct=2;
			rotate_angle+=direct;
			if(rotate_angle>=30 || rotate_angle<=-30)direct=-direct;
			if(!ent->Walking)rotate_angle=0;
			int sx,sy;
			GetScreenXyFromMapXy(ent->X+ent->TextureX,ent->Y+ent->TextureHeight-1+ent->TextureY,&sx,&sy);
			if(ent->Facing==_STOP && !ent->Walking)
			{
				SDL_Texture *tex=TextureManager::GetEntityTexture(ent);
				Window::Draw(tex,sx,sy,ent->TextureWidth*BLOCK_SIZE+0.5,ent->TextureHeight*BLOCK_SIZE+0.5);
				return;
			}
			int playerheight=ent->TextureHeight*BLOCK_SIZE+0.5;
			int headx=sx+16,heady=sy,headwidth=32,headheight=playerheight/4+0.5;
			int bodyx=sx+22,bodyy=sy+headheight,bodywidth=20,bodyheight=(playerheight-headheight)/2+0.5;
			int legx=sx+24,legy=sy+headheight+bodyheight+0.5,legwidth=16,legheight=bodyheight;
			int armx=sx+24,army=sy+headheight,armwidth=16,armheight=bodyheight;
			SDL_Texture *head=TextureManager::GetGameTexture(ent->Facing==_LEFT?"entitys/player_head_left":"entitys/player_head_right");
			SDL_Texture *body=TextureManager::GetGameTexture("entitys/player_body");
			SDL_Texture *leg=TextureManager::GetGameTexture("entitys/player_leg");
			SDL_Texture *arm=TextureManager::GetGameTexture("entitys/player_arm");
			Window::Draw(arm,armx-2,army,armwidth,armheight,NULL,-rotate_angle,0,-armheight/2);
			Window::Draw(leg,legx+2,legy,legwidth,legheight,NULL,-rotate_angle,0,-legheight/2);
			Window::Draw(head,headx,heady,headwidth,headheight);
			Window::Draw(body,bodyx,bodyy,bodywidth,bodyheight);
			Window::Draw(leg,legx-2,legy,legwidth,legheight,NULL,rotate_angle,0,-legheight/2);
			Window::Draw(arm,armx+2,army,armwidth,armheight,NULL,rotate_angle,0,-armheight/2);
		}
};
