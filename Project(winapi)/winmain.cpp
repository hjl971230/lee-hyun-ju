#include<windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//�۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR lpszClass = TEXT("Circle"); //â�̸�

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
	int radius = 21;
	PAINTSTRUCT ps;
	int a = 20;
	int b = 40;
	switch (iMessage)
	{
	case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
		return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		SetTextAlign(hdc, TA_TOP | TA_RIGHT);
		TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15);
		ReleaseDC(hWnd, hdc);
		return 0; 
	case WM_RBUTTONDOWN:
		hdc = GetDC(hWnd);
		SetTextAlign(hdc, TA_BOTTOM | TA_LEFT);
		TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//�� ���� : r * r == (x - r)^ + (y - r)^
		for (int x = -radius; x <= radius * 2; x++)//x, y ������ * 2 == ������ŭ
			for (int y = -radius; y <= radius * 2; y++)
				if (radius * radius > (x - radius) * (x - radius) + (y - radius) * (y - radius))//�ش� ������ ������ �ȿ��� ���� �׸�
					SetPixel(hdc, 120 + x, y, RGB(0, 0, 0));

		//Ÿ�� ���� : x^ / a^ + y^ / b^ = 1
		//x^ + y^ * a^ / b^ = a^
		//x^ * b^ + y^ * a^ = a^ * b^
		for (int x = -a; x <= a; x++)
			for (int y = -b; y <= b; y++)
				if (a * a * b * b > x * x * b * b + y * y * a * a)
					SetPixel(hdc, 120 + x, 100 + y, RGB(0, 0, 0));

		//Ellipse(hdc, 100, 100, 200, 200);
		//Ellipse(hdc, 220, 100, 400, 200);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
}