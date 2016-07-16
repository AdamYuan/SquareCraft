#pragma once
#include"Entity.cpp"
#include"../base/Window.cpp"
#include"../base/Texture.cpp"
class EntityPlayer : public Entity
{
	public:
		EntityPlayer(int id=2)
		{
			Id=id;
			HealthMax=20;
			Health=HealthMax;
			TextureName="player";
			TextureWidth=1,TextureHeight=1.9;
			Width=0.5,Height=1.9;
			TextureX=-0.25,TextureY=0;
			Jump_height=4.05;	
		}
};
