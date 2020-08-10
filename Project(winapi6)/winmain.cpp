#include "GameManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//�۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR lpszClass = TEXT("Image"); //â�̸�
TCHAR sTime[128];
int min = 0;
int sec = 0;
int timesize = 12;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	srand(time(NULL));
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
	GameManager::GetInstance()->Init(hWnd,g_hInst);
	GameManager::GetInstance()->GameInit(hWnd,g_hInst);
	while (GetMessage(&Message, NULL, 0, 0))//����ڿ��� �޽����� �޾ƿ��� �Լ�(WM_QUIT �޽��� ���� �� ����)
	{
		TranslateMessage(&Message); //  Ű���� �Է� �޽��� ó���Լ�
		DispatchMessage(&Message); //���� �޽����� WndProc�� �����ϴ� �Լ�
	}
	GameManager::GetInstance()->Release();
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hWnd);
	PAINTSTRUCT ps;
	int mouse_x = 0;
	int mouse_y = 0;
	TCHAR Message[128];
	wsprintf(Message, TEXT("\0"));
	switch (iMessage)
	{
	case WM_CREATE://������ ���� �� �Ҵ�, �ʱ�ȭ ��
		SetTimer(hWnd, 1, 1000, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
		KillTimer(hWnd, 1);
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
		return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
	case WM_TIMER:
		sec++;
		if (sec == 60)
		{
			sec = 0;
			min++;
		}
		wsprintf(sTime, TEXT("�ð� : %d : %d"), min, sec);
		if (sec >= 10 && min >= 10)
			timesize = 14;
		if (sec >= 10 || min >= 10)
			timesize = 13;
		else timesize = 12;
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_LBUTTONDOWN:
		mouse_x = LOWORD(lParam);
		mouse_y = HIWORD(lParam);
		GameManager::GetInstance()->Click(hdc, g_hInst, mouse_x, mouse_y);
		if (GameManager::GetInstance()->GameCheck())
		{
			if (MessageBox(hWnd, TEXT("OK : ���� ���� CANCEL : ����"), TEXT("MessageBox"), MB_OKCANCEL) == IDOK)
			{
				GameManager::GetInstance()->Init(hWnd, g_hInst);
				GameManager::GetInstance()->GameInit(hWnd, g_hInst);
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, CARD_DRAW_SIZE_X - DRAW_ADD_POINT_X, DRAW_ADD_POINT_Y * 0.3,
			CARD_DRAW_SIZE_X + DRAW_ADD_POINT_X * 6 + CARD_DRAW_SIZE_X * 5,
			DRAW_ADD_POINT_Y * 1.3 + CARD_DRAW_SIZE_Y * 4 + DRAW_ADD_POINT_Y * 4);
		GameManager::GetInstance()->GameDraw(hdc);
		Rectangle(hdc, 700 + CARD_DRAW_SIZE_X - DRAW_ADD_POINT_X, DRAW_ADD_POINT_Y * 0.3,
			800 + CARD_DRAW_SIZE_X + DRAW_ADD_POINT_X * 4 + CARD_DRAW_SIZE_X * 5,
			DRAW_ADD_POINT_Y * 1.3 + CARD_DRAW_SIZE_Y * 4 + DRAW_ADD_POINT_Y * 4);
		wsprintf(Message, TEXT("����  ī��"));
		TextOut(hdc, 700 + (CARD_DRAW_SIZE_X + DRAW_ADD_POINT_X * 2 + CARD_DRAW_SIZE_X * 5) / 2, DRAW_ADD_POINT_Y * 2, Message, 10);
		TextOut(hdc, 700 + (CARD_DRAW_SIZE_X + DRAW_ADD_POINT_X * 2 + CARD_DRAW_SIZE_X * 5) / 2, CARD_DRAW_SIZE_Y * 3 + DRAW_ADD_POINT_Y * 3, sTime, timesize);
		GameManager::GetInstance()->Draw(hdc);
		GameManager::GetInstance()->Matching(hdc, g_hInst);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
}