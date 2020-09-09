#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

GameManager::GameManager()
{
	
}

GameManager::~GameManager()
{

}

void GameManager::GameInit(HDC hdc, HINSTANCE hInst)
{
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 2000, 1000));
	Player::GetInstance()->Init(hdc, hInst);
}

void GameManager::GameDraw(HDC hdc)
{
	Player::GetInstance()->Draw(m_BitMap.getMemDC());
	BitBlt(hdc, 0, 0, m_BitMap.getsize().cx, m_BitMap.getsize().cy, m_BitMap.getMemDC(), 0, 0, SRCCOPY);
}

void GameManager::Update(HDC hdc)
{
	//GameDraw(hdc);
}

void GameManager::PlayGame()
{
	Player::GetInstance()->KeyInput();
	if(Player::GetInstance()->getjumpflag())
		Player::GetInstance()->Jump();
}