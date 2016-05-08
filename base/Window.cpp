//------------------------------------------------------------------------------------------------//
//copied from http://twinklebeardev.blogspot.com/2012/09/lesson-7-taking-advantage-of-classes.html//
//------------------------------------------------------------------------------------------------//
#ifndef WINDOW_H
#define WINDOW_H
#include<iostream>
#include<memory>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
using namespace std;
class Window
{
	private:
		static SDL_Rect mBox;
		static std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> mWindow;
		static std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> mRenderer;
	public:
		static SDL_Window *GetWindow()
		{
			return mWindow.get();
		}
		static SDL_Renderer *GetRenderer()
		{
			return mRenderer.get();
		}
		static void Init(int width,int height,std::string title="Window")
		{
			if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
				throw std::runtime_error("SDL Init Failed");
			if (TTF_Init() == -1)
				throw std::runtime_error("TTF Init Failed");
			Window::mBox.x = 0;
			Window::mBox.y = 0;
			Window::mBox.w = width;
			Window::mBox.h = height;
			Window::mWindow.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, 
						SDL_WINDOWPOS_CENTERED, Window::mBox.w, Window::mBox.h, SDL_WINDOW_RESIZABLE));
			if (Window::mWindow == nullptr)
				throw std::runtime_error("Failed to create window");
			Window::mRenderer.reset(SDL_CreateRenderer(Window::mWindow.get(), -1, 
						SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
			if (Window::mRenderer == nullptr)
				throw std::runtime_error("Failed to create renderer");
		}
		static void Quit()
		{
			SDL_Quit();
			TTF_Quit();
		}	
		static void Draw(SDL_Texture *tex, int x,int y,int width,int height, SDL_Rect *clip = NULL,
				float angle = 0.0, int xPivot = 0, int yPivot = 0,
				SDL_RendererFlip flip = SDL_FLIP_NONE)
		{
			xPivot += width / 2;
			yPivot += height / 2;
			SDL_Rect pos = {
				x,y,width,height
			};
			SDL_Point pivot = {
				xPivot,yPivot
			};
			SDL_RenderCopyEx(Window::mRenderer.get(),tex,clip,&pos,angle,&pivot,flip);
		}
		static SDL_Texture* LoadImage(const std::string file)
		{
			SDL_Texture* tex = nullptr;
			tex = IMG_LoadTexture(Window::mRenderer.get(), file.c_str());
			if (tex == nullptr)
				throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
			return tex;
		}
		static SDL_Texture* RenderText(const std::string message, const std::string &fontFile, 
				SDL_Color color, int fontSize)
		{
			TTF_Font *font = nullptr;
			font = TTF_OpenFont(fontFile.c_str(), fontSize);
			if (font == nullptr)
				throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());
			SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
			SDL_Texture *texture = SDL_CreateTextureFromSurface(Window::mRenderer.get(), surf);
			SDL_FreeSurface(surf);
			TTF_CloseFont(font);
			return texture;
		}

		static void Clear(){
			SDL_RenderClear(Window::mRenderer.get());
		}
		static void Present(){
			SDL_RenderPresent(Window::mRenderer.get());
		}
		static SDL_Rect Box(){
			SDL_GetWindowSize(Window::mWindow.get(), &Window::mBox.w, &Window::mBox.h);
			return Window::mBox;
		}
};
std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> Window::mWindow 
	= std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> Window::mRenderer
	= std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);
SDL_Rect Window::mBox;
#endif
