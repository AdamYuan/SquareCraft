#ifndef BIOMEDESERT_H
#define BIOMEDESERT_H
#include<iostream>
#include"../base/Random.cpp"
#include"Biome.cpp"
#include"BiomeTools.cpp"
using namespace std;
class BiomeDesert : public Biome
{
	public:
		void FillX(int x,double height,int water_height,double first,double last,int width,int index)
		{
			BiomeTools::ChangeHeight(&height,1.7,first,last,width,index);
			height=(int)height;
			if(height < water_height)height=water_height;
			int stone_height = Random(1,4);
			int r=Random(1,8);
			if(r==1)
				GameMap::SetBlock(Blocks::deadbush,x,height+1);
			else if(r==2)
			{
				int c_height=Random(2,5);
				for(int i=1;i<=c_height;i++)
					GameMap::SetBlock(Blocks::cactus,x,height+i);
			}
			BiomeTools::NormalFillX(x,height,water_height,stone_height,Blocks::sand,Blocks::sandstone);
		}
};
#endif
