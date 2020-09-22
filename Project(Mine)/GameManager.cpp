#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

GameManager::GameManager()
{
	m_imin = 0;
	m_isec = 0;
	m_ilevel = LEVEL_EASY;
	m_itrapcount = MINE_LEVEL_EASY;
	m_imapheight = MAPSIZE_HEIGHT_EASY;
	m_imapwidth = MAPSIZE_WIDTH_EASY;
	MouseReset();
}

GameManager::~GameManager()
{

}

void GameManager::Init(HDC hdc, HINSTANCE hInst)
{
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 900, 700));
	m_BG.Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\back.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	MapInit(m_BitMap.getMemDC(), hInst);
}

void GameManager::MapInit(HDC hdc, HINSTANCE hInst)
{
	vector<Block> vectmp;
	Block blocktmp;
	m_vecmap.reserve(MAPSIZE_HEIGHT_HARD);
	vectmp.reserve(MAPSIZE_WIDTH_HARD);
	m_vecmap.assign(MAPSIZE_HEIGHT_HARD, vectmp);
	for (vector<vector<Block>>::iterator iter_height = m_vecmap.begin(); iter_height != m_vecmap.end(); iter_height++)
	{
		(*iter_height).assign(MAPSIZE_WIDTH_HARD, blocktmp);
		for (vector<Block>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
		{
			(*iter_width).Init(hdc, hInst);
		}
	}
}

void GameManager::MapDraw()
{
	int x = 43;
	int y = 45;
	int size_y = 26;
	for (vector<vector<Block>>::iterator iter_height = m_vecmap.begin(); iter_height != m_vecmap.end(); iter_height++)
	{
		for (vector<Block>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
		{
			(*iter_width).Draw(m_BitMap.getMemDC(), x, y);
			x += 26;
		}
		y += size_y;
		x = 43;
	}
}

void GameManager::Draw(HDC hdc, HINSTANCE hInst)
{
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 900, 700));
	BGDraw();
	MapDraw();
	BitBlt(hdc, 0, 0, m_BitMap.getsize().cx, m_BitMap.getsize().cy, m_BitMap.getMemDC(), 0, 0, SRCCOPY);
}

void GameManager::BGDraw()
{
	int blocksize_x = 26;
	int blocksize_y = 26;
	int mapsize_x = m_BG.getsize().cx;
	int mapsize_y = m_BG.getsize().cy;
	//m_BG.Draw(m_BitMap.getMemDC(), 0, 0);
	//m_BG.CutDraw(m_BitMap.getMemDC(), 0, 0, 43 + (blocksize_x * ((m_imapwidth / 2))), 45 + (blocksize_y * m_imapheight / 2), 0, 0, 43 + (blocksize_x * ((m_imapwidth / 2))), 45 + (blocksize_y * m_imapheight / 2));
	m_BG.CutDraw(m_BitMap.getMemDC(), 
		693, 0, 
		mapsize_x, 45 + (blocksize_y * m_imapheight / 2),
		693, 0,
		mapsize_x, 45 + (blocksize_y * m_imapheight / 2));
	TextOut(m_BitMap.getMemDC(), TIMER_X, UI_Y, m_timer, lstrlen(m_timer));
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