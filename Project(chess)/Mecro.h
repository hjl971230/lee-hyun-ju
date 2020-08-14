#pragma once
#include<Windows.h>
#include<math.h>
#include<time.h>
#include<vector>
using namespace std;

//맵은 8*8, 플레이어 흑 백 각각, 킹,퀸 1개씩, 룩, 나이트, 비숍 2개씩, 폰 8개씩
//흑 : b, 백 : w
//폰 : 0, 나이트 : 1, 비숍 : 2, 룩 : 3, 퀸 : 4 킹 : 5
//블록 0, 1, 2 두 가지 번갈아서 맵 그리기
#define MAPSIZE_WIDTH 8
#define MAPSIZE_HEIGHT 8
#define PLAYERSIZE 2
#define BLACK 'b'
#define WHITE 'w'

enum CHESSPIECE_NUM
{
	CHESSPIECE_NUM_PAWN = 0,
	CHESSPIECE_NUM_KNIGHT = 1,
	CHESSPIECE_NUM_BISHOP = 2,
	CHESSPIECE_NUM_ROOK = 3,
	CHESSPIECE_NUM_QUEEN = 4,
	CHESSPIECE_NUM_KING = 5
};

enum PLAYER
{
	PLAYER_BLACK = 0,
	PLAYER_WHITE = 1
};