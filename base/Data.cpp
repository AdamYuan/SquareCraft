#pragma once
#include<SDL2/SDL.h>
#include<iostream>
#include<string>
#include<sstream>
using namespace std;
//keys
#define LEFT_KEY			SDLK_a
#define RIGHT_KEY			SDLK_d
#define UP_KEY				SDLK_w
#define DOWN_KEY			SDLK_s
#define SPACE_KEY			SDLK_SPACE
//datas
#define _X					"X"
#define _Y					"Y"
#define MAP_WIDTH			131072
#define MAP_HEIGHT			128
#define TERRAIN_BASEHEIGHT	70
#define BLOCK_SIZE			64
#define MOVE_SPEED			0.2
#define GRAVITY				0.3
#define JUMP_HEIGHT			4.05
#define ENTITYLOAD_LIMIT	1024
#define JUMP_FUNC(x)		((x)/5.0)
//textures
#define SELECTOR_TEXTURE	"select"
#define BG_TEXTURE			"bg"
#define HEART_TEXTURE		"heart"
#define HEART_BG_TEXTURE	"heart_bg"
string DESTROY_TEXTURE(double n)
{
	stringstream ss;
	if(n >= 10)n=10;
	if(n-(int)n==0)
		ss<<"destroy_stage_"<<(n-1);
	else
		ss<<"destroy_stage_"<<(int)n;
	return ss.str();
}
