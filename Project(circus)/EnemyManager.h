#pragma once
#include"Enemy.h"

class EnemyManager
{
private:
	static EnemyManager* m_this;
	
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

