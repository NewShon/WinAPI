#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <string>
#include <map>
#include <CommCtrl.h>
#pragma comment(lib,"comctl32")

#define ID_EDIT 100


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Dlgproc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{

	INITCOMMONCONTROLSEX iccs;
	iccs.dwSize = sizeof(iccs);
	iccs.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&iccs);

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
	static HWND hButOK, hCombo, hFIO, hMark, hInfo, hStatusBar;
	static HMENU hMenu;
	wchar_t buf[20];

	static int parts[4] = { 50,100,160,-1 };

	static std::map<int, std::pair<std::wstring, std::wstring>> mp;
	
	switch (uMsg) {

	case WM_INITDIALOG:
		SetWindowText(hwnd, _TEXT("Анкета студента"));

		hCombo = GetDlgItem(hwnd, IDC_COMBO2);
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("C"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("C++"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Python"));

		hFIO = GetDlgItem(hwnd, FIO);
		hMark = GetDlgItem(hwnd, MARK);
		hInfo = GetDlgItem(hwnd, INFO);
		hButOK = GetDlgItem(hwnd, IDOK);

		mp[0] = { L"Mark: 10", L"Q" };
		mp[1] = { L"Mark: 11", L"W" };
		mp[2] = { L"Mark: 12", L"E" };

		hStatusBar = CreateWindowEx(
			NULL,
			STATUSCLASSNAME,
			NULL,
			WS_CHILD | WS_VISIBLE | SBARS_TOOLTIPS | SBARS_SIZEGRIP,
			CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT,
			hwnd,
			(HMENU)NULL,
			GetModuleHandle(NULL),
			NULL
		);

		SendMessage(hStatusBar, SB_SIMPLE, false, 0);
		SendMessage(hStatusBar, SB_SETPARTS, 4, LPARAM(parts));
		SendMessage(hStatusBar, SB_SETTEXT, false, 0);

		hMenu = GetMenu(hwnd);
		EnableMenuItem(hMenu, ID_ACE, MF_BYCOMMAND | MF_DISABLED);

		return true;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) {

			SetWindowText(hFIO, _T("New Shon"));
			int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);

			SetWindowText(hMark, mp[index].first.c_str());
			SetWindowText(hInfo, mp[index].second.c_str());
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		PostQuitMessage(0);
		return true;
	}

	return false;
}
