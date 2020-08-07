#include "AnimalManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//�۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR lpszClass = TEXT("Image"); //â�̸�

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

	while (GetMessage(&Message, NULL, 0, 0))//����ڿ��� �޽����� �޾ƿ��� �Լ�(WM_QUIT �޽��� ���� �� ����)
	{
		TranslateMessage(&Message); //  Ű���� �Է� �޽��� ó���Լ�
		DispatchMessage(&Message); //���� �޽����� WndProc�� �����ϴ� �Լ�
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
	case WM_CREATE://������ ���� �� �Ҵ�, �ʱ�ȭ ��
		return 0;
	case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
		return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
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
				wsprintf(Message, TEXT("�� ���Դϴ�"));
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
		wsprintf(Message, TEXT("����  ī��\0"));
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
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
}