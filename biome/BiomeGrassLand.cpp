#pragma once
#include"Biome.cpp"
#include"BiomeTools.cpp"
#include<iostream>
using namespace std;
class BiomeGrassLand : public Biome
{
	public:
		void FillX(int x,double height,int water_height,double first,double last,int width,int index)
		{
			BiomeTools::ChangeHeight(&height,0.5,first,last,width,index);
			int dirt_height = Random(1,4);
			if(height>=water_height)
			{
				if(Random(1,5)==5)GameMap::SetBlock(Blocks::leaves,x,height+1);
				else if(Random(1,20)==10)BiomeTools::SetTree(x,height);
			}
			BiomeTools::NormalFillX(x,height,water_height,dirt_height,Blocks::grass,Blocks::dirt);
		}
};
