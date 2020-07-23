#include "WordManager.h"

WordManager* WordManager::m_WordManager_this = NULL;

WordManager::WordManager()
{
	m_iwordcount = 0;
	m_ispeed = 500;
	m_bdropflag = true;
}

WordManager::~WordManager()
{
}

void WordManager::Wordload()
{
	Word tmp;
	string str;
	ifstream load;
	int count = 0;
	load.open("Word.txt");
	if (load.is_open())
	{
		load >> m_iwordcount;
		while (!load.eof())
		{
			load >> str;
			tmp.Setstr(str);
			m_Wordlist.push_back(tmp);
		}
		load.close();
	}
}

bool WordManager::WordDrop()
{
	if (m_ispeed <= 200)
		m_ispeed = 200;
	if (clock() - m_iOldDropClock >= m_ispeed)
	{
		if (m_bdropflag)
		{
			for (list<Word>::iterator iter = m_Wordlist.begin(); iter != m_Wordlist.end(); iter++)
			{
				if ((*iter).Getstrflag())
					(*iter).drop();
				if ((*iter).Gety() >= Y - 2)
				{
					(*iter).Die();
					return false;
				}
			}
		}
		m_iOldDropClock = clock();
	}
	return true;
}

void WordManager::WordDie()
{
	for (list<Word>::iterator iter = m_Wordlist.begin(); iter != m_Wordlist.end(); iter++)
	{
		(*iter).Die();
	}
}

void WordManager::Reversehideflag()
{
	for (list<Word>::iterator iter = m_Wordlist.begin(); iter != m_Wordlist.end(); iter++)
	{
		if ((*iter).Gethideflag())
			(*iter).Sethideflag(false);
		else
			(*iter).Sethideflag(true);
	}
}

void WordManager::WordClear()
{
	for (list<Word>::iterator iter = m_Wordlist.begin(); iter != m_Wordlist.end(); iter++)
		(*iter).Die();
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
	rnum = rand() % m_iwordcount;
	list<Word>::iterator iter = m_Wordlist.begin();
	for(int i = 0; i < rnum; i++)
		iter++;
	if (m_bdropflag)
	{
		if (!(*iter).Getstrflag())
			(*iter).Live();
		if ((*iter).GetItemflag())
			(*iter).MakeItem();
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