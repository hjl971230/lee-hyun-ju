#include "GameManager.h"

GameManager* GameManager::m_GM_this = NULL;

GameManager::GameManager()
{
	m_itrapCount = 0;
	m_iGamelevel = 1;
	m_iremaintrap = 0;
}

GameManager::~GameManager()
{
	delete Interface::GetInstance();
	delete Player::GetInstance();
}

void GameManager::mapinit(string str)
{
	mapload(str);
	trap_setrandom(m_itrapCount);
	trap_setcount();
	Blocksetting();
	GamePlay();
}

void GameManager::mapload(string str)
{
	if (!m_vecmap.empty())
		m_vecmap.clear();
	int tmp;
	vector<Blockinfo> vectmp;
	Blockinfo blocktmp;
	ifstream load;
	load.open(str);
	if (load.is_open())
	{
		load >> m_mapsize.width;
		load >> m_mapsize.height;
		load >> m_itrapCount;
		m_iremaintrap = m_itrapCount;
		m_vecmap.reserve(m_mapsize.height);
		vectmp.reserve(m_mapsize.width);
		m_vecmap.assign(m_mapsize.height, vectmp);
		for (vector<vector<Blockinfo>>::iterator iter_height = m_vecmap.begin(); iter_height != m_vecmap.end(); iter_height++)
		{
			(*iter_height).assign(m_mapsize.width, blocktmp);
			for (vector<Blockinfo>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
			{
				load >> tmp;
				(*iter_width).BlockNum = tmp;
				(*iter_width).hideflag = true;
			}
		}
		load.close();
	}
}

void GameManager::trap_setrandom(int count)
{
	int trap_count = count;
	for (int i = 1; i < m_mapsize.height - 1; i++)
	{
		for (int j = 1; j < m_mapsize.width - 1; j++)
		{
			if (m_vecmap[i][j].BlockNum == EMPTY)
			{
				if (trap_count == 0)
					break;
				if (rand() % 100 < 1)
				{
					trap_count--;
					m_vecmap[i][j].BlockNum = TRAP;
				}
			}
		}
	}
	if (trap_count > 0)
		trap_setrandom(trap_count);
}

void GameManager::trap_setcount()
{
	for (int i = 1; i < m_mapsize.height - 1; i++)
	{
		for (int j = 1; j < m_mapsize.width - 1; j++)
		{
			if (m_vecmap[i][j].BlockNum == PLAYER)
			{
				Player::GetInstance()->setPoint(j, i);
				m_vecmap[i][j].BlockNum = EMPTY;
			}
			if (m_vecmap[i][j].BlockNum == TRAP)
			{
				if(m_vecmap[i - 1][j - 1].BlockNum < TRAP)
					m_vecmap[i - 1][j - 1].BlockNum++;
				if (m_vecmap[i - 1][j].BlockNum < TRAP)
					m_vecmap[i - 1][j].BlockNum++;
				if (m_vecmap[i - 1][j + 1].BlockNum < TRAP)
					m_vecmap[i - 1][j + 1].BlockNum++;
				if (m_vecmap[i][j - 1].BlockNum < TRAP)
					m_vecmap[i][j - 1].BlockNum++;
				if (m_vecmap[i][j + 1].BlockNum < TRAP)
					m_vecmap[i][j + 1].BlockNum++;
				if (m_vecmap[i + 1][j - 1].BlockNum < TRAP)
					m_vecmap[i + 1][j - 1].BlockNum++;
				if (m_vecmap[i + 1][j].BlockNum < TRAP)
					m_vecmap[i + 1][j].BlockNum++;
				if (m_vecmap[i + 1][j + 1].BlockNum < TRAP)
					m_vecmap[i + 1][j + 1].BlockNum++;
			}
		}
	}
}

void GameManager::Blocksetting()
{
	string str;
	for (vector<vector<Blockinfo>>::iterator iter_height = m_vecmap.begin(); iter_height != m_vecmap.end(); iter_height++)
	{
		for (vector<Blockinfo>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
		{
			switch ((*iter_width).BlockNum)
			{
			case WALL:
				str = "¢Ë";
				break;
			case TRAP:
				str = "¢Ã";
				break;
			case PLAYER:
				str = "¢Á";
				break;
			case FLAG:
				str = "¢Â";
				break;
			case BOOM:
				str = "¢Í";
				break;
			case EMPTY:
				str = "  ";
			default:
				str = " " + to_string((*iter_width).BlockNum);
				break;
			}
			(*iter_width).Blockshape = str;
		}
	}
}

void GameManager::GameMain()
{
	char level[256];
	int select = 0;
	while (true)
	{
		system("cls");
		Interface::GetInstance()->MainMenu();
		sprintf(level, "map%d.txt", m_iGamelevel);
		cin >> select;
		switch (select)
		{
		case MENU_PLAY:
			mapinit(level);
			break;
		case MENU_LEVEL:
			Level_Select();
			break;
		case MENU_EXIT:
			return;
		}
	}
}

void GameManager::Level_Select()
{
	int select = 0;
	system("cls");
	Interface::GetInstance()->selectLevel();
	cin >> select;
	switch (select)
	{
	case LEVEL_EASY:
		m_iGamelevel = LEVEL_EASY;
		break;
	case LEVEL_NORMAL:
		m_iGamelevel = LEVEL_NORMAL;
		break;
	case LEVEL_HARD:
		m_iGamelevel = LEVEL_HARD;
		break;
	case LEVEL_EXIT:
		return;
	}
}

void GameManager::GamePlay()
{
	bool gameflag = true;
	RESULT result;
	Interface::GetInstance()->GameDraw(m_mapsize.width, m_mapsize.height);
	while (gameflag)
	{
		Interface::GetInstance()->info(m_itrapCount, m_iremaintrap, m_mapsize.width, m_mapsize.height);
		Interface::GetInstance()->DrawPoint(Player::GetInstance()->geticon(), Player::GetInstance()->getPoint().x, Player::GetInstance()->getPoint().y);
		Input();
		RESULT result = WinCheck();
		switch (result)
		{
		case RESULT_CLEAR:
		case RESULT_BOOM:
			Interface::GetInstance()->GameResult(result, m_mapsize.width, m_mapsize.height);
			gameflag = false;
			break;
		case RESULT_PLAY:
			break;
		}
	}
	system("pause");
}

void GameManager::Input()
{
	char ch = getch();
	switch (ch)
	{
	case KEY_UP:
	case KEY_DOWN:
	case KEY_LEFT:
	case KEY_RIGHT:
		EraseCheck();
		Player::GetInstance()->move(ch, m_mapsize.width, m_mapsize.height);
		break;
	case KEY_ENTER:
		if (m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].hideflag)
		{
			DefaultCheck(Player::GetInstance()->getPoint().x, Player::GetInstance()->getPoint().y);
			TrapCheck();
			Interface::GetInstance()->vecmapDraw(m_vecmap);
		}
		break;
	case KEY_SPACE:
		if (m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].hideflag)
		{
			m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].hideflag = false;
			m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].BlockNum += FLAG;
			m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].Blockshape = "¢Â";
			m_iremaintrap--;
			Interface::GetInstance()->vecmapDraw(m_vecmap);
		}
		break;
	case KEY_CANCEL:
		if (m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].BlockNum >= FLAG)
		{
			m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].hideflag = true;
			m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].BlockNum -= FLAG;
			m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].Blockshape = " " 
				+ to_string(m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].BlockNum);
			m_iremaintrap++;
			Interface::GetInstance()->vecmapDraw(m_vecmap);
		}
		break;
	}
	
}

