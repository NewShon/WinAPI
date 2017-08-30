#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <algorithm>
#include <string>


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

BOOL CALLBACK Dlgproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hFirst, hSecond, hAnswer, hP;
	static wchar_t f[256];
	static wchar_t s[256];

	static std::wstring first;
	static std::wstring second;

	switch (uMsg) 
	{

	case WM_INITDIALOG:
		hFirst = GetDlgItem(hWnd, ID_FIRST);
		hSecond = GetDlgItem(hWnd, ID_SECOND);

		hAnswer = GetDlgItem(hWnd, ID_ANSWER);
		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_CHECK:
			GetWindowText(hFirst, f, sizeof(f));	
			first = f;

			if (IsDlgButtonChecked(hWnd, ID_ANAGRAMMA)){
				GetWindowText(hSecond, s, sizeof(s));
				second = s;
				std::sort(first.begin(), first.end());
				std::sort(second.begin(), second.end());

				if (first == second){
					SetWindowText(hAnswer, L"Да");
				}
				else{
					SetWindowText(hAnswer, L"Нет");
				}
			}
			else if (IsDlgButtonChecked(hWnd, ID_PALINDROM)){
				std::wstring tmp = first;
				bool flag = true;
				for (size_t i = 0; i < first.length(); ++i){
					if (first[i] != tmp[first.length() - (i+1)]){
						flag = false;
						break;
					}
				}
				if (flag){
					SetWindowText(hAnswer, L"Да");
				}
				else{
					SetWindowText(hAnswer, L"Нет");
				}
			}
			break;

		case ID_CLEAN:
			SetWindowText(hFirst, L"");
			SetWindowText(hSecond, L"");
			SetWindowText(hAnswer, L"");
			break;

		case ID_PALINDROM:
			EnableWindow(hSecond, false);
			break;

		case ID_ANAGRAMMA:
			EnableWindow(hSecond, true);
			break;
		}
		return true;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return true;
	}

	return false;
}
