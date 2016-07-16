#pragma once
#include<iostream>
#include"../base/Data.cpp"
class Entity
{
	public:
		double Jump_state=0,Jump_height=1.0;
		bool Jumping=false;
		int Jump_delay=0;
		int Id=1,Health=10,HealthMax=10;
		short Facing=_STOP;
		bool Walking=false;
		double X=1,Y=1,TextureX=0,TextureY=0,TextureWidth=1,TextureHeight=1,Width=1,Height=1;
		double Data;
		string Name,TextureName;
		/*Entity()
		  {

		  }*/
		Entity(int id=0,double width=1,double height=1,double TW=1,double TH=1,string name="",string textureName="")
		{
			Id=id,Width=width,Height=height,TextureWidth=TW,TextureHeight=TH,Name=name,TextureName=textureName;
		}
		bool operator== (Entity n)
		{
			return Id==n.Id && TextureName==n.TextureName && X==n.X && Y==n.Y && Width==n.Width && Height==n.Height;
		}
		bool operator!= (Entity n)
		{
			return !(Id==n.Id && TextureName==n.TextureName && X==n.X && Y==n.Y && Width==n.Width && Height==n.Height);
		}
};
