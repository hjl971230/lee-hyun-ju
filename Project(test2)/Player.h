#pragma once
#include"header.h"

struct Point
{
	int x;
	int y;
};

class Player
{
private:
	static Player* m_Player_this;
	Point m_Point;
public:
	static Player* GetInstance()
	{
		if (m_Player_this == NULL)
			m_Player_this = new Player;
		return m_Player_this;
	}
	Player();
	~Player();
	void setPoint(int x, int y);
	void move(vector<vector<int>> vecmap);
};

