#ifndef BIOMES_H
#define BIOMES_H
#include"BiomeForest.cpp"
#include"BiomeDesert.cpp"
#include"BiomeGrassLand.cpp"
#include"BiomeMForest.cpp"
#include<iostream>
class Biomes
{
	public:
		static Biome *GetRandomBiome()
		{
			int s=Random(1,4);
			switch(s)
			{
				case 1:		return forest;
				case 2:		return mforest;
				case 3:		return desert;
				case 4:		return grassland;
			}
			return forest;
		}
		static BiomeForest *forest;
		static BiomeMForest *mforest;
		static BiomeDesert *desert;
		static BiomeGrassLand *grassland;
};
BiomeForest *Biomes::forest = new BiomeForest();
BiomeMForest *Biomes::mforest = new BiomeMForest();
BiomeDesert *Biomes::desert = new BiomeDesert();
BiomeGrassLand *Biomes::grassland = new BiomeGrassLand();
#endif
