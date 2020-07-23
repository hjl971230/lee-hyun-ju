#pragma once
#include"Mecro.h"
#include"MapDraw.h"
#include"Item.h"

class Word
{
protected:
	int m_ix;
	int m_iy;
	bool m_bitemflag;
	bool m_bhideflag;
	bool m_bstrflag;
	string m_str;
	Item* m_Item;
public:
	Word();
	~Word();
	void draw();
	void drop();
	void Live();
	void Die();
	inline void Setstr(string str) { m_str = str; }
	inline string Getstr() { return m_str; }
	inline void Setx(int x) { m_ix = x; }
	inline void Sety(int y) { m_iy = y; }
	inline int Getx() { return m_ix; }
	inline int Gety() { return m_iy; }
	inline bool Getstrflag() { return m_bstrflag; }
	inline void Sethideflag(bool b) { m_bhideflag = b; }
	inline bool Gethideflag() { return m_bhideflag; }
	inline void SetItemflag(bool b) { m_bitemflag = b; }
	inline bool GetItemflag() { return m_bitemflag; }
	inline void SetItem(Item* i) { m_Item = i; }
	inline Item* GetItem() { return m_Item; }
	inline void deleteItem()
	{
		if (m_Item != NULL)
			delete m_Item;
	}
	void MakeItem();
};

