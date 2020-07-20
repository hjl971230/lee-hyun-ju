#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

GameManager::GameManager()
{
	m_bResetflag = false;
}

GameManager::~GameManager()
{

}

void GameManager::Mapload(string filename)
{
	int width = 0;
	int height = 0;
	ifstream load;
	int tmp = 0;
	load.open(filename);
	vector<int> vectmp;
	if (load.is_open())
	{
		load >> width;
		load >> height;
		m_vecMap.reserve(height);
		vectmp.reserve(width);
		m_vecMap.assign(height, vectmp);
		for (vector<vector<int>>::iterator iter_height = m_vecMap.begin(); iter_height != m_vecMap.end(); iter_height++)
		{
			(*iter_height).assign(width, 0);
			for (vector<int>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
			{
				load >> tmp;
				(*iter_width) = tmp;
			}
		}
		load.close();
	}
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
	int Width = (WIDTH * 2) + 10;
	int Height = HEIGHT + 10;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height, Width);
	system(buf);
	Mapload("Map1.txt");

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

		GREEN
		cout << "●: 랜덤 포탈(출구 중 랜덤한 위치)" << endl;
	ORIGINAL

		SKY_BLUE
		cout << "★: 랜덤 삭제(벽만 삭제, 확률적)" << endl;
	ORIGINAL

		GOLD
		cout << "★: 초기화" << endl;
	ORIGINAL
}