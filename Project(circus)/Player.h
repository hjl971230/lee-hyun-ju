#pragma once
#include"BitMap.h"

class Player : public BitMap
{
private:
	static Player* m_this;
	bool m_bjumpflag;
	int m_ijump_x;
	int m_ijump_y;
	int m_ivelocity;
	VIEW view;
	int m_ix;
	int m_iy;
	int m_isprite_sequence;
	int m_ichargejump;
public:
	inline static Player* GetInstance()
	{
		if (m_this == NULL) m_this = new Player;
		return m_this;
	}
	Player();
	~Player();
	inline bool getjumpflag() { return m_bjumpflag; }
	inline void setjumpflag(bool b) { m_bjumpflag = b; }
	inline void setx(int i) { m_ix = i; }
	inline void sety(int i) { m_iy = i; }
	inline int getx() { return m_ix; }
	inline int gety() { return m_iy; }
	void Init(HDC hdc, HINSTANCE hInst);
	void Draw(HDC hdc);
	void KeyDownMove(WPARAM wParam);
	void Jump();
};

