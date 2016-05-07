#pragma once
#include"Entity.cpp"
class EntityPlayer : public Entity
{
	public:
		EntityPlayer(int id=2)
		{
			Id=id;
			HealthMax=20;
			Health=HealthMax;
			TextureName="player";
			TextureWidth=1,TextureHeight=1.8;
			Width=0.5,Height=1.8;
			TextureX=-0.25,TextureY=0;
		}
};
