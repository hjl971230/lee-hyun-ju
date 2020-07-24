#pragma once
#include"header.h"

class GameManager
{
private:
	static GameManager* m_GM_this;
	int m_itrapCount;
	vector<vector<blockinfo>> m_vecmap;
public:
	static GameManager* GetInstance()
	{
		if (m_GM_this == NULL)
			m_GM_this = new GameManager;
		return m_GM_this;
	}
	GameManager();
	~GameManager();
	void mapinit();
	void trap_setrandom();
};

