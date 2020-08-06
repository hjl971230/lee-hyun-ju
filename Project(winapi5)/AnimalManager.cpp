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
	int x = 0;
	int y = 0;
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
		x += 145;
		if ((*iter).getbmpid() == IDB_BITMAP5)
		{
			x = 0;
			y += 235;
		}
		bmpid++;
	}
}

void AnimalManager::NameFactory(TCHAR name[], int bmpid)
{
	switch (bmpid)
	{
	case IDB_BITMAP1:
		wsprintf(name, TEXT("������"));
		break;
	case IDB_BITMAP2:
		wsprintf(name, TEXT("ȣ����"));
		break;
	case IDB_BITMAP3:
		wsprintf(name, TEXT("����"));
		break;
	case IDB_BITMAP4:
		wsprintf(name, TEXT("�ڳ���"));
		break;
	case IDB_BITMAP5:
		wsprintf(name, TEXT("��"));
		break;
	case IDB_BITMAP6:
		wsprintf(name, TEXT("��"));
		break;
	case IDB_BITMAP7:
		wsprintf(name, TEXT("�����"));
		break;
	case IDB_BITMAP8:
		wsprintf(name, TEXT("������"));
		break;
	case IDB_BITMAP9:
		wsprintf(name, TEXT("������"));
		break;
	case IDB_BITMAP10:
		wsprintf(name, TEXT("��"));
		break;
	default:
		break;
	}
}