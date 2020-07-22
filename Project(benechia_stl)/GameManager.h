#pragma once
#include"Interface.h"
#include"WordManager.h"
#include"Rank.h"

class GameManager
{
private:
	static GameManager* m_GameManger_this;
	int m_iLife;
	int m_iScore;
	string m_strName;
	int m_istage;
	int m_icreatspeed;
	bool m_bitemflag;
	int m_iItemclock;
	int m_ifailedclock;
public:
	static GameManager* GetInstance()
	{
		if (m_GameManger_this == NULL)
			m_GameManger_this = new GameManager;
		return m_GameManger_this;
	}
	GameManager();
	~GameManager();
	void GameBoot();
	void GameStart();
	void NameInput();
	void PlayGame();
	bool InputCheck(string str, ITEM& i);
	void Gameover();
};

