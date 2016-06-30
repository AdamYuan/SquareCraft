#pragma once
#ifdef WINDOWS
#include <direct.h>
#include <windows.h>
#else
#include <unistd.h>
#endif
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
#define PROGRAM_PATH		(GetProgramPath())
#define _LEFT				-1
#define _RIGHT				0
#define _UP					1
#define _DOWN				2
#define _STOP				3
#define MAP_WIDTH			131072
#define MAP_HEIGHT			128
#define TERRAIN_BASEHEIGHT	70
#define BLOCK_SIZE			64
#define MOVE_SPEED			0.2
#define GRAVITY				0.4
#define ENTITYLOAD_LIMIT	512
#define ENTITY_MAX			1024
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
static string _PATH="";
string GetFilePath (const string str)
{
	size_t found;
	found=str.find_last_of("/\\");
	return str.substr(0,found);
}
string GetProgramPath()
{
	if(_PATH=="")
	{
#ifdef WINDOWS
		char result[ MAX_PATH ];
		_PATH = GetFilePath(std::string( result, GetModuleFileName( NULL, result, MAX_PATH ) ));
#else
		char result[32767];
		ssize_t count = readlink( "/proc/self/exe", result,32767 );
		_PATH = GetFilePath(std::string( result, (count > 0) ? count : 0 ));
#endif
	}
	return _PATH;
}
