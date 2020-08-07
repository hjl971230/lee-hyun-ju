#include "AnimalManager.h"

AnimalManager* AnimalManager::m_AnimalManager_this = NULL;

AnimalManager::AnimalManager()
{
	vectorinit();
}

AnimalManager::~AnimalManager()
{
	vec_animal.clear();
}

void AnimalManager::vectorinit()
{
	Animal tmp;
	int bmpid = IDB_BITMAP1;
	int x = CARD_DRAW_SIZE_X;
	int y = DRAW_ADD_POINT_Y;
	TCHAR name[128];
	vec_animal.reserve(10);
	vec_animal.assign(10, tmp);
	vector<Animal>::iterator iter = vec_animal.begin();
	for (iter; iter != vec_animal.end(); iter++)
	{
		tmp.setbmpid(bmpid);
		tmp.setPoint(x, y);
		NameFactory(name, bmpid);
		tmp.setName(name);
		(*iter) = tmp;
		x += CARD_DRAW_SIZE_X;
		if ((*iter).getbmpid() == IDB_BITMAP5 || (*iter).getbmpid() == IDB_BITMAP10)
		{
			x = CARD_DRAW_SIZE_X;
			y += CARD_DRAW_SIZE_Y + DRAW_ADD_POINT_Y;
		}
		bmpid++;
		if (bmpid == IDB_BITMAP11) bmpid = IDB_BITMAP1;
	}
}

void AnimalManager::NameFactory(TCHAR name[], int bmpid)
{
	switch (bmpid)
	{
	case IDB_BITMAP1:
		wsprintf(name, TEXT("강아지"));
		break;
	case IDB_BITMAP2:
		wsprintf(name, TEXT("호랑이"));
		break;
	case IDB_BITMAP3:
		wsprintf(name, TEXT("오리"));
		break;
	case IDB_BITMAP4:
		wsprintf(name, TEXT("코끼리"));
		break;
	case IDB_BITMAP5:
		wsprintf(name, TEXT("소"));
		break;
	case IDB_BITMAP6:
		wsprintf(name, TEXT("말"));
		break;
	case IDB_BITMAP7:
		wsprintf(name, TEXT("고양이"));
		break;
	case IDB_BITMAP8:
		wsprintf(name, TEXT("원숭이"));
		break;
	case IDB_BITMAP9:
		wsprintf(name, TEXT("개구리"));
		break;
	case IDB_BITMAP10:
		wsprintf(name, TEXT("닭"));
		break;
	default:
		break;
	}
}