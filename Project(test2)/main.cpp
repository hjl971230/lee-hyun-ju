#include<iostream>
#include<vector>
#include<time.h>
#include<conio.h>
#include<fstream>

#define TRAP 9
#define PLAYER 2
#define WALL 1
#define EMPTY 0
using namespace std;

void main()
{
	srand(time(NULL));
	vector<vector<int>> map;
	vector<int> vectmp;
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
		
		for (vector<vector<int>>::iterator iter_height = map.begin(); iter_height != map.end(); iter_height++)
		{
			(*iter_height).assign(width, 0);
			for (vector<int>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
			{
				load >> tmp;
				(*iter_width) = tmp;
			}
		}
		load.close();
	}
	
}