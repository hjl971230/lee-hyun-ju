#include "GameManager.h"

void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_crtBreakAlloc = 469;
	srand(time(NULL));
	GameManager::GetInstance();
	delete GameManager::GetInstance();
}