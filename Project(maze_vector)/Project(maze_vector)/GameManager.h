#pragma once
#include"mecro.h"
#include"Player.h"

class GameManager
{
	static GameManager* m_this;
	vector<vector<int>> m_vecMap;
	Player P1;
	Point Entry_Potal[POTAL_MAX];
	Point Exit_Potal[POTAL_MAX];
	Point Random_Potal[POTAL_MAX];
public:
	GameManager();
	~GameManager();
	static GameManager* GetInstance()
	{
		if (m_this == NULL)
			m_this = new GameManager;
		return m_this;
	}
	void PlayGame();
	void Init();
	void Mapdraw();
	void Guide();
};

