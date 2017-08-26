#include <windows.h>

#define win2 200
#define win3 400
#define win4 600


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND makeWindow(LPWSTR szClassName, LPWSTR szTitleName, HINSTANCE hlnstance){
	WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.lpszClassName = szClassName;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hlnstance;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hbrBackground = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wndclass)) {
		return false;
	}

	HWND hWnd = CreateWindowEx(
		WS_EX_TOPMOST,
		szClassName,
		L"Window",
		WS_OVERLAPPEDWINDOW,
		200, 200, 300, 300,
		NULL,
		NULL,
		hlnstance,
		NULL);

	if (!hWnd) {
		return false;
	}

	return hWnd;
}

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	HWND window1 = makeWindow(L"MyWindowClass", L"MyWindow", hlnstance);
	ShowWindow(window1, 1);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	switch (iMsg) {
	case WM_CREATE:
		SetTimer(hWnd, win2, 1000, NULL);
		SetTimer(hWnd, win3, 3000, NULL);
		SetTimer(hWnd, win4, 5000, NULL);
		break;

	case WM_TIMER:
		if (wParam == win2){
			KillTimer(hWnd, win2);
			HWND window2 = makeWindow(L"MyWindowClass2", L"MyWindow2", GetModuleHandle(NULL));
			ShowWindow(window2, 1);
		}
		else if (wParam == win3){
			KillTimer(hWnd, win3);
			HWND window3 = makeWindow(L"MyWindowClass3", L"MyWindow3", GetModuleHandle(NULL));
			ShowWindow(window3, 1);
		}
		else if (wParam == win4){
			KillTimer(hWnd, win4);
			HWND window4 = makeWindow(L"MyWindowClass4", L"MyWindow4", GetModuleHandle(NULL));
			ShowWindow(window4, 1);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}

	return 0;
}
