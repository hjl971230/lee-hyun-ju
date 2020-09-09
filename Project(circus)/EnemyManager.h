#pragma once
#include"Enemy.h"

class EnemyManager
{
private:
	static EnemyManager* m_this;
	vector<Enemy*> m_vecEnemyList;
public:
	static EnemyManager* GetInstance()
	{
		if (m_this == NULL)
			m_this = new EnemyManager;
		return m_this;
	}
	EnemyManager();
	~EnemyManager();
};

