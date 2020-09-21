#pragma once
#include <windows.h>
#include<iostream>
#include<time.h>
#include<vector>
#include<list>
#include"resource.h"
using namespace std;

#define UI_Y 480
#define TIMER_X 170
#define MINENUM_X 500
#define BLOCK_COUNT 9
#define START_X 40
#define START_Y 40

enum LEVEL
{
	LEVEL_EASY = 0,
	LEVEL_NORMAL = 1,
	LEVEL_HARD = 2
};

enum MINE_LEVEL
{
	MINE_LEVEL_EASY = 10,
	MINE_LEVEL_NORMAL = 40,
	MINE_LEVEL_HARD = 80
};

enum MAPSIZE_LEVEL
{
	MAPSIZE_LEVEL_EASY = 10,
	MAPSIZE_LEVEL_NORMAL = 30,
	MAPSIZE_LEVEL_HARD = 50,
};