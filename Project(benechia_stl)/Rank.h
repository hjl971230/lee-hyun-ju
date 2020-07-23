#pragma once
#include"Mecro.h"
#include"MapDraw.h"

struct Rankinfo
{
	string Name;
	int stage;
	int score;
};

struct Rank_less
{
	bool operator()(Rankinfo left, Rankinfo right)
	{
		if (left.score == right.score)
			return (left.stage > right.stage);
		else return (left.score > right.score);
	}
};

struct Rank_less
{
	bool operator()(Rankinfo left, Rankinfo right)
	{
		if (left.score == right.score)
			return (left.stage > right.stage);
		else return (left.score > right.score);
	}
};

class Rank
{
private:
	static Rank* m_Rank_this;
	int m_icount;
	list<Rankinfo> m_Ranklist;
public:
	Rank();
	~Rank();
	static Rank* GetInstance()
	{
		if (m_Rank_this == NULL)
			m_Rank_this = new Rank;
		return m_Rank_this;
	}
	void Ranksave(string name, int stage, int score);
	void RankLoad();
	void DataInput(ifstream& load, Rankinfo& info);
	void ShowRank();
};

