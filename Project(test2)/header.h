#pragma once
#include<iostream>
#include<vector>
#include<time.h>
#include<conio.h>
#include<fstream>
#include<string>
#include<iomanip>
#include<Windows.h>

#define TRAP 9
#define PLAYER 2
#define EMPTY 0

enum KEY
{
	KEY_START = 0,
	KEY_LEFT = 'a',
	KEY_RIGHT = 'd',
	KEY_UP = 'w',
	KEY_DOWN = 's',
	KEY_ENTER = 13,
	KEY_SPACE = 32
};

struct blockinfo
{
	//¢Ë : ºí·Ï ¢Í : ÆøÆÄ ¢Á : ÇÃ·¹ÀÌ¾î ¢Â : ±ê¹ß ¢Ã : Áö·Ú
	string block;
	bool trapflag;
};

using namespace std;