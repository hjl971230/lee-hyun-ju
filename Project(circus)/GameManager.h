#pragma once
#include"Player.h"

class GameManager
{
private:
	static GameManager* m_this;
public:
	static GameManager* GetInstance()
	{
		if (m_this == NULL)
			m_this = new GameManager;
		return m_this;
	}
};

