/*
  Copyright (C) 2016 AdamYuan

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
	//int seed;
	//Terrain::SetSeed(seed=(unsigned int)time(0));
	Terrain::SetSeed(8740);
	//cout << seed << endl;
	Terrain::Generate();
	while(1)
	{
		GameLoop::Loop();
	}
	return 0;
}
