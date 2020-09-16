#pragma once
#include"Enemy.h"

class EnemyManager
{
private:
	static EnemyManager* m_this;
	vector<Enemy*> m_EnemyList;
public:
	static EnemyManager* GetInstance()
	{
		if (m_this == NULL)
			m_this = new EnemyManager;
		return m_this;
	}
	EnemyManager();
	~EnemyManager();
	void Init(HDC, HINSTANCE);
	void Draw(HDC);
	void B_Draw(HDC);
	void F_Draw(HDC);
	void release();
	void Update();
	void PointUpdate(int);
	void PointSetting();
	bool CollideCheck(RECT);
	Enemy* EnemyFactory(HDC, HINSTANCE, int);
};

