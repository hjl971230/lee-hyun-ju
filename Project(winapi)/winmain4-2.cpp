#include<windows.h>
#include<math.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimeProc(HWND, UINT, UINT, DWORD);
void CALLBACK MoveProc(HWND, UINT, UINT, DWORD);
void DrawWatch(HDC);
void DrawNiddle(HDC);
HINSTANCE g_hInst;//�۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR lpszClass = TEXT("Clock"); //â�̸�
#define MID_X 100
#define MID_Y 100
#define MIN_X 50
#define MIN_Y 50
#define MAX_X 150
#define MAX_Y 150
int x = 100;
int y = 100;
TCHAR sTime[128] = "\0";
SYSTEMTIME st;
bool xflag = true;
bool yflag = true;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	//WndClass�� �⺻ ������ȯ���� ����� ����ü��. �ɹ������� �ؿ��� ����.
	WndClass.cbClsExtra = 0; //���࿵��
	WndClass.cbWndExtra = 0; //���࿵�� (�Ű�x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//������ ���
	WndClass.hInstance = hInstance;//(���α׷� �ڵ鰪(��ȣ)���)
	WndClass.lpfnWndProc = WndProc;	//���μ��� �Լ� ȣ��
	WndClass.lpszClassName = lpszClass;	//Ŭ���� �̸�
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//�������� ������ ������ ���� �� �ٽ� �׸���.
	RegisterClass(&WndClass);  //������� WidClass�� ���

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))//����ڿ��� �޽����� �޾ƿ��� �Լ�(WM_QUIT �޽��� ���� �� ����)
	{
		TranslateMessage(&Message); //  Ű���� �Է� �޽��� ó���Լ�
		DispatchMessage(&Message); //���� �޽����� WndProc�� �����ϴ� �Լ�
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
	int clockdrawnum = 0;
	TCHAR sdrawTime[128] = "\0";
	switch (iMessage)
	{
	case WM_CREATE://������ ���� �� �Ҵ�, �ʱ�ȭ ��
		SetTimer(hWnd, 1, 1000, TimeProc);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		SetTimer(hWnd, 2, 50, MoveProc);
		SendMessage(hWnd, WM_TIMER, 2, 0);
		return 0;
	case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
	case WM_TIMER:
		GetLocalTime(&st);
		if (st.wHour >= 12)
			st.wHour -= 12;
		wsprintf(sTime, TEXT("���� �ð��� %d:%d:%d�Դϴ�."), st.wHour, st.wMinute, st.wSecond);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_CENTER);
		TextOut(hdc, 100, 100, sTime, lstrlen(sTime));
		DrawWatch(hdc);
		DrawNiddle(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
}

void CALLBACK TimeProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	GetLocalTime(&st);
	if (st.wHour >= 12)
		st.wHour -= 12;
	wsprintf(sTime, TEXT("���� �ð��� %d:%d:%d�Դϴ�."), st.wHour, st.wMinute, st.wSecond);
	InvalidateRect(hWnd, NULL, TRUE);
}

void CALLBACK MoveProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	if (x <= MIN_X)xflag = true;
	else if (x >= MAX_X)xflag = false;
	if (y <= MIN_Y)yflag = false;
	else if (y >= MAX_Y)yflag = true;

	if (xflag)x++;
	else x--;
	if (yflag)y--;
	else y++;

	InvalidateRect(hWnd, NULL, TRUE);
}

void DrawWatch(HDC hdc)
{
	int radius = 50;
	int c_x = 0;
	int c_y = 0;
	int clockdrawnum = 0;
	TCHAR sdrawTime[128] = "\0";
	for (int i = 0; i <= 360; i++)
	{
		c_x = cos((i) * 3.14 / 180) * (radius + 24);
		c_y = sin((i) * 3.14 / 180) * (radius + 24);
		SetPixel(hdc, x + 200 + c_x, y + 200 + c_y, RGB(0, 0, 0));
	}
	for (int i = -90; i <= 270; i++)
	{
		c_x = cos((i) * 3.14 / 180) * (radius + 14);
		c_y = sin((i) * 3.14 / 180) * (radius + 14);
		MoveToEx(hdc, x + 200, y + 200, NULL);
		if (i % 30 == 0)
		{
			wsprintf(sdrawTime, TEXT("%d"), clockdrawnum);
			TextOut(hdc, x + 200 + c_x, y + 200 + c_y - 7, sdrawTime, lstrlen(sdrawTime));
			clockdrawnum++;
		}
	}
}

void DrawNiddle(HDC hdc)
{
	int radius = 50;
	int c_x = 0;
	int c_y = 0;
	float hour_go = 0;
	for (int i = -90; i <= 270; i++)
	{
		c_x = cos((i) * 3.14 / 180) * radius;
		c_y = sin((i) * 3.14 / 180) * radius;
		MoveToEx(hdc, x + 200, y + 200, NULL);
		if ((i + 90) % 30 == 0 && (i + 90) / 30 == st.wHour)
		{
			hour_go = st.wMinute / 2;
			if (st.wHour > 6) hour_go *= -1;
			MoveToEx(hdc, x + 200, y + 200, NULL);
			LineTo(hdc, x + 200 + c_x + hour_go, y + 200 + c_y + hour_go);
		}
		if ((i + 90) % 6 == 0 && (i + 90) / 6 == st.wMinute)
		{
			MoveToEx(hdc, x + 200, y + 200, NULL);
			LineTo(hdc, x + 200 + c_x, y + 200 + c_y);
		}
		if ((i + 90) % 6 == 0 && (i + 90) / 6 == st.wSecond)
		{
			MoveToEx(hdc, x + 200, y + 200, NULL);
			LineTo(hdc, x + 200 + c_x, y + 200 + c_y);
		}
	}
}