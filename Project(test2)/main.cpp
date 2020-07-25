#include "GameManager.h"

void main()
{
	srand(time(NULL));
	GameManager::GetInstance()->GameMain();
	delete GameManager::GetInstance();
}