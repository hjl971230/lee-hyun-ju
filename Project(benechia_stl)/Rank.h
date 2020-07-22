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
	Rankinfo m_Rankinfo;
	Rank* m_FirstRank;
	Rank* m_Next;
	Rank** m_Rankarr;
	int m_icount;
public:
	static Rank* GetInstance()
	{
		if (m_Rank_this == NULL)
			m_Rank_this = new Rank;
		return m_Rank_this;
	}
	void Ranksave(string name, int stage, int score);
	void RankLoad();
	void DataInput(ifstream& load, Rankinfo& info);
	void MakeNext(Rank* tmp);
	void RankSort();
	inline Rank* GetNext() { return m_Next; }
	inline Rankinfo& GetRankinfo() { return m_Rankinfo; }
	void ShowRank();
	void Relese(Rank* Node);
	void deleterank();
};

