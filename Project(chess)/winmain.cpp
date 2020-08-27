#include "GameManager.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//글로벌 인스턴스핸들값
LPCTSTR lpszClass = TEXT("Chess"); //창이름
bool selectflag = false;
bool moveflag = false;

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
	int x = 0;
	int y = 0;
	
	switch (iMessage)
	{
	case WM_CREATE://윈도우 생성 시 할당, 초기화 등
		GameManager::GetInstance()->GameInit(hWnd);
		return 0;
	case WM_DESTROY:// 윈도우가 파괴되었다는 메세지
		delete GameManager::GetInstance();
		PostQuitMessage(0); //GetMessage함수에 WM_QUIT 메시지를 보낸다.
		return 0; //WndProc의 Switch는 break 대신 return 0; 를 쓴다.
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		if (selectflag)
		{
			if (GameManager::GetInstance()->MovePiece(hWnd, x, y))
			{
				selectflag = false;
			}
			else
			{
				selectflag = GameManager::GetInstance()->SelectPiece(hWnd, x, y);
			}
		}
		else
			selectflag = GameManager::GetInstance()->SelectPiece(hWnd, x, y);
		InvalidateRect(hWnd, NULL, TRUE);
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, 150, 100, 350, 600);
		Rectangle(hdc, 950, 100, 1150, 600);
		GameManager::GetInstance()->MapDraw(hdc);
		if (GameManager::GetInstance()->getturn() == BLACK)
			TextOut(hdc, 550, 50, TEXT("Turn : BLACK"), 12);
		else TextOut(hdc, 550, 50, TEXT("Turn : WHITE"), 12);
		GameManager::GetInstance()->ChessPieceDraw(hWnd);
		GameManager::GetInstance()->CalculateDraw(hWnd);
		GameManager::GetInstance()->PiecesCemeteryDraw(hdc);
		if (GameManager::GetInstance()->Check(hWnd))
		{
			InvalidateRect(hWnd, NULL, TRUE);
			Rectangle(hdc, 150, 100, 350, 600);
			Rectangle(hdc, 950, 100, 1150, 600);
			GameManager::GetInstance()->MapDraw(hdc);
			if (GameManager::GetInstance()->getturn() == BLACK)
				TextOut(hdc, 550, 50, TEXT("Turn : BLACK"), 12);
			else TextOut(hdc, 550, 50, TEXT("Turn : WHITE"), 12);
			GameManager::GetInstance()->ChessPieceDraw(hWnd);
			GameManager::GetInstance()->CalculateDraw(hWnd);
			GameManager::GetInstance()->PiecesCemeteryDraw(hdc);
		}
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case에 있는 메시지를 제외한 나머지 메시지를 처리한다.
}