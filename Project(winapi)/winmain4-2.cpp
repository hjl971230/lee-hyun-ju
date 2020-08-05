#include<windows.h>
#include<math.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimeProc(HWND, UINT, UINT, DWORD);
HINSTANCE g_hInst;//�۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR lpszClass = TEXT("Shapes"); //â�̸�
int x = 200;
int y = 200;
TCHAR sTime[128] = "\0";
SYSTEMTIME st;

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
		return 0;
	case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
		KillTimer(hWnd, 1);
		return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
	case WM_TIMER:
		/*GetLocalTime(&st);
		wsprintf(sTime, TEXT("���� �ð��� %d:%d:%d�Դϴ�."), st.wHour, st.wMinute, st.wSecond);
		InvalidateRect(hWnd, NULL, TRUE);*/
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_CENTER | TA_BOTTOM);
		TextOut(hdc, 100, 100, sTime, lstrlen(sTime));
		for (int i = 0; i <= 360; i++)
		{
			c_x = cos((i) * 3.14 / 180) * radius;
			c_y = sin((i) * 3.14 / 180) * radius;
			SetPixel(hdc, x + 200 + c_x, y + 200 + c_y, RGB(0, 0, 0));
			if (i % 30 == 0)
			{
				wsprintf(sdrawTime, TEXT("%d"), clockdrawnum);
				TextOut(hdc, x + 200 + c_x, y + 200 + c_y, sdrawTime, lstrlen(sdrawTime));
				clockdrawnum++;
			}
		}
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
}

void CALLBACK TimeProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	GetLocalTime(&st);
	wsprintf(sTime, TEXT("���� �ð��� %d:%d:%d�Դϴ�."), st.wHour, st.wMinute, st.wSecond);
	InvalidateRect(hWnd, NULL, TRUE);
}