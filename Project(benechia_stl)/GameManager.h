#pragma once
#include"Interface.h"
#include"WordManager.h"
#include"Rank.h"

class GameManager
{
private:
	static GameManager* m_GameManger_this;
public:
	static GameManager* GetInstance()
	{
		if (m_GameManger_this == NULL)
			m_GameManger_this = new GameManager;
		return m_GameManger_this;
	}
	GameManager();
	~GameManager();
};

