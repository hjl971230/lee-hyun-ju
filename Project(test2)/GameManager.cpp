#include "GameManager.h"

GameManager* GameManager::m_GM_this = NULL;

GameManager::GameManager()
{
	m_itrapCount = 0;
}

GameManager::~GameManager()
{

}

void GameManager::mapinit()
{
	ifstream load;
	int trap_count = 0;
	int width = 0;
	int height = 0;
	int tmp;
	vector<blockinfo> vectmp;
	ifstream load;
	load.open("map1.txt");
	if (load.is_open())
	{
		load >> trap_count;
		m_itrapCount = trap_count;
		load >> width;
		load >> height;
		m_vecmap.reserve(height + 2);
		vectmp.reserve(width + 2);
		m_vecmap.assign(height, vectmp);

		for (vector<vector<blockinfo>>::iterator iter_height = m_vecmap.begin(); iter_height != m_vecmap.end(); iter_height++)
		{
			//(*iter_height).assign(width + 2);
			for (vector<blockinfo>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
			{
				load >> tmp;
				(*iter_width).block = to_string(tmp);
			}
		}
		while (trap_count != 0)
		{
			trap_count--;
		}
	}
}