#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

GameManager::GameManager()
{
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
}

void GameManager::MapRelease()
{
	
}

void GameManager::MapDraw()
{
	
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
	
}

void GameManager::LevelInit()
{
	
}

void GameManager::ChangeLevel(HINSTANCE hInst)
{
	LevelInit();
	MapInit(m_BitMap.getMemDC(), hInst);
}

void GameManager::Lbutton_Click()
{
	
}

void GameManager::Rbutton_Click()
{
	
}

void GameManager::MouseReset()
{
	Lmouse.x = 0;
	Lmouse.y = 0;
	Rmouse.x = 0;
	Rmouse.y = 0;
}