#pragma once
#include"Interface.h"

class Player
{
private:
	static Player* m_Player_this;
	Point m_Point;
	string m_stricon;
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
	void move(char ch, int Width, int Height);
	inline Point getPoint() { return m_Point; }
	inline string geticon() { return m_stricon; }
};

