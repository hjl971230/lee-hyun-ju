#include<windows.h>
#include<math.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//글로벌 인스턴스핸들값
LPCTSTR lpszClass = TEXT("move & jump"); //창이름

#define MOVESPEED 5
#define GRAVITY 10
enum VIEW
{
	VIEW_DOWN = 0,
	VIEW_UP = 1,
	VIEW_LEFT = 2,
	VIEW_RIGHT = 3,
};

bool jumpflag = false;
int jump = 0;
int velocity = 0;
VIEW view = VIEW_DOWN;
int x = 100;
int y = 100;
int sprite_sequence = 0;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
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
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HDC hMemdc;
	BITMAP bit;
	HBITMAP myBitmap, oldBitmap;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_CREATE://윈도우 생성 시 할당, 초기화 등
		return 0;
	case WM_DESTROY:// 윈도우가 파괴되었다는 메세지
		PostQuitMessage(0); //GetMessage함수에 WM_QUIT 메시지를 보낸다.
		KillTimer(hWnd, 1);
		return 0; //WndProc의 Switch는 break 대신 return 0; 를 쓴다.
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			view = VIEW_LEFT;
			if(x - MOVESPEED >= 0) 
				x -= MOVESPEED;
			break;
		case VK_RIGHT:
			view = VIEW_RIGHT;
			if (x + MOVESPEED <= 1300) 
				x += MOVESPEED;
			break;
		case VK_UP:
			view = VIEW_UP;
			if (y - MOVESPEED >= 0) 
				y -= MOVESPEED;
			break;
		case VK_DOWN:
			view = VIEW_DOWN;
			if (y + MOVESPEED <= 600) 
				y += MOVESPEED;
			break;
		case VK_SPACE:
			jumpflag = true;
			break;
		}
		if (wParam != VK_SPACE)
		{
			sprite_sequence++;
			if (sprite_sequence >= 4)
				sprite_sequence = 1;
		}
		else sprite_sequence = 2;
		InvalidateRect(hWnd, NULL, TRUE);
	case WM_PAINT:
		if (jumpflag)
		{
			if (velocity <= 0)
			{
				velocity = 30;
				jumpflag = false;
				jump = 0;
			}
			jump -= velocity;
			velocity -= GRAVITY;
		}
		hdc = BeginPaint(hWnd, &ps);
		hMemdc = CreateCompatibleDC(hdc);
		myBitmap = (HBITMAP)LoadImage(NULL, "image.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		oldBitmap = (HBITMAP)SelectObject(hMemdc, myBitmap);
		GetObject(myBitmap, sizeof(bit), &bit);
		TransparentBlt(hdc, x, y + jump, (bit.bmWidth / 4), (bit.bmHeight / 4), hMemdc,
			(bit.bmWidth / 4) * sprite_sequence, (bit.bmHeight / 4) * view, (bit.bmWidth / 4), (bit.bmHeight / 4),
			RGB(255, 0, 255));
		SelectObject(hMemdc, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(hMemdc);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case에 있는 메시지를 제외한 나머지 메시지를 처리한다.
}