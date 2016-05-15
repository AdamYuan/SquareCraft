#ifndef EVENTS_H
#define EVENTS_H
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<SDL2/SDL.h>
#include"../base/Window.cpp"
#include"../base/Data.cpp"
#include"GameMap.cpp"
#define CHANGEBLOCK_DELAY 15
using namespace std;
class GameEvents
{
	private:
		static int left_down,right_down,up_down,down_down,space_down,mouse_state,chblock_delay;
	public:
		static void EventKeyUp(SDL_Event evt)
		{
			switch(evt.key.keysym.sym)
			{
				case RIGHT_KEY:
					right_down=0;
					break;
				case LEFT_KEY:
					left_down=0;
					break;
				case DOWN_KEY:
					down_down=0;
					break;
				case UP_KEY:
					up_down=0;
					break;
				case SPACE_KEY:
					space_down=0;
					break;
			}
		}
		static void EventKeyDown(SDL_Event evt)
		{
			switch(evt.key.keysym.sym)
			{
				case RIGHT_KEY:
					right_down=1;
					break;
				case LEFT_KEY:
					left_down=1;
					break;
				case DOWN_KEY:
					down_down=1;
					break;
				case UP_KEY:
					up_down=1;
					break;
				case SPACE_KEY:
					space_down=1;
					break;
			}
		}
		static void ReciveEvent(SDL_Event evt)
		{
			switch(evt.type)
			{
				case SDL_KEYDOWN:
					EventKeyDown(evt);
					break;
				case SDL_KEYUP:
					EventKeyUp(evt);
					break;
				case SDL_MOUSEBUTTONDOWN:
					mouse_state = evt.button.button;
					break;
				case SDL_MOUSEBUTTONUP:
					GameMap::DestroyBlockState=0;
					chblock_delay=CHANGEBLOCK_DELAY;
					mouse_state = -1;
					break;
				case SDL_QUIT:
					GameMap::Quit();
					Window::Quit();
					exit(0);
			}
		}
		static void AfterReciveEvent()
		{
			GameMap::Player.Walking=false;
			/*if(down_down)
			  {
			  GameMap::Player.Y -= MOVE_SPEED;
			  GameMap::EntityHitTest(&GameMap::Player,_Y,-MOVE_SPEED);
			  }*/
			if(up_down)
			{
				GameMap::Player.Y += MOVE_SPEED+GRAVITY;
				GameMap::EntityTools::EntityHitTest(&GameMap::Player,_UP);
			}
			if(right_down)
			{
				GameMap::Player.X += MOVE_SPEED;
				GameMap::Player.Facing = _RIGHT;
				GameMap::Player.Walking=!GameMap::EntityTools::EntityHitTest(&GameMap::Player,_RIGHT);
			}
			if(left_down)
			{
				GameMap::Player.X -= MOVE_SPEED;
				GameMap::Player.Facing = _LEFT;
				GameMap::Player.Walking=!GameMap::EntityTools::EntityHitTest(&GameMap::Player,_LEFT);
			}
			if(space_down)
				GameMap::EntitysAi::PlayerJump();
			//
			if(mouse_state == SDL_BUTTON_LEFT)
			{
				if(GameMap::CanChangeBlock() && (GameMap::DestroyBlockState += GameMap::GetBlock()->DestroySpeed)>=10)
				{
					GameMap::SetBlock(Blocks::air);
					GameMap::DestroyBlockState = 0;
				}
			}
			else if(mouse_state == SDL_BUTTON_RIGHT)
			{
				if(++chblock_delay>=CHANGEBLOCK_DELAY)
				{
					chblock_delay=0;
					if(GameMap::CanChangeBlock() && !GameMap::GetBlock()->HaveHitBox)
						GameMap::SetBlock(Blocks::sand);
				}
			}
		}
};
int GameEvents::left_down,GameEvents::right_down,GameEvents::up_down,GameEvents::down_down,GameEvents::space_down,GameEvents::mouse_state=-1,GameEvents::chblock_delay=CHANGEBLOCK_DELAY;
#endif
