#pragma once
#include"mecro.h"

class Player
{
	Point CharacterPoint;//1p x,y
	int m_iLastObjectindex;//1p ó�� �̵��Ϸ��� ��ġ ������ NULL�� ����
public:
	Player();
	~Player();
	inline void setCharacterPoint(int x, int y) { CharacterPoint.x = x; CharacterPoint.y = y;}
	bool Move(vector<vector<int>>& v, Point Exit_Potal[]);
	bool PlayerMoveCheck(char ch, vector<vector<int>>& v, Point Exit_Potal[]);
	bool MovePlayer(vector<vector<int>>& v, Point Exit_Potal[]);
	bool MoveCheck(vector<vector<int>>& v, Point Exit_Potal[]);
};

