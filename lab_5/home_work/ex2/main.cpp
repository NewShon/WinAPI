#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <vector>
#include <ctime>


#define CAT_TIMER 1
#define DOG_TIMER 2
#define ALL_TIMER 3
#define FAST_SPEED 10
#define SLOW_SPEED 2000


BOOL CALLBACK Dlgproc(HWND, UINT, WPARAM, LPARAM);

void init(std::vector<HBITMAP> &pict) {
	pict.push_back(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1)));
	pict.push_back(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2)));
	pict.push_back(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3)));
	pict.push_back(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP4)));
	pict.push_back(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP5)));
	pict.push_back(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP6)));
	pict.push_back(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP7)));
	pict.push_back(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP8)));
	pict.push_back(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP9)));
	pict.push_back(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP10)));
}

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd = CreateDialog(hinst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, Dlgproc);
	ShowWindow(hWnd, SW_NORMAL);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

BOOL CALLBACK Dlgproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	srand(unsigned(time(0)));

	static HWND hCat, hDog, hFast, hSlow, hStart, hStop, hBG;
	static std::vector<HBITMAP>picture;
	int speed = 1000;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		hCat = GetDlgItem(hWnd, ID_CAT);
		hDog = GetDlgItem(hWnd, ID_DOG);

		hFast = GetDlgItem(hWnd, ID_FAST);
		hSlow = GetDlgItem(hWnd, ID_SLOW);

		hStart = GetDlgItem(hWnd, ID_START);
		hStop = GetDlgItem(hWnd, ID_STOP);

		hBG = GetDlgItem(hWnd, ID_BG);

		init(picture);

		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_START:
			if (IsDlgButtonChecked(hWnd, ID_FAST)) {
				speed = FAST_SPEED;
			}
			else {
				speed = SLOW_SPEED;
			}
			if (SendMessage(hCat, BM_GETCHECK, 0, 0) && SendMessage(hDog, BM_GETCHECK, 0, 0)) {
				SendMessage(hBG, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)picture[rand() % 10]);
				SetTimer(hWnd, ALL_TIMER, speed, NULL);
			}
			else if (SendMessage(hCat, BM_GETCHECK, 0, 0) && !SendMessage(hDog, BM_GETCHECK, 0, 0)) {
				SendMessage(hBG, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)picture[rand() % 5]);
				SetTimer(hWnd, CAT_TIMER, speed, NULL);
			}
			else if (!SendMessage(hCat, BM_GETCHECK, 0, 0) && SendMessage(hDog, BM_GETCHECK, 0, 0)) {
				SendMessage(hBG, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)picture[rand() % 5 + 5]);
				SetTimer(hWnd, DOG_TIMER, speed, NULL);
			}
			else {
				MessageBox(hWnd, L"Выбери что нибудь", L"Error", MB_OK);
			}
			break;

		case ID_STOP:
			if (SendMessage(hCat, BM_GETCHECK, 0, 0) && SendMessage(hDog, BM_GETCHECK, 0, 0)) {
				KillTimer(hWnd, ALL_TIMER);
			}
			else if (SendMessage(hCat, BM_GETCHECK, 0, 0)) {
				KillTimer(hWnd, CAT_TIMER);
			}
			else if (SendMessage(hDog, BM_GETCHECK, 0, 0)) {
				KillTimer(hWnd, DOG_TIMER);
			}
			break;
		}
		return true;

	case WM_TIMER:
		if (wParam == ALL_TIMER) {
			SendMessage(hBG, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)picture[rand() % 10]);
		}
		else if (wParam == CAT_TIMER) {
			SendMessage(hBG, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)picture[rand() % 5]);
		}
		else if (wParam == DOG_TIMER) {
			SendMessage(hBG, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)picture[rand() % 5 + 5]);
		}
		return true;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return true;
	}

	return false;
}
