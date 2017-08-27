#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <ctime>
#include <string>

#define WIDTH 300
#define HEIGHT 150
#define CLOSE_TIMER 1
#define MOVE_TIMER 2
#define TIME_TIMER 3

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
	wnd.hbrBackground = CreateSolidBrush(RGB(150, 200, 255));
	wnd.lpszMenuName = NULL;
	wnd.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));

	if (!RegisterClassEx(&wnd)){
		MessageBox(NULL, _TEXT("wnd Error"), _TEXT("Error"), MB_OK | MB_ICONERROR);
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
	static HCURSOR hArrow, hSword;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect, rApp;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	GetWindowRect(hWnd, &rApp);
	int x, y;
	SYSTEMTIME st;
	GetLocalTime(&st);
	std::wstring tm = L"";
	std::wstring hours = std::to_wstring(st.wHour);
	std::wstring minutes = std::to_wstring(st.wMinute);
	std::wstring seconds = std::to_wstring(st.wSecond);

	switch (uMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, CLOSE_TIMER, 10000, NULL);	
		SetTimer(hWnd, TIME_TIMER, 500, NULL);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		SetTextColor(hdc, RGB(50, 50, 150));
		SetBkMode(hdc, TRANSPARENT);

		hours = std::to_wstring(st.wHour);
		minutes = std::to_wstring(st.wMinute);
		seconds = std::to_wstring(st.wSecond);
		tm += hours + L" : " + minutes + L" : " + seconds;

		DrawText(hdc, tm.c_str(), -1, &rect, DT_CENTER );
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		SetClassLong(hWnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_ARROW));
		break;

	case WM_LBUTTONDBLCLK:
		SetClassLong(hWnd, GCL_HCURSOR, (LONG)LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR1)));
		break;

	case WM_RBUTTONDOWN:
		srand(unsigned(time(0)));
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		InvalidateRect(hWnd, NULL, true);
		break;

	case WM_RBUTTONDBLCLK:
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)(HBRUSH)GetStockObject(WHITE_BRUSH));
		InvalidateRect(hWnd, NULL, true);
		break;

	case WM_SYSKEYDOWN:
		if (wParam == VK_LEFT) {
			ShowWindow(hWnd, SW_SHOWNORMAL);
		}
		else if (wParam == VK_RIGHT) {
			ShowWindow(hWnd, SW_SHOWNORMAL);
		}
		else if (wParam == VK_DOWN) {
			ShowWindow(hWnd, SW_SHOWMINIMIZED);
		}
		else if (wParam == VK_UP) {
			ShowWindow(hWnd, SW_SHOWMAXIMIZED);
		}
		else if (wParam == VK_F4) {
			PostMessage(
				hWnd,
				WM_CLOSE,
				0, 0
				);
		}
		break;

	case WM_KEYDOWN:
		if(wParam == VK_RETURN){
			MoveWindow(hWnd, rect.right - WIDTH, rect.top, WIDTH, HEIGHT, true);
			SetTimer(hWnd, MOVE_TIMER, 1, NULL);
		}
		if (wParam == VK_ESCAPE){
			KillTimer(hWnd, MOVE_TIMER);
		}

	case WM_TIMER:
		if (wParam == TIME_TIMER){
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
		}
		if (wParam == MOVE_TIMER){
			if (rApp.right == rect.right && rApp.bottom != rect.bottom){
				x = rApp.right - WIDTH;
				y = rApp.top;
				MoveWindow(hWnd, x, ++y, WIDTH, HEIGHT, true);
			}
			else if (rApp.bottom == rect.bottom && rApp.left != rect.left){
				x = rApp.right - WIDTH;
				y = rApp.top;
				MoveWindow(hWnd, --x, y, WIDTH, HEIGHT, true);
			}
			else if (rApp.left == rect.left && rApp.top != rect.top){
				x = rApp.right - WIDTH;
				y = rApp.top;
				MoveWindow(hWnd, x, --y, WIDTH, HEIGHT, true);
			}
			else if (rApp.top == rect.top && rApp.right != rect.right){
				x = rApp.right - WIDTH;
				y = rApp.top;
				MoveWindow(hWnd, ++x, y, WIDTH, HEIGHT, true);
			}
		}
		else if (wParam == CLOSE_TIMER) {
			KillTimer(hWnd, CLOSE_TIMER);
			if (MessageBox(hWnd, _TEXT("Do you want exit?"), _TEXT("Exit"), MB_YESNO) == IDYES) {
				DestroyWindow(hWnd);
			}
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, _TEXT("Do you want exit?"), _TEXT("Exit"), MB_YESNO) == IDYES){
			DestroyWindow(hWnd);
		}
		break;

	case WM_DESTROY:
		KillTimer(hWnd, CLOSE_TIMER);
		PostQuitMessage(0);
		break;
	
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
