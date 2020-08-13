#pragma once
#include"BitMap.h"

class Player : public BitMap
{
private:
	static Player* m_this;
	bool m_bjumpflag;
	int m_ijump;
	int m_ivelocity;
	VIEW view;
	int m_ix;
	int m_iy;
	int m_isprite_sequence;
public:
	inline static Player* GetInstance()
	{
		if (m_this == NULL) m_this = new Player;
		return m_this;
	}
	Player();
	~Player();
	inline bool getjumpflag() { return m_bjumpflag; }
	void Init(HWND hWnd, HINSTANCE hInst);
	void Draw(HDC hdc);
	void Move(WPARAM);
	void Jump();
	void Drop();
};

