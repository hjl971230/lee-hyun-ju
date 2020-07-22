#pragma once
#include"Word.h"

class WordManager
{
private:
	static WordManager* m_WordManager_this;
	int m_iwordcount;
	int m_ispeed;
	int m_iOldDropClock;
	Word* m_Word;
	bool m_bdropflag;
public:
	WordManager();
	~WordManager();
	static WordManager* GetInstance()
	{
		if (m_WordManager_this == NULL)
			m_WordManager_this = new WordManager;
		return m_WordManager_this;
	}
	void Wordload();
	void Relese(Word* Node);
	inline Word* GetWord() { return m_Word; }
	inline int Getwordcount() { return m_iwordcount; }
	bool WordDrop();
	inline void SetSpeed(int i) { m_ispeed = i; }
	inline int GetSpeed() { return m_ispeed; }
	inline void SetOldClock() { m_iOldDropClock = clock(); }
	void Reversehideflag();
	void WordCreate();
	void WordClear();
	void SpeedUpDown(bool b);
	inline void Stop(bool b) { m_bdropflag = b; }
	void ItemOn(ITEM item, int& i, int stage);
	void ItemOff(ITEM item);
};

