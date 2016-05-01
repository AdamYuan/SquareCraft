#ifndef TEXTURE_H
#define TEXTURE_H
#include<iostream>
#include<map>
#include"Window.cpp"
#include"../block/Block.cpp"
#include"../block/Blocks.cpp"
#include"../entity/Entitys.cpp"
using namespace std;
class TextureManager
{
	private:
		static map<string,SDL_Texture*> textures;
		static map<string,SDL_Texture*>::iterator it;
	public:
		static string GetBlockTexturePath(Block *b)
		{ 
			return "/home/adamyuan/code/SquareCraftSDL/texture/blocks/" + b->TextureName + ".png";
		}
		static string GetGameTexturePath(string name)
		{
			return "/home/adamyuan/code/SquareCraftSDL/texture/" + name + ".png";
		}
		static string GetEntityTexturePath(Entity *ent)
		{
			return "/home/adamyuan/code/SquareCraftSDL/texture/entitys/" + ent->TextureName + ".png";
		}
		static SDL_Texture* GetBlockTexture (Block *b)
		{	
			string bl=b->TextureName;
			string s=TextureManager::GetBlockTexturePath(b);
			TextureManager::it=TextureManager::textures.find(bl);
			if(TextureManager::it==TextureManager::textures.end())
			{
				TextureManager::textures[bl]=Window::LoadImage(s);
			}
			return TextureManager::textures[bl];
		}
		static SDL_Texture* GetEntityTexture (Entity *ent)
		{
			//try
			//{
			string bl=ent->TextureName;
			string s=TextureManager::GetEntityTexturePath(ent);
			TextureManager::it=TextureManager::textures.find(bl);
			if(TextureManager::it==TextureManager::textures.end())
			{
				TextureManager::textures[bl]=Window::LoadImage(s);
			}
			return TextureManager::textures[bl];

			/*}
			  catch(const std::runtime_error &e)
			  {
			  return nullptr;
			  }*/
		}
		static SDL_Texture* GetGameTexture (string textureName)
		{
			string s=TextureManager::GetGameTexturePath(textureName);
			TextureManager::it=TextureManager::textures.find(textureName);
			if(TextureManager::it==TextureManager::textures.end())
			{
				TextureManager::textures[textureName]=Window::LoadImage(s);
			}
			return TextureManager::textures[textureName];
		}
};
map<string,SDL_Texture*> TextureManager::textures;
map<string,SDL_Texture*>::iterator TextureManager::it;
#endif
