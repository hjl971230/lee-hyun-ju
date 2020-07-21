#pragma once
#include"Word.h"

class WordManager
{
private:
	static WordManager* m_WordManager_this;
public:
	static WordManager* GetInstance()
	{
		if (m_WordManager_this == NULL)
			m_WordManager_this = new WordManager;
		return m_WordManager_this;
	}
};

