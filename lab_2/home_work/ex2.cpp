#include <windows.h>
#include <ctime>
#include <tchar.h>
#include <string>

#define x 580
#define y 200
#define butStart 101
#define butEnd 102


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
	srand(unsigned(time(0)));
	wndclass.hbrBackground = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wndclass)) {
		return false;
	}

	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

	HWND hWnd = CreateWindowEx(
		WS_EX_TOPMOST,
		szClassName,
		szTitleName,
		WS_OVERLAPPEDWINDOW,
		(rect.right / 2) - 250, (rect.bottom / 2) - 250, 500, 500,
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

	HWND hWnd = makeWindow(L"MyWindowClass", L"Угадайка", hlnstance);
	

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	HWND hStart, hEnd;

	switch (iMsg){

	case WM_CREATE:
		ShowWindow(hWnd, 1);
		hStart = CreateWindowEx(
			NULL,
			L"BUTTON",
			L"Начать игру",
			WS_CHILD | WS_VISIBLE,
			x / 2 - 125, y / 2 + 70, 150, 50,
			hWnd,
			(HMENU)butStart,
			GetModuleHandle(NULL),
			NULL);

		hEnd = CreateWindowEx(
			NULL,
			L"BUTTON",
			L"Выход",
			WS_CHILD | WS_VISIBLE,
			x / 2 - 125, y / 2 + 120, 150, 50,
			hWnd,
			(HMENU)butEnd,
			GetModuleHandle(NULL),
			NULL);
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == butEnd){
			PostQuitMessage(0);
			break;
		}
		else if (LOWORD(wParam) == butStart){
			bool winner = 0;
			int min = 0;
			int max = 101;
			int rVar = min + max;
			bool lier = 0;
			while (!winner){
				int num = rand() % max + min;
				if (min == num){
					++num;
				}
				std::wstring tempt = L"Это число " + std::to_wstring(num) + L"?";
				if (MessageBox(hWnd, tempt.c_str(), _TEXT("Tempt"), MB_YESNO | MB_ICONQUESTION) == IDYES){
					std::wstring congratulations = _TEXT("Я чемпиён!!!");
					if (lier == true){
						std::wstring for_lier = _TEXT("\nИ больше не обманывай!!!");
						congratulations += for_lier;
					}
					MessageBox(hWnd, congratulations.c_str(), _TEXT("Winner"), MB_OK | MB_ICONWARNING);
					winner = 1;
				}
				else {
					if (MessageBox(hWnd, _TEXT("Больше?"), _TEXT("Question"), MB_YESNO | MB_ICONQUESTION) == IDYES){
						if (min + max - num == 1){
							MessageBox(hWnd, _TEXT("Больше некуда!!!\nТы сам говорил!!!"), _TEXT("WARNING"), MB_OK | MB_ICONWARNING);
							lier = true;
							continue;
						}
						min = num;
						max = rVar - min;
					}
					else{
						if (num - min == 1){
							MessageBox(hWnd, _TEXT("Меньше некуда!!!\nТы сам говорил!!!"), _TEXT("WARNING"), MB_OK | MB_ICONWARNING);
							lier = true;
							continue;
						}
						rVar = num;
						if (max > num){
							max = num;
							if (max < 1){
								max = 1;
							}
							continue;
						}
						max = rVar - min;
					}
				}
				if (max < 1){
					max = 1;
				}
			}
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
