#pragma once
#include"Mecro.h"
#include"MapDraw.h"

struct Rankinfo
{
	string Name;
	int stage;
	int score;
};

class Rank
{
private:
	static Rank* m_Rank_this;
public:
	static Rank* GetInstance()
	{
		if (m_Rank_this == NULL)
			m_Rank_this = new Rank;
		return m_Rank_this;
	}
};

