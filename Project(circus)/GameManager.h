#pragma once
#include"Player.h"
#include"EnemyManager.h"

class GameManager
{
private:
	static GameManager* m_this;
	BitMap m_BitMap;
public:
	static GameManager* GetInstance()
	{
		if (m_this == NULL)
			m_this = new GameManager;
		return m_this;
	}
	GameManager();
	~GameManager();
	void GameInit(HDC, HINSTANCE);
	void GameDraw(HDC);
	void Update(HDC);
	void PlayGame();
};

