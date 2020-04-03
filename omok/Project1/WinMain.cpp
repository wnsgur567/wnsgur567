#include "Board.h"
#include "Render.h"

//GDI+
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
//

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Omok");
HWND hWnd;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	//GDI+ start
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

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
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, MAP_W + 16, MAP_H + 18,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	//gdi end
	Gdiplus::GdiplusShutdown(gdiplusToken);

	return (int)Message.wParam;
}


#include"Player.h"

Board* board = new Board;
int mouseX, mouseY;
//static Player* player1 = new Player;
//static Player* player2 = new Player;

//바둑돌 위치 최소 최대 좌표값
#define MAX_POS 1000
#define MIN_POS 100

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;


	switch (iMessage) {

	case WM_CREATE:
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		//---------바둑돌 위치 조정----------//
		{
			if (mouseX % 50 > 25) mouseX = mouseX / 50 * 50 + 50;
			else  mouseX = mouseX / 50 * 50;
			if (mouseY % 50 > 25) mouseY = mouseY / 50 * 50 + 50;
			else  mouseY = mouseY / 50 * 50;

			if (mouseX < MIN_POS) mouseX = MIN_POS;
			else if (mouseX > MAX_POS) mouseX = MAX_POS;
			if (mouseY < MIN_POS) mouseY = MIN_POS;
			else if (mouseY > MAX_POS) mouseY = MAX_POS;
		}
		//----------------------------------//
		return 0;

	case WM_MOUSEMOVE:

		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		//---------바둑돌 위치 조정----------//
		{
			if (mouseX % 50 > 25) mouseX = mouseX / 50 * 50 + 50;
			else  mouseX = mouseX / 50 * 50;
			if (mouseY % 50 > 25) mouseY = mouseY / 50 * 50 + 50;
			else  mouseY = mouseY / 50 * 50;

			if (mouseX < MIN_POS) mouseX = MIN_POS;
			else if (mouseX > MAX_POS) mouseX = MAX_POS;
			if (mouseY < MIN_POS) mouseY = MIN_POS;
			else if (mouseY > MAX_POS) mouseY = MAX_POS;
		}
		//----------------------------------//
		InvalidateRect(hWnd, NULL, false);
		return 0;

	case WM_LBUTTONDOWN:

		if (board->putOn(mouseX, mouseY) == BLACK)
			MessageBox(hWnd, L"black", L"cow", MB_OK);
		if (board->putOn(mouseX, mouseY) == WHITE)
			MessageBox(hWnd, L"white", L"noise", MB_OK);

		InvalidateRect(hWnd, NULL, false);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		Render();

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		delete board;
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
