#pragma once
#include<Windows.h>
#include<math.h>
#include<time.h>
#include<vector>
using namespace std;

//���� 8*8, �÷��̾� �� �� ����, ŷ,�� 1����, ��, ����Ʈ, ��� 2����, �� 8����
//�� : b, �� : w
//�� : 0, ����Ʈ : 1, ��� : 2, �� : 3, �� : 4 ŷ : 5
//��� 0, 1, 2 �� ���� �����Ƽ� �� �׸���
#define MAPSIZE_WIDTH 8
#define MAPSIZE_HEIGHT 8
#define BMPSIZE_WIDTH 125
#define BMPSIZE_HEIGHT 125
#define PLAYERSIZE 2
#define LINESIZE 2
#define CHESSPIECE_SIZE 16
#define BLACK 'b'
#define WHITE 'w'
#define MAP_X 400
#define MAP_Y 100

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