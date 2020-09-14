#include "EnemyManager.h"

EnemyManager* EnemyManager::m_this = NULL;

EnemyManager::EnemyManager()
{
	
}

EnemyManager::~EnemyManager()
{
	release();
}

void EnemyManager::Init(HDC hdc, HINSTANCE hInst)
{

}

void EnemyManager::release()
{
	vector<Enemy*>::iterator iter = m_vecEnemyList.begin();
	for (iter; iter != m_vecEnemyList.end(); iter++)
	{
		if ((*iter) != NULL)
		{
			delete (*iter);
			(*iter) = NULL;
		}
	}
	m_vecEnemyList.clear();
}

Enemy* EnemyManager::EnemyFactory(HDC hdc, HINSTANCE hInst, int type)
{
	switch (type)
	{
	case ENEMY_CODE_RING:
		return new Ring(hdc, hInst);
	case ENEMY_CODE_SMALLRING:
		return new SmallRing(hdc, hInst);
	case ENEMY_CODE_POT:
		return new Pot(hdc, hInst);
	default:
		return NULL;
	}
}