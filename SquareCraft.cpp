#include<iostream>
#include"base/Window.cpp"
#include"game/GameMap.cpp"
#include"game/Events.cpp"
#include"game/Loop.cpp"
#include"game/Terrain.cpp"
#include"entity/Entitys.cpp"
using namespace std;
int main()
{
	Window::Init(1080,720,"SquareCraft");
	GameMap::Init();
	//SDL_ShowCursor(0);
	Terrain::SetSeed(11);
	Terrain::Generate();
	cout << PROGRAM_PATH << endl;
	while(1)
	{
		GameLoop::Loop();
	}
	return 0;
}
