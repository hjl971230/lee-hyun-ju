#include<windows.h>
#include<math.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//�۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR lpszClass = TEXT("Shapes"); //â�̸�
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
	switch (iMessage)
	{
	case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
		return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
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
		if (MessageBox(hWnd, TEXT("ok : �簢�� cancel : ��"), TEXT("Change"), MB_YESNO) == IDYES)
			flag = false;
		else
			flag = true;
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//sin(��) = y / d == y = sin(��) * d  
		//cos(��) = x / d == x = cos(��) * d
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
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
}