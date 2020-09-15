#include "Enemy.h"

Ring::Ring(HDC hdc, HINSTANCE hInst)
{
	m_itype_code = ENEMY_CODE_RING;
}

Ring::~Ring()
{

}

void Ring::Init(HDC hdc, HINSTANCE hInst)
{

}

void Ring::Move()
{

}

bool Ring::CollideCheck()
{
	//타원 공식 : x^ / a^ + y^ / b^ = 1
		//x^ + y^ * a^ / b^ = a^
		//x^ * b^ + y^ * a^ = a^ * b^
	//for (int x = -a; x <= a; x++)
		//for (int y = -b; y <= b; y++)
			//if (a * a * b * b > x * x * b * b + y * y * a * a)
}