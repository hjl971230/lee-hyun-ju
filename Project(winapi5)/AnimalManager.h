#pragma once
#include"Animal.h"
class AnimalManager
{
private:
	static AnimalManager* m_AnimalManager_this;
	vector<Animal> vec_animal;
public:
	static AnimalManager* GetInstance()
	{
		if (m_AnimalManager_this == NULL)
			m_AnimalManager_this = new AnimalManager;
		return m_AnimalManager_this;
	}
	AnimalManager();
	~AnimalManager();
	void vectorinit();
	void NameFactory(TCHAR name[], int bmpid);
	inline vector<Animal> getvec_animal() { return vec_animal; }
};

