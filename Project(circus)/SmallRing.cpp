#include"Enemy.h"

SmallRing::SmallRing(HDC hdc, HINSTANCE hInst)
{
	m_itype_code = ENEMY_CODE_SMALLRING;
}

SmallRing::~SmallRing()
{

}

void SmallRing::Init(HDC hdc, HINSTANCE hInst)
{

}

void SmallRing:: Move()
{

}

bool SmallRing::CollideCheck()
{
	//Ÿ�� ���� : x^ / a^ + y^ / b^ = 1
		//x^ + y^ * a^ / b^ = a^
		//x^ * b^ + y^ * a^ = a^ * b^
	//for (int x = -a; x <= a; x++)
		//for (int y = -b; y <= b; y++)
			//if (a * a * b * b > x * x * b * b + y * y * a * a)
}