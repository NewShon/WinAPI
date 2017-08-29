#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <CommCtrl.h>
#include <commdlg.h>
#pragma comment(lib,"comctl32")


BOOL CALLBACK Dlgproc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	LoadLibrary(L"Riched20.dll");
	HACCEL hAccel = LoadAccelerators(hinst, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	INITCOMMONCONTROLSEX iccs;
	iccs.dwSize = sizeof(iccs);
	iccs.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&iccs);

	HWND hWnd = CreateDialog(hinst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, Dlgproc);
	ShowWindow(hWnd, SW_NORMAL);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		if (!TranslateAccelerator(hWnd, hAccel, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

BOOL CALLBACK Dlgproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hRich, hStatusBar;
	static HMENU hMenu;
	RECT rect;
	static int parts[5] = { 150, 300, 450, 600, -1 };
	
	static OPENFILENAME openfile;
	static wchar_t filename[256];
	static wchar_t filetitle[256];

	switch (uMsg) {

	case WM_INITDIALOG:
		hRich = GetDlgItem(hWnd, ID_RICH);
		hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		SetMenu(hWnd, hMenu);

		EnableMenuItem(hMenu, SRIFT, MF_BYCOMMAND | MF_DISABLED);
		CheckMenuItem(hMenu, SOST, MF_BYCOMMAND | MF_CHECKED);
		

		hStatusBar = CreateWindowEx(
			NULL,
			STATUSCLASSNAME,
			NULL,
			WS_CHILD | WS_VISIBLE | SBARS_TOOLTIPS | SBARS_SIZEGRIP,
			CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT,
			hWnd,
			(HMENU)NULL,
			GetModuleHandle(NULL),
			NULL
		);
		SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)L"King's road");
		SendMessage(hStatusBar, SB_SETPARTS, 5, LPARAM(parts));

		memset(&openfile, 0, sizeof(OPENFILENAME));
		//ZeroMemory(&openfile, sizeof(OPENFILENAME));
		openfile.lStructSize = sizeof(OPENFILENAME);
		openfile.hInstance = GetModuleHandle(NULL);
		openfile.hwndOwner = hWnd;
		openfile.lpstrFilter = L"TEXT(*.*)\0*.\0\0";
		openfile.nMaxFile = 256;
		openfile.nMaxFileTitle = 30;
		openfile.lpstrFileTitle = filetitle;
		openfile.lpstrFile = filename;

		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case OPEN:
			GetOpenFileName(&openfile);
			break;

		case DELETE:
			SetWindowText(hRich, L"");
			break;

		case PASTE:
			SendMessage(hRich, WM_PASTE, 0, 0);
			break;

		case COPY:
			SendMessage(hRich, WM_COPY, 0, 0);
			break;

		case CUT:
			SendMessage(hRich, WM_CUT, 0, 0);
			break;

		case ABOUT:
			MessageBox(hRich, L"I'm the best proger", L"Info", MB_OK);
			break;

		case EXIT:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
		return true;

	case WM_SIZE:
		GetClientRect(hWnd, &rect);
		MoveWindow(hRich, 0, 0, rect.right, rect.bottom, true);
		MoveWindow(hStatusBar, 0, 0, rect.right, rect.bottom, true);
		
		return true;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return true;
	}

	return false;
}