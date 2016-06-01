#ifndef BLOCK_H
#define BLOCK_H
#include<iostream>
#include"../base/Window.cpp"
#include<SDL2/SDL.h>
#include"BlockUpdateType.cpp"
using namespace std;
class Block
{
	public:
		bool HaveHitBox=true;
		int Id=0;
		double DestroySpeed=0.1;
		string Name="",TextureName="";
		BlockUpdateType UpdateType;
		Block(int id=0,string name="",string textureName="",double destroySpeed=0.1,bool haveHitBox=true,BlockUpdateType updateType=BlockUpdateType::None)
		{
			Id=id;
			Name=name;
			TextureName=textureName;
			DestroySpeed=destroySpeed;
			HaveHitBox=haveHitBox;
			UpdateType=updateType;
		}
};
#endif











