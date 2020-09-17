#pragma once
#include<Windows.h>
#include<math.h>
#include<time.h>
#include<vector>
#include<list>

#define MOVESPEED 20
#define JUMPSPEED 20
#define GRAVITY 10
#define OBJECT_MAX 10
#define PLAYER_MOTION_SIZE 3
#define PLAYER_WIN_MOTION_SIZE 2

using namespace std;

enum BOX_SIZE
{
	BOX_SIZE_X = 300,
	BOX_SIZE_Y = 100
};

enum PLAYER_MOTION
{
	PLAYER_MOTION_STAND = 0,
	PLAYER_MOTION_BACK0 = 0,
	PLAYER_MOTION_BACK1 = 1,
	PLAYER_MOTION_RUN1 = 1,
	PLAYER_MOTION_RUN2 = 2,
	PLAYER_MOTION_JUMP = 2,
};

enum BG_CODE
{
	BG_CODE_BACK = 0,
	BG_CODE_DECO = 1,
	BG_CODE_NORMAL = 2,
	BG_CODE_NORMAL2 = 3
};

enum ENEMY_CODE
{
	ENEMY_CODE_RING = 0,
	ENEMY_CODE_SMALLRING = 1,
	ENEMY_CODE_POT = 2,
	ENEMY_CODE_END = 3
};

enum RING_IMAGE
{
	RING_IMAGE_1 = 0,
	RING_IMAGE_2 = 1
};

enum RING_IMAGE_TYPE
{
	RING_IMAGE_TYPE_ORIGIN = 0,
	RING_IMAGE_TYPE_B = 1,
	RING_IMAGE_TYPE_F = 2
};

enum POT_IMAGE
{
	POT_IMAGE_1 = 0,
	POT_IMAGE_2 = 1
};

enum ITEM_CODE
{
	ITEM_CODE_MONEY = 0
};