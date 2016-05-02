#ifndef TEXTURE_H
#define TEXTURE_H
#include<iostream>
#include<map>
#include<unistd.h>
#include"Window.cpp"
#include"Data.cpp"
#include"../block/Block.cpp"
#include"../block/Blocks.cpp"
#include"../entity/Entitys.cpp"
using namespace std;
class TextureManager
{
	private:
		static map<string,SDL_Texture*> textures;
		static map<string,SDL_Texture*>::iterator it;
		static string GetBlockTexturePath(Block *b)
		{
			return PROGRAM_PATH + "/texture/blocks/" + b->TextureName + ".png";
		}
		static string GetEntityTexturePath(Entity *ent)
		{
			return PROGRAM_PATH + "/texture/entitys/" + ent->TextureName + ".png";
		}
		static string GetGameTexturePath(string name)
		{
			return PROGRAM_PATH + "/texture/" + name + ".png";
		}
		static SDL_Texture* GetTexture (string name,string path)
		{
			TextureManager::it=TextureManager::textures.find(name);
			if(TextureManager::it==TextureManager::textures.end())
			{
				TextureManager::textures[name]=Window::LoadImage(path);
			}
			return TextureManager::textures[name];
		}
	public:
		static SDL_Texture* GetBlockTexture (Block *b)
		{	
			return GetTexture(b->TextureName,GetBlockTexturePath(b));
		}
		static SDL_Texture* GetEntityTexture (Entity *ent)
		{
			return GetTexture(ent->TextureName,GetEntityTexturePath(ent));
		}
		static SDL_Texture* GetGameTexture (string textureName)
		{
			return GetTexture(textureName,GetGameTexturePath(textureName));
		}
};
map<string,SDL_Texture*> TextureManager::textures;
map<string,SDL_Texture*>::iterator TextureManager::it;
#endif
