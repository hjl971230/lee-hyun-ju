#pragma once
#include"MapDraw.h"
class Interface : public MapDraw
{
private:
	int m_istage;
	static Interface* m_interface_this;
public:
	static Interface* GetInstance()
	{
		if (m_interface_this == NULL)
			m_interface_this = new Interface;
		return m_interface_this;
	}
	Interface();
	void GameTitle();
	void InfoDraw(int life, int score, string name);
	void GameScroll();
	void ShowStage(int& stage);
};

