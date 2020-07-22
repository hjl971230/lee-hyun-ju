#include "WordManager.h"

WordManager* WordManager::m_WordManager_this = NULL;

WordManager::WordManager()
{
	m_iwordcount = 0;
	m_Word = NULL;
	m_ispeed = 500;
	m_bdropflag = true;
}
WordManager::~WordManager()
{
	//Relese(m_Word);
	if (m_Word != NULL)
	{
		delete[] m_Word;
		m_Word = NULL;
	}
}
void WordManager::Wordload()
{
	string str;
	ifstream load;
	int count = 0;
	load.open("Word.txt");
	if (load.is_open())
	{
		load >> m_iwordcount;
		while (count < m_iwordcount)
		{
			load >> str;
			if (m_Word == NULL)
				m_Word = new Word[m_iwordcount];
			m_Word[count].Setstr(str);
			count++;
		}
		load.close();
	}
}
void WordManager::Relese(Word* Node)
{
	if (Node == NULL)
		return;
	Relese(Node->GetNext());
	delete Node;
	Node = NULL;
}
bool WordManager::WordDrop()
{
	if (m_ispeed <= 200)
		m_ispeed = 200;
	if (clock() - m_iOldDropClock >= m_ispeed)
	{
		if (m_bdropflag)
		{
			for (int i = 0; i < m_iwordcount; i++)
			{
				if (m_Word[i].Getstrflag())
					m_Word[i].drop();
				if (m_Word[i].Gety() >= Y - 2)
				{
					m_Word[i].Die();
					return false;
				}
			}
		}
		m_iOldDropClock = clock();
	}
	return true;
}
void WordManager::Reversehideflag()
{
	for (int i = 0; i < m_iwordcount; i++)
	{
		if (m_Word[i].Gethideflag())
			m_Word[i].Sethideflag(false);
		else
			m_Word[i].Sethideflag(true);
	}
}
void WordManager::WordClear()
{
	for (int i = 0; i < m_iwordcount; i++)
		m_Word[i].Die();
}
void WordManager::SpeedUpDown(bool b)
{
	if (b)
		m_ispeed += 50;
	else
		m_ispeed -= 50;
}
void WordManager::WordCreate()
{
	int rnum = 0;
	rnum = rand() % 75; //WordManager ÀÌµ¿
	if (m_bdropflag)
	{
		if (!m_Word[rnum].Getstrflag())
			m_Word[rnum].Live();
		if (m_Word[rnum].GetItemflag())
			m_Word[rnum].MakeItem();
	}
}
void WordManager::ItemOn(ITEM item, int& score, int stage)
{
	switch (item)
	{
	case ITEM_BLIND:
		Reversehideflag();
		break;
	case ITEM_CLEAR:
		WordClear();
		score += 200 * stage;
		break;
	case ITEM_SPEEDUP:
		SpeedUpDown(true);
		break;
	case ITEM_SPEEDDOWN:
		SpeedUpDown(false);
		break;
	case ITEM_STOP:
		Stop(false);
		break;
	default:
		break;
	}
}
void WordManager::ItemOff(ITEM item)
{
	switch (item)
	{
	case ITEM_BLIND:
		Reversehideflag();
		break;
	case ITEM_CLEAR:
		break;
	case ITEM_SPEEDUP:
		SpeedUpDown(false);
		break;
	case ITEM_SPEEDDOWN:
		SpeedUpDown(true);
		break;
	case ITEM_STOP:
		Stop(true);
		break;
	default:
		break;
	}
}