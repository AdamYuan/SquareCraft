#include<SDL2/SDL.h>
#include"../base/Window.cpp"
#include"../base/Texture.cpp"
#include"../base/Data.cpp"
class Gui
{
	private:
		static void drawPlayerHealth()
		{
			SDL_Texture *health=TextureManager::GetGameTexture(HEART_TEXTURE);
			SDL_Texture *health_bg=TextureManager::GetGameTexture(HEART_BG_TEXTURE);
			for(int i=0;i<Player->HealthMax;i++)
			{
				Window::Draw(health_bg,i*16,0,16,16);
				if(i<Player->Health)
					Window::Draw(health,i*16,0,16,16);
			}
		}
		static void drawItemBar()
		{
			for(int i=1;i<=9;i++)
			{
				Window::Draw(TextureManager::GetBlockTexture(Blocks::GetBlockFromId(i)),
						Window::ScreenW/2-32*9/2+32*i,Window::ScreenH-32,32,32);
			}
		}
	public:
		static void ShowGui()
		{
			drawPlayerHealth();
			drawItemBar();
		}
};
