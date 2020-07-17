#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

GameManager::GameManager()
{
	for (auto iter = m_vecMap.begin(); iter != m_vecMap.end(); iter++)
		(*iter).reserve(MAX_SIZE);
	m_bResetflag = false;
}

GameManager::~GameManager()
{

}

void GameManager::PlayGame()
{
	bool gameFlag = true;
	Init();
	while (gameFlag)
	{
		Mapdraw();
		Guide();
		gameFlag = P1.Move(m_vecMap, Exit_Potal, m_bResetflag);
		if (m_bResetflag)
		{
			Init();
			m_bResetflag = false;
		}
	}
}

void GameManager::Init()
{
	/*int Width = (WIDTH * 2) + 10;
	int Height = HEIGHT + 10;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height, Width);
	system(buf);*/

	m_vecMap =
	{
		{WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
		{WALL, ENTRY_START, CHARACTER, EMPTY, EMPTY, RANDOM_START + 1, WALL, WALL, EMPTY, EMPTY, RANDOM_START + 2, WALL},
		{WALL, EMPTY, EMPTY, EMPTY, EXIT_START + 1, WALL, EMPTY, WALL, WALL, EMPTY, EMPTY, WALL},
		{WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, EXIT_START + 3, ENTRY_START + 4, EMPTY, WALL},
		{WALL, EMPTY, RANDOM_START + 3, EMPTY, WALL, EMPTY, WALL, EMPTY, ENTRY_START + 1, EMPTY, EMPTY, WALL},
		{WALL, EMPTY, ENTRY_START + 3, EXIT_START + 5, WALL, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, WALL},
		{WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, KEY, EMPTY, WALL},
		{WALL, EMPTY, RANDOM_START + 4, EMPTY, WALL, RESET, WALL, ENTRY_START + 2, EMPTY, WALL, EMPTY, GAMECLEAR},
		{WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EXIT_START + 4, EMPTY, EMPTY, EMPTY, WALL},
		{WALL, EMPTY, EXIT_START, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, RANDOM_START, WALL},
		{WALL, KEY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EXIT_START + 2, EMPTY, WALL},
		{WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}
	};

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (m_vecMap[y][x] == CHARACTER)
			{
				P1.setCharacterPoint(x, y);
			}
			else if (m_vecMap[y][x] >= ENTRY_START && m_vecMap[y][x] < ENTRY_START + POTAL_MAX)
			{
				Entry_Potal[m_vecMap[y][x] - ENTRY_START].x = x;
				Entry_Potal[m_vecMap[y][x] - ENTRY_START].y = y;
			}
			else if (m_vecMap[y][x] >= EXIT_START && m_vecMap[y][x] < EXIT_START + POTAL_MAX)
			{
				Exit_Potal[m_vecMap[y][x] - EXIT_START].x = x;
				Exit_Potal[m_vecMap[y][x] - EXIT_START].y = y;
			}
			else if (m_vecMap[y][x] >= RANDOM_START && m_vecMap[y][x] < RANDOM_START + POTAL_MAX)
			{
				Random_Potal[m_vecMap[y][x] - RANDOM_START].x = x;
				Random_Potal[m_vecMap[y][x] - RANDOM_START].y = y;
			}

		}
	}

	P1.setLastObjectindex(0);
}

void GameManager::Mapdraw()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (m_vecMap[y][x] == WALL)
			{
				cout << "▩";
			}
			else if (m_vecMap[y][x] >= ENTRY_START && m_vecMap[y][x] < ENTRY_START + POTAL_MAX)
			{
				BLUE
					cout << "◎";
				ORIGINAL
			}
			else if (m_vecMap[y][x] >= EXIT_START && m_vecMap[y][x] < EXIT_START + POTAL_MAX)
			{
				YELLOW
					cout << "●";
				ORIGINAL
			}
			else if (m_vecMap[y][x] == GAMECLEAR)
			{
				GRAY
					cout << "◎";
				ORIGINAL
			}
			else if (m_vecMap[y][x] == CHARACTER)
			{
				RED
					cout << "♠";
				ORIGINAL
			}
			else if (m_vecMap[y][x] >= RANDOM_START && m_vecMap[y][x] < RANDOM_START + POTAL_MAX)
			{
				GREEN
					cout << "●";
				ORIGINAL
			}
			else if (m_vecMap[y][x] == RESET)
			{
				GOLD
					cout << "★";
				ORIGINAL
			}
			else if (m_vecMap[y][x] == KEY)
			{
				SKY_BLUE
					cout << "★";
				ORIGINAL
			}
			else if (m_vecMap[y][x] == EMPTY)
				cout << "  ";
		}
		cout << endl;
	}
}

void GameManager::Guide()
{
	cout << "▩: 벽" << endl;

	BLUE
		cout << "◎: 포탈 입구 " << "\t";
	ORIGINAL

		YELLOW
		cout << "●: 포탈 출구" << endl;
	ORIGINAL

		RED
		cout << "♠: 플레이어 1" << "\t";
	ORIGINAL

		PUPPLE
		cout << "♣: 플레이어 2" << endl;
	ORIGINAL

		GREEN
		cout << "●: 랜덤 포탈" << "\t";
	ORIGINAL

		SKY_BLUE
		cout << "★: 랜덤 삭제(벽만 삭제, 확률적)" << endl;
	ORIGINAL

		GOLD
		cout << "★: 초기화" << endl;
	ORIGINAL
}