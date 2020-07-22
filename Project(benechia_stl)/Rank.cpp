#include "Rank.h"

Rank* Rank::m_Rank_this = NULL;

Rank::Rank()
{
	m_FirstRank = NULL;
	m_Next = NULL;
	m_Rankarr = NULL;
}
Rank::~Rank()
{
	deleterank();
}
void Rank::MakeNext(Rank* tmp)
{
	if (m_Next == NULL)
	{
		m_Next = tmp;
		return;
	}
	m_Next->MakeNext(tmp);
}
void Rank::deleterank()
{
	for (int i = 0; i < m_icount; i++)
	{
		if (m_Rankarr[i] != NULL)
		{
			delete m_Rankarr[i];
			m_Rankarr[i] = NULL;
		}
	}
	if (m_Rankarr != NULL)
		delete[] m_Rankarr;
	m_FirstRank = NULL;
	m_Next = NULL;
	m_Rankarr = NULL;
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
	deleterank();
	int count = 0;
	Rank* tmp = NULL;
	ifstream load;
	load.open("Rank.txt");
	if (load.is_open())
	{
		while (!load.eof())
		{
			tmp = new Rank;
			DataInput(load, tmp->m_Rankinfo);
			if (m_FirstRank == NULL)
				m_FirstRank = tmp;
			else
				m_FirstRank->MakeNext(tmp);
			count++;
		}
	}
	m_icount = count;
	load.close();
	tmp = m_FirstRank;
	m_Rankarr = new Rank * [count];
	for (int i = 0; i < m_icount; i++)
	{
		if (m_Rankarr[i] != NULL)
			m_Rankarr[i] = NULL;
		m_Rankarr[i] = tmp;
		if (tmp->GetNext() != NULL)
			tmp = tmp->GetNext();
	}
	RankSort();
}
void Rank::DataInput(ifstream& load, Rankinfo& info)
{
	load >> info.Name;
	load >> info.stage;
	load >> info.score;
}
void Rank::RankSort()
{
	Rank* tmp = NULL;
	for (int i = 0; i < m_icount - 1; i++)
	{
		for (int j = i + 1; j < m_icount; j++)
		{
			if (m_Rankarr[i]->GetRankinfo().score < m_Rankarr[j]->GetRankinfo().score)
			{
				tmp = m_Rankarr[i];
				m_Rankarr[i] = m_Rankarr[j];
				m_Rankarr[j] = tmp;
			}
			else if (m_Rankarr[i]->GetRankinfo().score == m_Rankarr[j]->GetRankinfo().score)
			{
				if (m_Rankarr[i]->GetRankinfo().stage < m_Rankarr[j]->GetRankinfo().stage)
				{
					tmp = m_Rankarr[i];
					m_Rankarr[i] = m_Rankarr[j];
					m_Rankarr[j] = tmp;
				}
			}
		}
	}
}
void Rank::ShowRank()
{
	int y = 0;
	SKY_BLUE
		m_DrawManager.BoxDraw(0, 0, X, Y);
	ORIGINAL
		BLUE
		m_DrawManager.BoxDraw(X, 3, 20, 5);
	m_DrawManager.DrawMidText("Ranking", X, 5);
	for (int i = 2; i < X * 2 - 2; i++)
		m_DrawManager.TextDraw("=", i, 8);
	m_DrawManager.DrawPoint("Name\t\t\tScore\t\t\tStage", X / 3, 11);
	for (int i = 0; i < MAX_RANK; i++)
	{
		m_DrawManager.DrawPoint(to_string(i + 1) + ". \t\t"
			+ m_Rankarr[i]->GetRankinfo().Name + "\t\t\t"
			+ to_string(m_Rankarr[i]->GetRankinfo().score) + "\t\t\t"
			+ to_string(m_Rankarr[i]->GetRankinfo().stage), X / 5, 14 + y);
		y += 2;
	}
	ORIGINAL
		char ch = getch();
}
void Rank::Relese(Rank* Node)
{
	if (Node == NULL)
		return;
	Relese(Node->GetNext());
	delete Node;
	Node = NULL;
}