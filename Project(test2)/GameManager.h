#pragma once
#include "Player.h"

struct mapsize
{
	int width;
	int height;
};

enum MENU
{
	MENU_PLAY = 1,
	MENU_LEVEL = 2,
	MENU_EXIT = 3
};

enum LEVEL
{
	LEVEL_EASY = 1,
	LEVEL_NORMAL = 2,
	LEVEL_HARD = 3,
	LEVEL_EXIT = 4
};

class GameManager
{
private:
	static GameManager* m_GM_this;
	int m_itrapCount;
	int m_iremaintrap;
	int m_iGamelevel;
	vector<vector<Blockinfo>> m_vecmap;
	mapsize m_mapsize;
public:
	static GameManager* GetInstance()
	{
		if (m_GM_this == NULL)
			m_GM_this = new GameManager;
		return m_GM_this;
	}
	GameManager();
	~GameManager();
	void mapinit(string str);
	void mapload(string str);
	void Blocksetting();
	void trap_setrandom(int count);
	void trap_setcount();
	void GameMain();
	void Level_Select();
	void GamePlay();
	void Input();
	void TrapCheck();
	void EraseCheck();
	void DefaultCheck(int x, int y);
	RESULT WinCheck();
};

