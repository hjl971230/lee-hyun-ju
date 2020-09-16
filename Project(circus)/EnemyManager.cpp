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
	for (int i = 0; i < 10; i++)
	{
		m_EnemyList.push_back(EnemyFactory(hdc, hInst, (rand() % ENEMY_CODE_END)));
	}
	PointSetting();
}

void EnemyManager::PointSetting()
{
	int x = 700;
	int y = 0;
	vector<Enemy*>::iterator iter = m_EnemyList.begin();
	for (iter; iter != m_EnemyList.end(); iter++)
	{
		if ((*iter) != NULL)
		{
			switch ((*iter)->gettype_code())
			{
			case ENEMY_CODE_RING:
			case ENEMY_CODE_SMALLRING:
				y = 480;
				break;
			case ENEMY_CODE_POT:
				y = 615;
				break;
			}
			(*iter)->setx(x);
			(*iter)->sety(y);
			x += 700;
		}
	}
}

void EnemyManager::PointUpdate(int move)
{
	vector<Enemy*>::iterator iter = m_EnemyList.begin();
	for (iter; iter != m_EnemyList.end(); iter++)
	{
		if ((*iter) != NULL)
		{
			(*iter)->setscroll_move(move);
		}
	}
}

void EnemyManager::Draw(HDC hdc)
{
	vector<Enemy*>::iterator iter = m_EnemyList.begin();
	for (iter; iter != m_EnemyList.end(); iter++)
	{
		if ((*iter) != NULL && (*iter)->gettype_code() == ENEMY_CODE_POT)
		{
			(*iter)->Draw(hdc);
		}
	}
}

void EnemyManager::B_Draw(HDC hdc)
{
	vector<Enemy*>::iterator iter = m_EnemyList.begin();
	for (iter; iter != m_EnemyList.end(); iter++)
	{
		if ((*iter) != NULL && (*iter)->gettype_code() != ENEMY_CODE_POT)
		{
			(*iter)->B_Draw(hdc);
		}
	}
}

void EnemyManager::F_Draw(HDC hdc)
{
	vector<Enemy*>::iterator iter = m_EnemyList.begin();
	for (iter; iter != m_EnemyList.end(); iter++)
	{
		if ((*iter) != NULL && (*iter)->gettype_code() != ENEMY_CODE_POT)
		{
			(*iter)->F_Draw(hdc);
		}
	}
}

void EnemyManager::Update()
{
	vector<Enemy*>::iterator iter = m_EnemyList.begin();
	for (iter; iter != m_EnemyList.end(); iter++)
	{
		if ((*iter) != NULL)
		{
			(*iter)->Move();
		}
	}
}

void EnemyManager::release()
{
	vector<Enemy*>::iterator iter = m_EnemyList.begin();
	for (iter; iter != m_EnemyList.end(); iter++)
	{
		if ((*iter) != NULL)
		{
			delete (*iter);
			(*iter) = NULL;
		}
	}
	m_EnemyList.clear();
}

bool EnemyManager::CollideCheck(RECT rt)
{
	vector<Enemy*>::iterator iter = m_EnemyList.begin();
	for (iter; iter != m_EnemyList.end(); iter++)
	{
		if ((*iter) != NULL)
		{
			if ((*iter)->CollideCheck(rt))
				return true;
		}
	}
	return false;
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