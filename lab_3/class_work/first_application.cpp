#include <windows.h>
#include <tchar.h>
#include "resource.h"


#define WIDTH 200
#define HEIGHT 100
#define CLOSE_TIMER 1
#define COLOR_TIMER 2


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

	wnd.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(102));
	wnd.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(101));
	//wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.hbrBackground = CreateSolidBrush(RGB(150, 200, 255));
	wnd.lpszMenuName = NULL;
	wnd.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(101));

	if(!RegisterClassEx(&wnd)){
		MessageBox(NULL, _TEXT("Sorry...!!!!!!!!!!!!!!!!!! :("), _TEXT("Error"), MB_OK|MB_ICONERROR);
		return 0;
	}

	HWND hWnd = CreateWindowEx(
		NULL, 
		_TEXT("Window"), 
		_TEXT("Hello"), 
		WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_MINIMIZEBOX),
		CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
		NULL, 
		NULL, 
		hInstance, 
		NULL);

	if(!hWnd){
		MessageBox(NULL, _TEXT("Sorry... :("), _TEXT("Error"), MB_OK|MB_ICONERROR);
		return 0;
	}

	ShowWindow(hWnd, 1);
	UpdateWindow(hWnd);

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	int x, y;
	switch(uMessage)
	{
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		MoveWindow(hWnd, x, y, 300, 300, true);
		break;
	case WM_CREATE:
		SetTimer(hWnd, CLOSE_TIMER, 5000, NULL);
		SetTimer(hWnd, COLOR_TIMER, 1000, NULL);
		break;
	case WM_TIMER:
		if (wParam == COLOR_TIMER) {
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
			InvalidateRect(hWnd, NULL, true);
		}
		else if (wParam == CLOSE_TIMER) {
		//	KillTimer(hWnd, CLOSE_TIMER);
			if (MessageBox(hWnd, _TEXT("Âû äåéñòâèòåëüíî õîòèòå çàâåðøèòü ðàáîòó ïðèëîæåíèÿ?"), _TEXT("Èíôîðìàöèÿ"), MB_YESNO) == IDYES) {
				DestroyWindow(hWnd);
			}
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, CLOSE_TIMER);
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, _TEXT("Âû äåéñòâèòåëüíî õîòèòå çàâåðøèòü ðàáîòó ïðèëîæåíèÿ?"), _TEXT("Èíôîðìàöèÿ"), MB_YESNO) == IDYES){
			DestroyWindow(hWnd);
		}
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