void GameManager::EraseCheck()
{
	if(m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].hideflag)
		Interface::GetInstance()->Erase(Player::GetInstance()->getPoint().x,
			Player::GetInstance()->getPoint().y,"¢Ë");
	else
		Interface::GetInstance()->Erase(Player::GetInstance()->getPoint().x,
			Player::GetInstance()->getPoint().y,
			m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].Blockshape);
}

void GameManager::TrapCheck()
{
	if (m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].hideflag)
	{
		if (m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].BlockNum == TRAP)
		{
			for (vector<vector<Blockinfo>>::iterator iter_height = m_vecmap.begin(); iter_height != m_vecmap.end(); iter_height++)
			{
				for (vector<Blockinfo>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
				{
					(*iter_width).hideflag = false;
				}
			}
			m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].BlockNum = BOOM;
			m_vecmap[Player::GetInstance()->getPoint().y][Player::GetInstance()->getPoint().x].Blockshape = "¢Í";
		}
	}
}

void GameManager::DefaultCheck(int x, int y)
{
	if (x <= 0 || y <= 0 || x >= m_mapsize.width || y >= m_mapsize.height)
		return;
	if (m_vecmap[y][x].BlockNum < TRAP && m_vecmap[y][x].hideflag)
	{
		m_vecmap[y][x].hideflag = false;
		if(m_vecmap[y][x].BlockNum > EMPTY)
			return;
		else
		{
			DefaultCheck(x - 1, y);
			DefaultCheck(x + 1, y);
			DefaultCheck(x, y - 1);
			DefaultCheck(x, y + 1);
			DefaultCheck(x - 1, y - 1);
			DefaultCheck(x - 1, y + 1);
			DefaultCheck(x + 1, y - 1);
			DefaultCheck(x + 1, y + 1);
		}
	}
}

RESULT GameManager::WinCheck()
{
	int count = 0;
	for (vector<vector<Blockinfo>>::iterator iter_height = m_vecmap.begin(); iter_height != m_vecmap.end(); iter_height++)
	{
		for (vector<Blockinfo>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
		{
			if ((*iter_width).BlockNum == BOOM)
				return RESULT_BOOM;
			if ((*iter_width).BlockNum >= FLAG)
				count++;
		}
	}
	if (count == m_itrapCount)
		return RESULT_CLEAR;
	return RESULT_PLAY;
}