#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

GameManager::GameManager()
{
	m_imin = 0;
	m_isec = 0;
	m_ilevel = LEVEL_EASY;
	m_itrapcount = MINE_LEVEL_EASY;
	MouseReset();
}

GameManager::~GameManager()
{

}

void GameManager::Init(HDC hdc, HINSTANCE hInst)
{
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 2000, 1000));
	m_BG.Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\back.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
}

void GameManager::MapInit(HDC hdc, HINSTANCE hInst)
{
	if (!m_vecmap.empty())
		m_vecmap.clear();
	int tmp;
	vector<Block> vectmp;
	Block blocktmp;
	vector<vector<Block>>::iterator y_iter = m_vecmap.begin();
	m_vecmap.reserve(MAPSIZE_LEVEL_HARD);
	vectmp.reserve(MAPSIZE_LEVEL_HARD);
	m_vecmap.assign(MAPSIZE_LEVEL_HARD, vectmp);
	for (vector<vector<Block>>::iterator iter_height = m_vecmap.begin(); iter_height != m_vecmap.end(); iter_height++)
	{
		(*iter_height).assign(MAPSIZE_LEVEL_HARD, blocktmp);
		for (vector<Block>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
		{

		}
	}
}

void GameManager::Draw(HDC hdc, HINSTANCE hInst)
{
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 2000, 1000));
	m_BG.Draw(m_BitMap.getMemDC(), 0, 0);
	TextOut(m_BitMap.getMemDC(), TIMER_X, UI_Y, m_timer, lstrlen(m_timer));
	BitBlt(hdc, 0, 0, m_BitMap.getsize().cx, m_BitMap.getsize().cy, m_BitMap.getMemDC(), 0, 0, SRCCOPY);
}

void GameManager::TimeUpdate()
{
	wsprintf(m_timer, "%d : %d", m_imin, m_isec);
	m_isec++;
	if (m_isec >= 60)
	{
		m_isec = 0;
		m_imin++;
	}
}

void GameManager::Click()
{
	//MouseReset();
}

void GameManager::MouseReset()
{
	Lmouse.x = 0;
	Lmouse.y = 0;
	Rmouse.x = 0;
	Rmouse.y = 0;
}