#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

GameManager::GameManager()
{
	m_imin = 0;
	m_isec = 0;
	m_ilevel = LEVEL_EASY;
	LevelInit();
	MouseReset();
}

GameManager::~GameManager()
{
	MapRelease();
}

void GameManager::Init(HDC hdc, HINSTANCE hInst)
{
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 900, 700));
	m_BG.Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\back.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	MapInit(m_BitMap.getMemDC(), hInst);
}

void GameManager::MapInit(HDC hdc, HINSTANCE hInst)
{
	MapRelease();
	vector<Block*> vectmp;
	Block* blocktmp = NULL;
	m_vecmap.reserve(m_imapheight);
	vectmp.reserve(m_imapwidth);
	m_vecmap.assign(m_imapheight, vectmp);
	for (vector<vector<Block*>>::iterator iter_height = m_vecmap.begin(); iter_height != m_vecmap.end(); iter_height++)
	{
		(*iter_height).assign(m_imapwidth, blocktmp);
		for (vector<Block*>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
		{
			(*iter_width) = new Block;
			(*iter_width)->Init(hdc, hInst);
		}
	}
	trap_setrandom(m_itrapcount);
	trap_setcount(hInst);
}

void GameManager::MapRelease()
{
	for (vector<vector<Block*>>::iterator iter_height = m_vecmap.begin(); iter_height != m_vecmap.end(); iter_height++)
	{
		for (vector<Block*>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
		{
			if ((*iter_width) != NULL)
			{
				delete (*iter_width);
				(*iter_width) = NULL;
			}
		}
	}
	m_vecmap.clear();
}

void GameManager::MapDraw()
{
	int x = 43;
	int y = 45;
	int size_y = 26;
	for (vector<vector<Block*>>::iterator iter_height = m_vecmap.begin(); iter_height != m_vecmap.end(); iter_height++)
	{
		for (vector<Block*>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
		{
			(*iter_width)->Draw(m_BitMap.getMemDC(), x, y);
			(*iter_width)->UpdateCollider(x, y);
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
	wsprintf(m_minenumtext, "%d", m_itrapcount);
	m_BG.CutDraw(m_BitMap.getMemDC(), 
		0, 0, 
		43 + (blocksize_x * ((m_imapwidth / 2))), 45 + (blocksize_y * m_imapheight / 2), 
		0, 0, 
		43 + (blocksize_x * ((m_imapwidth / 2))), 45 + (blocksize_y * m_imapheight / 2));
	m_BG.CutDraw(m_BitMap.getMemDC(), 
		43 + (blocksize_x * ((m_imapwidth / 2))), 0,
		45 + (blocksize_x * ((m_imapwidth / 2))), 45 + (blocksize_y * m_imapheight / 2),
		mapsize_x - (45 + (blocksize_x * ((m_imapwidth / 2)))), 0,
		45 + (blocksize_x * ((m_imapwidth / 2))), 45 + (blocksize_y * m_imapheight / 2));
	m_BG.CutDraw(m_BitMap.getMemDC(),
		0, 45 + (blocksize_y * m_imapheight / 2),
		43 + (blocksize_x * ((m_imapwidth / 2))), 45 + (blocksize_y * m_imapheight / 2),
		0, mapsize_y - (46 + (blocksize_y * m_imapheight / 2)),
		43 + (blocksize_x * ((m_imapwidth / 2))), (46 + (blocksize_y * m_imapheight / 2)));
	m_BG.CutDraw(m_BitMap.getMemDC(),
		43 + (blocksize_x * ((m_imapwidth / 2))), 45 + (blocksize_y * m_imapheight / 2),
		45 + (blocksize_x * ((m_imapwidth / 2))), 45 + (blocksize_y * m_imapheight / 2),
		mapsize_x - (45 + (blocksize_x * ((m_imapwidth / 2)))), mapsize_y - (46 + (blocksize_y * m_imapheight / 2)),
		45 + (blocksize_x * ((m_imapwidth / 2))), (46 + (blocksize_y * m_imapheight / 2)));
	if (m_ilevel == LEVEL_EASY)
	{
		m_BG.CutDraw(m_BitMap.getMemDC(), 40, 45 + (blocksize_y * m_imapheight / 2) + (blocksize_y * m_imapheight / 2), 
			150, 45, 100, mapsize_y - 46, 140, 45);
		m_BG.CutDraw(m_BitMap.getMemDC(), 40 + (blocksize_x * ((m_imapwidth / 2))), 45 + (blocksize_y * m_imapheight), 
			150, 45, 620, mapsize_y - 46, 140, 45);
		TextOut(m_BitMap.getMemDC(), 120, 60 + (blocksize_y * m_imapheight), m_timer, lstrlen(m_timer));
		TextOut(m_BitMap.getMemDC(),
			100 + (blocksize_x * ((m_imapwidth / 2))), 60 + (blocksize_y * m_imapheight), m_minenumtext, lstrlen(m_minenumtext));
	}
	else
	{
		TextOut(m_BitMap.getMemDC(), 
			TIMER_X + 60 * (m_ilevel - 1) - (m_ilevel * m_imapwidth), 60 + (blocksize_y * m_imapheight), m_timer, lstrlen(m_timer));
		TextOut(m_BitMap.getMemDC(), 
			43 + (blocksize_x * ((m_imapwidth / 2))) + m_ilevel * m_imapwidth * 4, 60 + (blocksize_y * m_imapheight), m_minenumtext, lstrlen(m_minenumtext));
	}
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

void GameManager::LevelInit()
{
	switch (m_ilevel)
	{
	case LEVEL_EASY:
		m_itrapcount = MINE_LEVEL_EASY;
		m_imapheight = MAPSIZE_HEIGHT_EASY;
		m_imapwidth = MAPSIZE_WIDTH_EASY;
		break;
	case LEVEL_NORMAL:
		m_itrapcount = MINE_LEVEL_NORMAL;
		m_imapheight = MAPSIZE_HEIGHT_NORMAL;
		m_imapwidth = MAPSIZE_WIDTH_NORMAL;
		break;
	case LEVEL_HARD:
		m_itrapcount = MINE_LEVEL_HARD;
		m_imapheight = MAPSIZE_HEIGHT_HARD;
		m_imapwidth = MAPSIZE_WIDTH_HARD;
		break;
	}
	m_imin = 0; 
	m_isec = 0;
	wsprintf(m_timer, "%d : %d", m_imin, m_isec);
}

void GameManager::ChangeLevel(HINSTANCE hInst)
{
	LevelInit();
	MapInit(m_BitMap.getMemDC(), hInst);
}

void GameManager::Lbutton_Click()
{
	for (int i = 0; i < m_imapheight; i++)
	{
		for (int j = 0; j < m_imapwidth; j++)
		{
			if (m_vecmap[i][j]->Click(Lmouse, MINE_CLICKED, m_itrapcount))
			{
				DefaultCheck(j, i);
			}
		}
	}
}

void GameManager::Rbutton_Click()
{
	for (vector<vector<Block*>>::iterator iter_height = m_vecmap.begin(); iter_height != m_vecmap.end(); iter_height++)
	{
		for (vector<Block*>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
		{
			if ((*iter_width)->Click(Rmouse, MINE_FLAG, m_itrapcount))
			{
			}
		}
	}
}

void GameManager::MouseReset()
{
	Lmouse.x = 0;
	Lmouse.y = 0;
	Rmouse.x = 0;
	Rmouse.y = 0;
}

void GameManager::trap_setrandom(int count)
{
	int trap_count = count;
	for (int i = 0; i < m_imapheight; i++)
	{
		for (int j = 0; j < m_imapwidth; j++)
		{
			if (m_vecmap[i][j]->getcount() == 0)
			{
				if (trap_count == 0)
					break;
				if (rand() % 100 < 1)
				{
					trap_count--;
					m_vecmap[i][j]->setcount(TRAP);
				}
			}
		}
	}
	if (trap_count > 0)
		trap_setrandom(trap_count);
}

void GameManager::trap_setcount(HINSTANCE hInst)
{
	for (int i = 0; i < m_imapheight; i++)
	{
		for (int j = 0; j < m_imapwidth; j++)
		{
			if (m_vecmap[i][j]->getcount() == TRAP)
			{
				if (i > 0)
				{
					if (j > 0)
					{
						if (m_vecmap[i - 1][j - 1]->getcount() < TRAP)
							m_vecmap[i - 1][j - 1]->countup();
					}
					if (j < m_imapwidth - 1)
					{
						if (m_vecmap[i - 1][j + 1]->getcount() < TRAP)
							m_vecmap[i - 1][j + 1]->countup();
					}
					if (m_vecmap[i - 1][j]->getcount() < TRAP)
						m_vecmap[i - 1][j]->countup();
				}
				if (j > 0)
				{
					if (m_vecmap[i][j - 1]->getcount() < TRAP)
						m_vecmap[i][j - 1]->countup();
				}
				if (j < m_imapwidth - 1)
				{
					if (m_vecmap[i][j + 1]->getcount() < TRAP)
						m_vecmap[i][j + 1]->countup();
				}
				if (i < m_imapheight - 1)
				{
					if (j > 0)
					{
						if (m_vecmap[i + 1][j - 1]->getcount() < TRAP)
							m_vecmap[i + 1][j - 1]->countup();
					}
					if (j < m_imapwidth - 1)
					{
						if (m_vecmap[i + 1][j + 1]->getcount() < TRAP)
							m_vecmap[i + 1][j + 1]->countup();
					}
					if (m_vecmap[i + 1][j]->getcount() < TRAP)
						m_vecmap[i + 1][j]->countup();
				}
			}
		}
	}
	for (vector<vector<Block*>>::iterator iter_height = m_vecmap.begin(); iter_height != m_vecmap.end(); iter_height++)
	{
		for (vector<Block*>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
		{
			(*iter_width)->numbersload(m_BitMap.getMemDC(), hInst);
		}
	}
}

void GameManager::DefaultCheck(int x, int y)
{
	if (x <= 0 || y <= 0 || x >= m_imapwidth || y >= m_imapheight)
		return;
	if (m_vecmap[y][x]->getcount() < TRAP && m_vecmap[y][x]->gethideflag() != MINE_FLAG)
	{
		m_vecmap[y][x]->sethideflag(MINE_CLICKED);
		if (m_vecmap[y][x]->getcount() > 0)
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
	else return;
}