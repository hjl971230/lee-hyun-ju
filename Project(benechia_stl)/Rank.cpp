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
	//deleterank();
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
//void Rank::deleterank()
//{
//	for (int i = 0; i < m_icount; i++)
//	{
//		if (m_Rankarr[i] != NULL)
//		{
//			delete m_Rankarr[i];
//			m_Rankarr[i] = NULL;
//		}
//	}
//	if (m_Rankarr != NULL)
//		delete[] m_Rankarr;
//	m_FirstRank = NULL;
//	m_Next = NULL;
//	m_Rankarr = NULL;
//}

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
	int count = 0;
	Rankinfo tmp;
	ifstream load;
	load.open("Rank.txt");
	if (load.is_open())
	{
		while (!load.eof())
		{
			DataInput(load, tmp);
			m_Ranklist.push_back(tmp);
			count++;
		}
	}
	m_icount = count;
	load.close();
	//m_Ranklist.sort();
	RankSort(m_Ranklist.begin(), m_Ranklist.end());
}

void Rank::DataInput(ifstream& load, Rankinfo& info)
{
	load >> info.Name;
	load >> info.stage;
	load >> info.score;
}

void Rank::RankSort(list<Rankinfo>::iterator begin, list<Rankinfo>::iterator end)
{
	Rankinfo tmp;
	list<Rankinfo>::iterator next = begin;
	list<Rankinfo>::iterator forward_end = end;
	next++;
	end--;
	for (begin; begin != forward_end; begin++)
	{
		for (next; next != end; next++)
		{
			if ((*begin).score < (*next).score)
			{
				tmp = (*begin);
				(*begin) = (*next);
				(*next) = tmp;
			}
			else if ((*begin).score == (*next).score)
			{
				if ((*begin).stage < (*next).stage)
				{
					tmp = (*begin);
					(*begin) = (*next);
					(*next) = tmp;
				}
			}
		}
	}
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
void Rank::Relese(Rank* Node)
{
	if (Node == NULL)
		return;
	Relese(Node->GetNext());
	delete Node;
	Node = NULL;
}