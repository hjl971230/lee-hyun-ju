#include "GameManager.h"

void main()
{
	srand(time(NULL));
	GameManager::GetInstance();
	delete GameManager::GetInstance();
	/*vector<vector<blockinfo>> map;
	vector<blockinfo> vectmp;
	int width = 0, height = 0;
	int tmp = 0;
	ifstream load;
	load.open("map1.txt");
	if (load.is_open())
	{
		load >> width;
		load >> height;
		map.reserve(height);
		vectmp.reserve(width);
		map.assign(height, vectmp);
		
		for (vector<vector<blockinfo>>::iterator iter_height = map.begin(); iter_height != map.end(); iter_height++)
		{
			(*iter_height).assign(width);
			for (vector<blockinfo>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
			{
				load >> tmp;
				(*iter_width) = tmp;
			}
		}
		load.close();
	}*/
}