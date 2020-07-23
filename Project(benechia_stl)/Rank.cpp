#include "Rank.h"

Rank* Rank::m_Rank_this = NULL;

Rank::Rank()
{
	m_icount = 0;
}

Rank::~Rank()
{
}

void Rank::Ranksave(string name, int stage, int score)
{
	ofstream save;
	save.open("Rank.txt", ios::app);
	if (save.is_open())
	{
		save << name << " " << stage << " " << score << endl;
	}
	save.close();
}

void Rank::RankLoad()
{
	if(!m_Ranklist.empty())
		m_Ranklist.clear();
	Rankinfo tmp;
	ifstream load;
	load.open("Rank.txt");
	if (load.is_open())
	{
		while (!load.eof())
		{
			DataInput(load, tmp);
			m_Ranklist.push_back(tmp);
			m_icount++;
		}
	}
	load.close();
	m_Ranklist.sort(Rank_sort());
}

void Rank::DataInput(ifstream& load, Rankinfo& info)
{
	load >> info.Name;
	load >> info.stage;
	load >> info.score;
}

void Rank::ShowRank()
{
	int i = 0, y = 0;
	list<Rankinfo>::iterator iter = m_Ranklist.begin();
	SKY_BLUE
		MapDraw::GetInstance()->BoxDraw(0, 0, X, Y);
	ORIGINAL
		BLUE
		MapDraw::GetInstance()->BoxDraw(X, 3, 20, 5);
	MapDraw::GetInstance()->DrawMidText("Ranking", X, 5);
	for (int i = 2; i < X * 2 - 2; i++)
		MapDraw::GetInstance()->TextDraw("=", i, 8);
	MapDraw::GetInstance()->DrawPoint("Name\t\t\tScore\t\t\tStage", X / 3, 11);
	for(int i = 0; i < MAX_RANK; i++)
	{
		MapDraw::GetInstance()->DrawPoint(to_string(i + 1) + ". \t\t"
			+ (*iter).Name + "\t\t\t"
			+ to_string((*iter).score) + "\t\t\t"
			+ to_string((*iter).stage), X / 5, 14 + y);
		y += 2;
		iter++;
	}
	ORIGINAL
		char ch = getch();
}