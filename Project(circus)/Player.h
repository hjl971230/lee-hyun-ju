#pragma once
#include"BitMap.h"
#include"Item.h"

class Player
{
private:
	static Player* m_this;
	bool m_bjumpflag;
	int m_ijump_x;
	int m_ijump_y;
	int m_ivelocity;
	POINT m_point;
	int m_isprite_sequence;
	int m_ichargejump;
	int m_imotion_num;
	int m_iwinmotion_num;
	BitMap m_MotionBitMap[PLAYER_MOTION_SIZE];
	BitMap m_WinMotionBitMap[PLAYER_WIN_MOTION_SIZE];
	BitMap m_DieBitMap;
	int m_iscore;
	int m_ilife;
	RECT collider;
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
	inline void setx(int i) { m_point.x = i; }
	inline void sety(int i) { m_point.y = i; }
	inline int getx() { return m_point.x; }
	inline int gety() { return m_point.y; }
	inline POINT getPoint() { return m_point; }
	inline void setlife(int i) { m_ilife = i; }
	inline int getlife() { return m_ilife; }
	inline void setscore(int i) { m_iscore = i; }
	inline int getscore() { return m_iscore; }
	inline RECT getcollider() { return collider; }
	void UpdateCollider();
	BitMap getWinMotionBitMap() { return m_WinMotionBitMap[0]; }
	void Init(HDC hdc, HINSTANCE hInst);
	void Draw(HDC hdc);
	void WinDraw(HDC hdc);
	void DieDraw(HDC hdc);
	void KeyInput();
	void Jump();
};

