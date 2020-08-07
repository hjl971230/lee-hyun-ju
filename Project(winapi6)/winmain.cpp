#include "AnimalManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//글로벌 인스턴스핸들값
LPCTSTR lpszClass = TEXT("Image"); //창이름

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	srand(time(NULL));
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	//WndClass는 기본 윈도우환경을 만드는 구조체다. 맴버변수는 밑에와 같다.
	WndClass.cbClsExtra = 0; //예약영역
	WndClass.cbWndExtra = 0; //예약영역 (신경x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//아이콘 모양
	WndClass.hInstance = hInstance;//(프로그램 핸들값(번호)등록)
	WndClass.lpfnWndProc = WndProc;	//프로세스 함수 호출
	WndClass.lpszClassName = lpszClass;	//클레스 이름
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//윈도우의 수직과 수평이 변경 시 다시 그린다.
	RegisterClass(&WndClass);  //만들어진 WidClass를 등록

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))//사용자에게 메시지를 받아오는 함수(WM_QUIT 메시지 받을 시 종료)
	{
		TranslateMessage(&Message); //  키보드 입력 메시지 처리함수
		DispatchMessage(&Message); //받은 메시지를 WndProc에 전달하는 함수
	}
	delete AnimalManager::GetInstance();
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memDC;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	HBITMAP myBitmap, oldBitmap;
	int mouse_x = 0;
	int mouse_y = 0;
	TCHAR Message[128];
	vector<Animal> tmp = AnimalManager::GetInstance()->getvec_animal();
	vector<Animal>::iterator iter = tmp.begin();
	switch (iMessage)
	{
	case WM_CREATE://윈도우 생성 시 할당, 초기화 등
		return 0;
	case WM_DESTROY:// 윈도우가 파괴되었다는 메세지
		PostQuitMessage(0); //GetMessage함수에 WM_QUIT 메시지를 보낸다.
		return 0; //WndProc의 Switch는 break 대신 return 0; 를 쓴다.
	case WM_LBUTTONDOWN:
		mouse_x = LOWORD(lParam);
		mouse_y = HIWORD(lParam);
		for (iter; iter != tmp.end(); iter++)
		{
			if (((*iter).getPoint().x <= mouse_x && mouse_x <= (*iter).getPoint().x + CARD_DRAW_SIZE_X)
				&& ((*iter).getPoint().y <= mouse_y && mouse_y <= (*iter).getPoint().y + CARD_DRAW_SIZE_Y))
			{
				wsprintf(Message, (*iter).getName());
				break;
			}	
			else
				wsprintf(Message, TEXT("빈 곳입니다"));
		}
		MessageBox(hWnd, Message, TEXT("MessageBox"), MB_OK);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, CARD_DRAW_SIZE_X - DRAW_ADD_POINT_X, DRAW_ADD_POINT_Y * 0.3, 
			CARD_DRAW_SIZE_X + DRAW_ADD_POINT_X + CARD_DRAW_SIZE_X * 5, 
			DRAW_ADD_POINT_Y * 1.3 + CARD_DRAW_SIZE_Y * 4 + DRAW_ADD_POINT_Y * 4);
		memDC = CreateCompatibleDC(hdc);
		for (iter = tmp.begin(); iter != tmp.end(); iter++)
		{
			myBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE((*iter).getbmpid()));
			oldBitmap = (HBITMAP)SelectObject(memDC, myBitmap);
			StretchBlt(hdc, (*iter).getPoint().x, (*iter).getPoint().y, CARD_DRAW_SIZE_X, CARD_DRAW_SIZE_Y, memDC, 0, 0, CARD_SIZE_X, CARD_SIZE_Y, SRCCOPY);
			SelectObject(memDC, oldBitmap);
			DeleteObject(myBitmap);
		}
		Rectangle(hdc, 800 + CARD_DRAW_SIZE_X - DRAW_ADD_POINT_X, DRAW_ADD_POINT_Y * 0.3,
			800 + CARD_DRAW_SIZE_X + DRAW_ADD_POINT_X + CARD_DRAW_SIZE_X * 5,
			DRAW_ADD_POINT_Y * 1.3 + CARD_DRAW_SIZE_Y * 4 + DRAW_ADD_POINT_Y * 4);
		wsprintf(Message, TEXT("남은  카드\0"));
		TextOut(hdc, 800 + (CARD_DRAW_SIZE_X + DRAW_ADD_POINT_X + CARD_DRAW_SIZE_X * 5) / 2, DRAW_ADD_POINT_Y * 2, Message, 6);
		for (iter = tmp.begin(); iter != tmp.end(); iter++)
		{
			myBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE((*iter).getbmpid()));
			oldBitmap = (HBITMAP)SelectObject(memDC, myBitmap);
			StretchBlt(hdc, 800 + (*iter).getPoint().x, 50 + (*iter).getPoint().y, CARD_DRAW_SIZE_X, CARD_DRAW_SIZE_Y, memDC, 0, 0, CARD_SIZE_X, CARD_SIZE_Y, SRCCOPY);
			SelectObject(memDC, oldBitmap);
			DeleteObject(myBitmap);
			if ((*iter).getbmpid() == IDB_BITMAP10) break;
		}
		DeleteDC(memDC);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case에 있는 메시지를 제외한 나머지 메시지를 처리한다.
}