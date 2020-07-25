#pragma once
#include<iostream>
#include<vector>
#include<time.h>
#include<conio.h>
#include<fstream>
#include<string>
#include<iomanip>
#include<Windows.h>

using namespace std;

#define WALL 10
#define TRAP 9
#define BOOM 40
#define FLAG 30
#define PLAYER 20
#define EMPTY 0
#define WINDOW_WIDTH 50
#define WINDOW_HEIGHT 50

enum KEY
{
	KEY_START = 0,
	KEY_LEFT = 'a',
	KEY_RIGHT = 'd',
	KEY_UP = 'w',
	KEY_DOWN = 's',
	KEY_ENTER = 13,
	KEY_SPACE = 32,
	KEY_CANCEL = 'z'
};

enum RESULT
{
	RESULT_CLEAR = 1,
	RESULT_BOOM = 2,
	RESULT_PLAY = 3
};

struct Blockinfo
{
	int BlockNum;
	bool hideflag;
	string Blockshape;
};

struct Point
{
	int x;
	int y;
};