#ifndef TERRAIN_H
#define TERRAIN_H
#include<iostream>
#include<cmath>
#include"../base/PerlinNoise.cpp"
#include"../block/Blocks.cpp"
#include"../game/GameMap.cpp"
#include"../base/Tools.cpp"
#include"../biome/Biomes.cpp"
using namespace std;
class Terrain
{
	private:
		static PerlinNoise pn; 
	public:
		static int WaterHeight;
		static void SetSeed(int seed)
		{
			srand(seed);
			pn.SetRandomSeed(seed);
			WaterHeight=Random(TERRAIN_BASEHEIGHT-5,TERRAIN_BASEHEIGHT+5);
		}	
		static double GetHeight(int bx)
		{
			double r=pn.GetHeight(pn.RandomSeed(),bx);
			return r*10+TERRAIN_BASEHEIGHT;
		}
		static void Generate()
		{
			int i=1,biome_x,currentBiomeWidth;
			Biome *currentBiome;
			while(i <= MAP_WIDTH)
			{
				biome_x=i;
				currentBiomeWidth=Random(100,800);
				currentBiome=Biomes::GetRandomBiome();
				for(i=biome_x;i<biome_x+currentBiomeWidth;i++)
				{
					if(i > MAP_WIDTH)
						return;
					currentBiome->FillX(i,GetHeight(i),WaterHeight,GetHeight(biome_x),GetHeight(biome_x+currentBiomeWidth-1),currentBiomeWidth,i-biome_x);
				}
			}
		}
};
PerlinNoise Terrain::pn = PerlinNoise(65536,0.3,1,1,0);
int Terrain::WaterHeight;
#endif
