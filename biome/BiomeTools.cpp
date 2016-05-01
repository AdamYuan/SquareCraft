#pragma once
#include"../game/GameMap.cpp"
class BiomeTools
{
	public:
		static inline void NormalFillX(int x,int height,int water_height,int dirt_height,Block *surface,Block *dirt)
		{
			if(height>=water_height)
				GameMap::SetBlock(surface,x,height);
			else
				GameMap::SetBlock(dirt,x,height);
			for(int j=water_height;j>height;j--)
			{
				GameMap::SetBlock(Blocks::water,x,j);
			}
			for(int j=height-1;j>=height-dirt_height;j--)
			{
				GameMap::SetBlock(dirt,x,j);
			}
			for(int j=height-dirt_height-1;j>=2;j--)
			{
				GameMap::SetBlock(Blocks::stone,x,j);
			}
			GameMap::SetBlock(Blocks::bedrock,x,1);
		}
		static inline void SetTree(int x,int y)
		{
			int tree_height=Random(4,7);
			for(int i=1;i<=tree_height;i++)
			{
				GameMap::SetBlock(Blocks::wood,x,y+i);
			}
			if(GameMap::GetBlock(x-1,y+tree_height)==Blocks::air)
				GameMap::SetBlock(Blocks::leaves,x-1,y+tree_height);
			if(GameMap::GetBlock(x+1,y+tree_height)==Blocks::air)
				GameMap::SetBlock(Blocks::leaves,x+1,y+tree_height);
			if(GameMap::GetBlock(x-1,y+tree_height-1)==Blocks::air)
				GameMap::SetBlock(Blocks::leaves,x-1,y+tree_height-1);
			if(GameMap::GetBlock(x-2,y+tree_height-1)==Blocks::air)
				GameMap::SetBlock(Blocks::leaves,x-2,y+tree_height-1);
			if(GameMap::GetBlock(x+1,y+tree_height-1)==Blocks::air)
				GameMap::SetBlock(Blocks::leaves,x+1,y+tree_height-1);
			if(GameMap::GetBlock(x+2,y+tree_height-1)==Blocks::air)
				GameMap::SetBlock(Blocks::leaves,x+2,y+tree_height-1);
			if(GameMap::GetBlock(x-1,y+tree_height-2)==Blocks::air)
				GameMap::SetBlock(Blocks::leaves,x-1,y+tree_height-2);
			if(GameMap::GetBlock(x-2,y+tree_height-2)==Blocks::air)
				GameMap::SetBlock(Blocks::leaves,x-2,y+tree_height-2);
			if(GameMap::GetBlock(x+1,y+tree_height-2)==Blocks::air)
				GameMap::SetBlock(Blocks::leaves,x+1,y+tree_height-2);
			if(GameMap::GetBlock(x+2,y+tree_height-2)==Blocks::air)
				GameMap::SetBlock(Blocks::leaves,x+2,y+tree_height-2);
		}
		static void ChangeHeight(double *height,double times,double first_height,double last_height,int width,int index)
		{
			*height-=(first_height+(last_height-first_height)/width*index);
			*height *= times;
			*height+=(first_height+(last_height-first_height)/width*index);
			*height=(int)*height;
		}
};
