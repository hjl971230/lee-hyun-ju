#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

GameManager::GameManager()
{
	m_ibacksize = 0;
	m_idecosize = 0;
	m_inormalcount = 0;
	m_imitercount = 0;
	m_imiter = 100;
	wsprintf(nowMiter, TEXT("%d"), m_imiter);
	m_imovemiter = 0;
}

GameManager::~GameManager()
{

}

void GameManager::GameInit(HDC hdc, HINSTANCE hInst)
{
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 2000, 1000));
	m_BG[BG_CODE_BACK].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "back.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_BG[BG_CODE_DECO].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "back_deco.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_BG[BG_CODE_NORMAL].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "back_normal.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_BG[BG_CODE_NORMAL2].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "back_normal2.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_Miter.Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "miter.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	Player::GetInstance()->Init(hdc, hInst);
}

void GameManager::GameDraw(HDC hdc, HINSTANCE hInst)
{
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 2000, 1000));
	BGDraw(m_BitMap.getMemDC());
	Player::GetInstance()->Draw(m_BitMap.getMemDC());
	BitBlt(hdc, 0, 0, m_BitMap.getsize().cx, m_BitMap.getsize().cy, m_BitMap.getMemDC(), 0, 0, SRCCOPY);
}

void GameManager::BGDraw(HDC hdc)
{
	while (m_ibacksize + m_imovemiter <= 1800)
	{
		if (m_imitercount % 10 == 0)
		{
			m_Miter.Draw(hdc, m_ibacksize, 670);
			wsprintf(nowMiter, TEXT("%d"), m_imiter);
			TextOut(hdc, m_ibacksize + 25, 675, nowMiter, lstrlen(nowMiter));
			m_imitercount = 0;
			if (m_imiter > 0) m_imiter -= 10;
		}
		m_BG[BG_CODE_BACK].Draw(hdc, m_ibacksize, 480);
		if (m_inormalcount < 12)
		{
			m_BG[BG_CODE_NORMAL].Draw(hdc, m_idecosize, 416);
			m_idecosize += m_BG[BG_CODE_NORMAL].getsize().cx;
			m_inormalcount++;
		}
		else
		{
			m_BG[BG_CODE_DECO].Draw(hdc, m_idecosize, 413);
			m_idecosize += m_BG[BG_CODE_DECO].getsize().cx;
			m_inormalcount = 0;
		}
		m_ibacksize += m_BG[BG_CODE_BACK].getsize().cx;
		m_imitercount++;
	}
	m_ibacksize = 0 + m_imovemiter;
	m_idecosize = 0 + m_imovemiter;
	m_inormalcount = 0;
	m_imitercount = 0;
	m_imiter = 100;
	wsprintf(nowMiter, TEXT("%d"), m_imiter);
}

void GameManager::Update(HDC hdc)
{
	//GameDraw(hdc);
}

void GameManager::PlayGame()
{
	KeyInput();
	Player::GetInstance()->KeyInput();
	if (Player::GetInstance()->getjumpflag())
	{
		Player::GetInstance()->Jump();
	}
}

void GameManager::KeyInput()
{
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_imovemiter += MOVESPEED * 2;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_imovemiter -= MOVESPEED * 2;
	}
}