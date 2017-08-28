#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <ctime>
#include <string>

#define WIDTH 800
#define HEIGHT 500


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wnd;
	wnd.cbSize = sizeof(wnd);
	wnd.lpszClassName = _TEXT("Window");
	wnd.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wnd.lpfnWndProc = WndProc;
	wnd.cbWndExtra = 0;
	wnd.cbClsExtra = 0;
	wnd.hInstance = hInstance;

	wnd.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));
	wnd.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(101));
	wnd.hbrBackground = CreateSolidBrush(RGB(150, 200, 255));
	wnd.lpszMenuName = NULL;
	wnd.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(101));

	if (!RegisterClassEx(&wnd)){
		MessageBox(NULL, _TEXT("wnd Error"), _TEXT("Error"), MB_OK | MB_ICONERROR);
		return 0;
	}

	HWND hWnd = CreateWindowEx(
		NULL,
		_TEXT("Window"),
		_TEXT("Catch me if you can"),
		WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME),
		(GetSystemMetrics(SM_CXSCREEN) - WIDTH) / 2, (GetSystemMetrics(SM_CYSCREEN) - HEIGHT) / 2, WIDTH, HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd){
		MessageBox(NULL, _TEXT("hWnd Error"), _TEXT("Error"), MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hWnd, 1);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	srand((unsigned)time(0));

	static HWND hWndChildQuestion, hWndChild42;
	static WINDOWPLACEMENT wp, wh;
	RECT rectParent, rectStatic;
	static int xc, yc, xsl, yst, xsr, ysb;
	int xl, yt;

	switch (uMessage)
	{
	case WM_CREATE:
		hWndChildQuestion = CreateWindowEx(
			WS_EX_TOPMOST,
			L"STATIC",
			L"What is the meaning of life?",
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			300, 10, 190, 20,
			hWnd,
			(HMENU)NULL,
			GetModuleHandle(NULL),
			NULL);

		hWndChild42 = CreateWindowEx(
			WS_EX_TOPMOST,
			L"STATIC",
			L"42",
			WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
			360, 200, 50, 30,
			hWnd,
			(HMENU)NULL,
			GetModuleHandle(NULL),
			NULL);
		break;

	case WM_MOUSEMOVE:
		GetWindowPlacement(hWnd, &wp);
		GetWindowPlacement(hWndChild42, &wh);
		rectParent = wp.rcNormalPosition;
		rectStatic = wh.rcNormalPosition;

		xc = LOWORD(lParam);
		yc = HIWORD(lParam);

		xsl = rectStatic.left;
		yst = rectStatic.top;
		xsr = rectStatic.right;
		ysb = rectStatic.bottom;

		if (xc > xsl - 40 && xc < xsr + 40 && yc > yst - 40 && yc < ysb + 40){
			xl = xsl;
			yt = yst;
			while (xl > xsl - 100 && xl + 50 < xsr + 100 && yt > yst - 100 && yt+30 < ysb + 100){
				xl = rand() % (WIDTH - 100) + 10;
				yt = rand() % (HEIGHT - 100) + 10;
			}	
			MoveWindow(hWndChild42, xl, yt, 50, 30, TRUE);
		}
		break;

	case WM_LBUTTONDOWN:
		if (xc >= xsl && xc <= xsr && yc >= yst && yc <= ysb){
			if (MessageBox(hWnd, _TEXT("Perfect! You are the winner!"), _TEXT("CONGRATULATIONS"), MB_OK) == IDOK){
				DestroyWindow(hWnd);
			}
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, _TEXT("Do you want to exit?"), _TEXT("Exit"), MB_YESNO) == IDYES){
			DestroyWindow(hWnd);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
