#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <string>


#define ID_EDIT 100


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Dlgproc(HWND, UINT, WPARAM, LPARAM);

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

BOOL CALLBACK Dlgproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	static HWND hButOK, hEdit, edit2, edit3;
	wchar_t buf[20];
	switch (uMsg) {

	case WM_RBUTTONDOWN:
		SendMessage(edit3, WM_CUT, 0, 0);
		//SendMessage(edit2, WM_CLEAR , 0, 0);
		return true;
	case WM_RBUTTONDBLCLK:
		SendMessage(edit2, WM_PASTE, 0, 0);
		//SetWindowText(edit2, _TEXT(""));
		return true;

	case WM_INITDIALOG:
		edit2 = GetDlgItem(hwnd, IDC_EDIT2);
		edit3 = GetDlgItem(hwnd, IDC_EDIT3);

		hButOK = GetDlgItem(hwnd, IDOK);
		hEdit = CreateWindowEx(
			NULL,
			L"EDIT",
			L"Как бы все начать сначала, я всю жизнь переменю, я продам свою гитару и работу я найду, я убью своих соседей, что мешают спать, хжзкааввкп",
			WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL,
			10, 10, 100, 50,
			hwnd,
			(HMENU)ID_EDIT,
			GetModuleHandle(NULL),
			NULL);
		return true;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) {
			GetWindowText(hButOK, buf, 20);
			if (std::wstring(buf) == _TEXT("OK")) {
				SetWindowText(hButOK, _TEXT("NE OK"));
				SetWindowText(edit2, _TEXT("NE OK"));
				SetWindowText(edit3, _TEXT(""));
			}
			else {
				SetWindowText(hButOK, _TEXT("OK"));
				SetWindowText(edit3, _TEXT("OK"));
				SetWindowText(edit2, _TEXT(""));
			}
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		PostQuitMessage(0);
		return true;
	}
	
	return false;
}

