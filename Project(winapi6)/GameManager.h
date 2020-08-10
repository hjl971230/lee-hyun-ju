#pragma once
#include"Animal.h"

class GameManager
{
private:
	static GameManager* m_pThis;
	vector<Animal> m_bt;
	vector<Animal> m_game_bt;
	Animal* match1;
	Animal* match2;
public:
	GameManager();
	~GameManager();
	static GameManager* GetInstance()
	{
		if (m_pThis == NULL)
			m_pThis = new GameManager;
		return m_pThis;
	}
	void Init(HWND hWnd, HINSTANCE hInst);
	void Draw(HDC hdc);
	void GameInit(HWND hWnd, HINSTANCE hInst);
	void GameDraw(HDC hdc);
	void Release();
	void NameFactory(TCHAR name[], int bmpid);
	void Click(HDC hdc, HINSTANCE hInst, int x, int y);
	void Matching(HDC hdc, HINSTANCE hInst);
	bool GameCheck();
};

