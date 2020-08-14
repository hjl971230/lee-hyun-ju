#pragma once
#include"BitMap.h"
class GameManager
{
private:
	static GameManager* m_this;
	//vector<vector<int>> m_map;
public:
	static inline GameManager* GetInstance()
	{
		if (m_this == NULL) m_this = new GameManager;
		return m_this;
	}
	GameManager();
	~GameManager();
	void GameInit();
};

