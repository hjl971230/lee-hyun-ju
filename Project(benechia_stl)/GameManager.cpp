#include "GameManager.h"

GameManager* GameManager::m_GameManger_this = NULL;

GameManager::GameManager()
{

}

GameManager::~GameManager()
{
	delete MapDraw::GetInstance();
	delete Interface::GetInstance();	
	delete WordManager::GetInstance();
	delete Rank::GetInstance();
}