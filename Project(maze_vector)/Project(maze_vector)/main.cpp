#include"GameManager.h"

void main()
{
	srand(time(NULL));
	GameManager::GetInstance()->PlayGame();
	delete GameManager::GetInstance();
}