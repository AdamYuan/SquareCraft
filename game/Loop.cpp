#ifndef LOOP_H
#define LOOP_H
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<SDL2/SDL.h>
#include"../base/Window.cpp"
#include"GameMap.cpp"
#include"Events.cpp"
using namespace std;
class GameLoop
{
	private:
		static SDL_Event evt;
	public:
		static void Loop()
		{
			static int mx,my;
			SDL_GetMouseState(&mx,&my);
			GameMap::RefreshScreenSize();
			GameMap::ShowBackground();
			GameMap::ShowMap();
			while(SDL_PollEvent(&evt))
				GameEvents::ReciveEvent(evt);
			GameEvents::AfterReciveEvent();
			GameMap::GetSelectedXyFromMouseXy(mx,my);
			GameMap::SelectBlock(GameMap::SelectedX,GameMap::SelectedY);
			GameMap::ShowGui();
			Window::Present();
		}
};
SDL_Event GameLoop::evt;
#endif
