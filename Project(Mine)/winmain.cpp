#include"GameManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MineSweeper");
INT_PTR CALLBACK SettingDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
HDC hdc;
HWND r1, r2, r3;
enum
{
	ID_R1 = 101,
	ID_R2,
	ID_R3,
};
int num = ID_R1;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	srand(time(NULL));
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;

	//메뉴 리소스를 작성해서 윈도우 클래스에 배치
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	hdc = GetDC(hWnd);
	GameManager::GetInstance()->Init(hdc, g_hInst);
	while (true)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			InvalidateRect(hWnd, NULL, FALSE);
		}
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int x = 0, y = 0;
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_MENU_RESTART:
			MessageBox(hWnd, TEXT("Restart"), TEXT("restart"), MB_OK);
			break;
		case ID_MENU_EXIT:
			if (MessageBox(hWnd, TEXT("게임을 종료하시겠습니까?"), TEXT("Game Exit"), MB_YESNO) == IDYES)
				PostQuitMessage(0);
			break;
		case ID_OPTION_SETTING:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, SettingDlg);
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		GameManager::GetInstance()->setLmousepoint(x, y);
		return 0;
	case WM_RBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		GameManager::GetInstance()->setRmousepoint(x, y);
		return 0;
	case WM_TIMER:
		GameManager::GetInstance()->TimeUpdate();
		InvalidateRect(hWnd, NULL, FALSE);
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GameManager::GetInstance()->Draw(hdc, g_hInst);
		GameManager::GetInstance()->Click();
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

INT_PTR CALLBACK SettingDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		CreateWindow(TEXT("button"), TEXT("Level"), WS_CHILD | WS_VISIBLE |
			BS_GROUPBOX, 5, 5, 120, 110, hDlg, (HMENU)0, g_hInst, NULL);
		r1 = CreateWindow(TEXT("button"), TEXT("Easy"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON | WS_GROUP, 10, 20, 100, 30, hDlg, (HMENU)ID_R1, g_hInst, NULL);
		r2 = CreateWindow(TEXT("button"), TEXT("Normal"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON, 10, 50, 100, 30, hDlg, (HMENU)ID_R2, g_hInst, NULL);
		r3 = CreateWindow(TEXT("button"), TEXT("Hard"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON, 10, 80, 100, 30, hDlg, (HMENU)ID_R3, g_hInst, NULL);
		CheckRadioButton(hDlg, ID_R1, ID_R3, num);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			//setting save
			if (IsDlgButtonChecked(hDlg, ID_R1) == BST_CHECKED)
			{
				num = ID_R1;
				MessageBox(hDlg, "Beginner", "초급자", MB_OK);
			}
			else if (IsDlgButtonChecked(hDlg, ID_R2) == BST_CHECKED)
			{
				num = ID_R2;
				MessageBox(hDlg, "Intermediate", "중급자", MB_OK);
			}
			else if (IsDlgButtonChecked(hDlg, ID_R3) == BST_CHECKED)
			{
				num = ID_R3;
				MessageBox(hDlg, "Advanced ", "고급자", MB_OK);
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case IDCANCEL:
			//setting cancel
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
