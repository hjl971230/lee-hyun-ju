#include<windows.h>
#include<math.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//글로벌 인스턴스핸들값
LPCTSTR lpszClass = TEXT("Shapes"); //창이름
#define MIN_RECT_X 50
#define MIN_RECT_Y 50
#define MAX_RECT_X 500
#define MAX_RECT_Y 500
int x = 0;
int y = 0;
bool flag = true;

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
	int radius = 50;
	int c_x = 0;
	int c_y = 0;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_DESTROY:// 윈도우가 파괴되었다는 메세지
		PostQuitMessage(0); //GetMessage함수에 WM_QUIT 메시지를 보낸다.
		return 0; //WndProc의 Switch는 break 대신 return 0; 를 쓴다.
	/*case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			x -= 10;
			break;
		case VK_RIGHT:
			x += 10;
			break;
		case VK_UP:
			y -= 10;
			break;
		case VK_DOWN:
			y += 10;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;*/
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_RBUTTONDOWN:
		if (MessageBox(hWnd, TEXT("ok : 사각형 cancel : 원"), TEXT("Change"), MB_YESNO) == IDYES)
			flag = false;
		else
			flag = true;
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//sin(θ) = y / d == y = sin(θ) * d  
		//cos(θ) = x / d == x = cos(θ) * d
		Rectangle(hdc, MIN_RECT_X, MIN_RECT_Y, MAX_RECT_X, MAX_RECT_Y);
		if (x < MIN_RECT_X * 2)
			x = MIN_RECT_X * 2;
		else if (x > MAX_RECT_X - MIN_RECT_X)
			x = MAX_RECT_X - MIN_RECT_X;
		if (y < MIN_RECT_Y * 2)
			y = MIN_RECT_Y * 2;
		else if (y > MAX_RECT_Y - MIN_RECT_Y)
			y = MAX_RECT_Y - MIN_RECT_Y;
		if (flag)
		{
			for (int i = 0; i <= 360; i++)
			{
				c_x = cos(i) * radius;
				c_y = sin(i) * radius;
				SetPixel(hdc, x + c_x, y + c_y, RGB(0, 0, 0));
			}
		}
		else 
			Rectangle(hdc, x - 50, y - 50, x + 50, y + 50);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case에 있는 메시지를 제외한 나머지 메시지를 처리한다.
}