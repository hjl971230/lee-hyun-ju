#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

GameManager::GameManager()
{
	
}

GameManager::~GameManager()
{
	MapRelease();
	m_Playervec.clear();
}

void GameManager::GameInit(HWND hWnd)
{
	MapInit(hWnd);
	PlayerInit(hWnd);
}

void GameManager::MapInit(HWND hWnd)
{
	vector<BitMap> size;
	BitMap bsize;
	size.reserve(MAPSIZE_WIDTH);
	MapRelease();
	m_map.reserve(MAPSIZE_HEIGHT);
	m_map.assign(MAPSIZE_HEIGHT, size);
	char filename[128];
	int num = 1;
	int x = MAP_X;
	int y = MAP_Y;
	int height = 0;
	for (vector<vector<BitMap>>::iterator iter = m_map.begin(); iter != m_map.end(); iter++)
	{
		(*iter).assign(MAPSIZE_WIDTH, bsize);
		x = MAP_X;
		for (vector<BitMap>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			sprintf(filename, TEXT("block0%d.bmp"), num);
			(*iter2).setFileName(filename);
			(*iter2).Init(hWnd, x, y);
			if (x != MAP_X + ((BMPSIZE_WIDTH / 2) * (MAPSIZE_WIDTH - 1)))
			{
				if (num == 1)num = 2;
				else num = 1;
			}
			x += BMPSIZE_WIDTH / 2;
		}
		y += BMPSIZE_HEIGHT / 2;
	}
}

void GameManager::MapRelease()
{
	if (!m_map.empty())
		m_map.clear();
}

void GameManager::MapDraw(HDC hdc)
{
	for (vector<vector<BitMap>>::iterator iter = m_map.begin(); iter != m_map.end(); iter++)
	{
		for (vector<BitMap>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			(*iter2).Draw(hdc);
		}
	}
}

void GameManager::PlayerInit(HWND hWnd)
{
	Player tmp;
	int x = MAP_X;
	int y = MAP_Y;
	m_Playervec.clear();
	m_Playervec.reserve(PLAYERSIZE);
	m_Playervec.assign(PLAYERSIZE, tmp);
	m_Playervec[PLAYER_BLACK].setPlayerType(BLACK);
	m_Playervec[PLAYER_WHITE].setPlayerType(WHITE);
	for (int i = 0; i < LINESIZE; i++)
	{
		if (i == PLAYER_WHITE) y = MAP_Y + ((BMPSIZE_HEIGHT / 2) * 6);
		m_Playervec[i].ChessPieceInit(hWnd, x, y, i);
	}
}

void GameManager::PieceDraw(HDC hdc)
{
	for (int i = 0; i < LINESIZE; i++)
		m_Playervec[i].ChessPieceDraw(hdc);
}