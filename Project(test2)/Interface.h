#pragma once
#include"Draw.h"

class Interface : public Draw
{
private:
	static Interface* m_Interface_this;
public:
	Interface();
	~Interface();
	static Interface* GetInstance()
	{
		if (m_Interface_this == NULL)
			m_Interface_this = new Interface;
		return m_Interface_this;
	}
	void MainMenu();
	void selectLevel();
	void GameDraw(int width, int height);
	void GameResult(RESULT res, int width, int height);
	void vecmapDraw(vector<vector< Blockinfo>> map);
	void info(int& mine, int& count, int width, int height);
};

