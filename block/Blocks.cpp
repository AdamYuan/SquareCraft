#ifndef BLOCKS_H
#define BLOCKS_H
#include<iostream>
#include"Block.cpp"
using namespace std;
class Blocks
{
	public:
		static Block *GetBlockFromId(int id)
		{
			switch(id)
			{
				case 0:		return air;
				case 1:		return bedrock;
				case 2:		return grass;
				case 3:		return dirt;
				case 4:		return stone;
				case 5:		return wood;
				case 6:		return plank;
				case 7:		return water;
				case 8:		return sand;
				case 9:		return sandstone;
				case 10:	return leaves;
				case 11:	return deadbush;
				case 12:	return cactus;
			}
			return air;
		}
		static Block *air;
		static Block *bedrock;
		static Block *grass;
		static Block *dirt;
		static Block *stone;
		static Block *wood;
		static Block *plank;
		static Block *water;
		static Block *sand;
		static Block *sandstone;
		static Block *leaves;
		static Block *deadbush;
		static Block *cactus;
};
Block *Blocks::air			= new Block(0	,""			,""			,0		,false	);
Block *Blocks::bedrock		= new Block(1	,"Bedrock"	,"bedrock"	,0		,true	);
Block *Blocks::grass		= new Block(2	,"Grass"	,"grass"	,0.5	,true	);
Block *Blocks::dirt			= new Block(3	,"Dirt"		,"dirt"		,0.5	,true	);
Block *Blocks::stone		= new Block(4	,"Stone"	,"stone"	,0.2	,true	);
Block *Blocks::wood			= new Block(5	,"Wood"		,"wood"		,0.3	,true	);
Block *Blocks::plank		= new Block(6	,"Plank"	,"plank"	,0.3	,true	);
Block *Blocks::water		= new Block(7	,"Water"	,"water"	,10		,false	,BlockUpdateType::Liquid,0.5);
Block *Blocks::sand			= new Block(8	,"Sand"		,"sand"		,0.8	,true	,BlockUpdateType::Fall);
Block *Blocks::sandstone	= new Block(9	,"Sandstone","sandstone",0.2	,true	);
Block *Blocks::leaves		= new Block(10	,"Leaves"	,"leaves"	,1		,true	);
Block *Blocks::deadbush		= new Block(11	,"Deadbush"	,"deadbush"	,1		,false	,BlockUpdateType::RemoveIfHang);
Block *Blocks::cactus		= new Block(12	,"Cactus"	,"cactus"	,0.5	,true	,BlockUpdateType::RemoveIfHang);
#endif
