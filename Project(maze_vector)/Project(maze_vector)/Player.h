#pragma once
#include"mecro.h"

class Player
{
	Point CharacterPoint;//1p x,y
	int m_iLastObjectindex;//1p 처음 이동하려는 위치 정보를 NULL로 저장
public:
	Player();
	~Player();
	inline void setCharacterPoint(int x, int y) { CharacterPoint.x = x; CharacterPoint.y = y;}
	inline void setLastObjectindex(int i) { m_iLastObjectindex = i;}
	bool Move(vector<vector<int>>& v, Point Exit_Potal[], bool &resetflag);
	bool PlayerMoveCheck(char ch, vector<vector<int>>& v, Point Exit_Potal[], bool &resetflag);
	bool MovePlayer(vector<vector<int>>& v, Point Exit_Potal[], bool &resetflag);
	bool MoveCheck(vector<vector<int>>& v, Point Exit_Potal[], bool &resetflag);
};

