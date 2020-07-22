#include "GameManager.h"

GameManager* GameManager::m_GameManger_this = NULL;

GameManager::GameManager()
{
	m_iLife = MAX_LIFE;
	m_iScore = 0;
	m_strName = "? ? ?";
	m_istage = 1;
	m_icreatspeed = 3000;
	m_iItemclock = 0;
	m_ifailedclock = 0;
	m_bitemflag = false;
}

GameManager::~GameManager()
{
	delete MapDraw::GetInstance();
	delete Interface::GetInstance();	
	delete WordManager::GetInstance();
	delete Rank::GetInstance();
}

void GameManager::GameBoot()
{
	int select = 0;
	while (true)
	{
		WordManager::GetInstance()->Wordload();
		Interface::GetInstance()->GameTitle();
		Interface::GetInstance()->InfoDraw(m_iLife, m_iScore, m_strName);
		select = Interface::GetInstance()->MenuSelectCursor(3, 3, 26, 14);
		switch (select)
		{
		case 1:
			GameStart();
			break;
		case 2:
			Rank::GetInstance()->RankLoad();
			Rank::GetInstance()->ShowRank();
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}
void GameManager::GameStart()
{
	SKY_BLUE
		Interface::GetInstance()->BoxDraw(0, 0, X, Y);
	Interface::GetInstance()->BoxDraw(X, Y - 11, 20, 5);
	Interface::GetInstance()->DrawMidText("skip : s", X, Y - 9);
	ORIGINAL
		Interface::GetInstance()->InfoDraw(m_iLife, m_iScore, m_strName);
	Interface::GetInstance()->GameScroll();
	NameInput();
	PlayGame();
}
void GameManager::NameInput()
{
	int i = 0;
	string str = "\0";
	char tmp = '\0';
	char ch[MAX_NAME + 1] = { '\0' };
	SKY_BLUE
		Interface::GetInstance()->BoxDraw(0, 0, X, Y);
	Interface::GetInstance()->DrawMidText("이름 입력 : ", X, Y - 14);
	Interface::GetInstance()->BoxDraw(X, Y - 11, 20, 5);
	while (true)
	{
		Interface::GetInstance()->DrawMidText("                           ", X, Y - 9);
		Interface::GetInstance()->DrawMidText(str, X, Y - 9);
		tmp = getch();
		if (((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z')) && i < MAX_NAME)
		{
			ch[i] = tmp;
			i++;
		}
		else if (tmp == BACKSPACE && i > 0 && i <= MAX_NAME)
		{
			ch[i - 1] = '\0';
			i--;
		}
		else if (i > 0 && tmp == ENTER)
		{
			m_strName = str;
			break;
		}
		str = (string)ch;
		if (i >= 10)
			Interface::GetInstance()->DrawMidText("10글자 초과!!", X, Y - 13);
		else
			Interface::GetInstance()->DrawMidText("                           ", X, Y - 13);
	}
	ORIGINAL
}
void GameManager::PlayGame()
{
	ITEM item = ITEM_START;
	bool stageflag = true;
	bool infoflag = false;
	int i = 0;
	string str = "\0";
	char tmp = '\0';
	char ch[MAX_NAME * 2 + 1] = { '\0' };
	int rnum = 0;
	int oldclock = clock();
	bool failedflag = false;
	if (m_icreatspeed <= 800)
		m_icreatspeed = 800;
	WordManager::GetInstance()->SetOldClock();
	m_ifailedclock = 0;
	while (true)
	{
		if (stageflag)
		{
			stageflag = false;
			SKY_BLUE
				Interface::GetInstance()->BoxDraw(0, 0, X, Y);
			Interface::GetInstance()->BoxDraw(X, Y - 11, 20, 5);
			ORIGINAL
				Interface::GetInstance()->InfoDraw(m_iLife, m_iScore, m_strName);
			Interface::GetInstance()->ShowStage(m_istage);
		}
		if (infoflag)
		{
			infoflag = false;
			Interface::GetInstance()->InfoDraw(m_iLife, m_iScore, m_strName);
		}
		if (clock() - oldclock >= m_icreatspeed)
		{
			WordManager::GetInstance()->WordCreate();
			oldclock = clock();
		}
		if (!WordManager::GetInstance()->WordDrop())
		{
			m_iLife--;
			infoflag = true;
		}
		if (m_iLife <= 0)
		{
			stageflag = true;
			Gameover();
			break;
		}

		if (clock() - m_iItemclock >= 1500 && m_bitemflag)
		{
			m_bitemflag = false;
			WordManager::GetInstance()->ItemOff(item);
			m_iItemclock = 0;
		}
		if (kbhit() && !failedflag)
		{
			tmp = getch();
			if (((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z')) && i < MAX_NAME * 2)
			{
				ch[i] = tmp;
				i++;
			}
			else if (tmp == BACKSPACE && i > 0 && i <= MAX_NAME * 2)
			{
				ch[i - 1] = '\0';
				i--;
			}
			else if (i > 0 && tmp == ENTER)
			{
				str = (string)ch;
				if (!InputCheck(str, item))
				{
					RED
						Interface::GetInstance()->DrawMidText("Failed Compare", X, Y - 9);
					ORIGINAL
						failedflag = true;
					m_ifailedclock = clock();
					str = "                           ";
					for (int j = 0; j < MAX_NAME * 2 + 1; j++)
						ch[j] = '\0';
					i = 0;
				}
				else
				{
					infoflag = true;
					Interface::GetInstance()->DrawMidText("                           ", X, Y - 9);
					str = "                           ";
					for (int j = 0; j < MAX_NAME * 2 + 1; j++)
						ch[j] = '\0';
					i = 0;

				}
			}
			str = (string)ch;
			if (i >= 20)
				Interface::GetInstance()->DrawMidText("20글자 초과!!", X, Y - 13);
			else
				Interface::GetInstance()->DrawMidText("                           ", X, Y - 13);
			if (!failedflag)
			{
				Interface::GetInstance()->DrawMidText("                           ", X, Y - 9);
				SKY_BLUE
					Interface::GetInstance()->BoxDraw(X, Y - 11, 20, 5);
				Interface::GetInstance()->DrawMidText(str, X, Y - 9);
				ORIGINAL
			}
		}
		if (clock() - m_ifailedclock >= 3000 && failedflag)
		{
			failedflag = false;
			m_ifailedclock = 0;
			Interface::GetInstance()->DrawMidText("                           ", X, Y - 9);
		}

		if (m_iScore >= 300 * m_istage)
		{
			stageflag = true;
			m_icreatspeed -= 100;
			m_istage++;
			for (int i = 0; i < WordManager::GetInstance()->Getwordcount(); i++)
			{
				WordManager::GetInstance()->GetWord()[i].Die();
			}
			WordManager::GetInstance()->SetSpeed(WordManager::GetInstance()->GetSpeed() - 20);
			oldclock = clock();
			m_ifailedclock = clock();
		}
	}
}
bool GameManager::InputCheck(string str, ITEM& item)
{
	for (int i = 0; i < WordManager::GetInstance()->Getwordcount(); i++)
	{
		if (WordManager::GetInstance()->GetWord()[i].Getstrflag())
		{
			if (str == WordManager::GetInstance()->GetWord()[i].Getstr())
			{
				if (WordManager::GetInstance()->GetWord()[i].GetItemflag())
				{
					m_bitemflag = true;
					item = WordManager::GetInstance()->GetWord()[i].GetItem()->ItemValue();
					WordManager::GetInstance()->ItemOn(item, m_iScore, m_istage);
					m_iItemclock = clock();
				}
				WordManager::GetInstance()->GetWord()[i].Die();
				m_iScore += 30 + m_istage;
				return true;
			}
		}
	}
	return false;
}
void GameManager::Gameover()
{
	Rank::GetInstance()->Ranksave(m_strName, m_istage, m_iScore);
	int oldclock = clock();
	Interface::GetInstance()->DrawMidText("♨ Game Over ♨", X, Y / 2 - 1);
	while (true)
	{
		if (clock() - oldclock >= 3000)
			break;
	}
	m_iLife = MAX_LIFE;
	m_iScore = 0;
	m_strName = "? ? ?";
	m_istage = 1;
	m_icreatspeed = 3000;
	for (int i = 0; i < WordManager::GetInstance()->Getwordcount(); i++)
	{
		WordManager::GetInstance()->GetWord()[i].Die();
	}
}