#include <windows.h>
#include "cGame.h"

LRESULT CALLBACK WindowFunc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY: PostQuitMessage(0); break;
	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	} return 0;
}
bool InitWindow(HINSTANCE hInst, HWND *hWnd, bool *exclusive)
{
	WNDCLASSEX wcl;
	char szWinName[] = "Project Silcharde 2D";
	wcl.cbSize = sizeof(WNDCLASSEX);
	wcl.hInstance = hInst;
	wcl.lpszClassName = szWinName;
	wcl.lpfnWndProc = WindowFunc;
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = NULL;
	wcl.lpszMenuName = NULL;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	if (!RegisterClassEx(&wcl)) return false;
	int fullscreen;
	fullscreen = MessageBox(0, "Would you like fullscreen mode?", "2D Project", MB_YESNO);
	if (fullscreen == IDYES)
	{
		*hWnd = CreateWindow(szWinName, szWinName, WS_POPUP, 0, 0,
			SCREEN_RES_X, //GetSystemMetrics(SM_CXSCREEN),
			SCREEN_RES_Y, //GetSystemMetrics(SM_CYSCREEN),
			HWND_DESKTOP, NULL, hInst, NULL);
		*exclusive = true;
	}
	else
	{
		*hWnd = CreateWindow(szWinName, szWinName,
			WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
			0, 0, SCREEN_RES_X, SCREEN_RES_Y, NULL, NULL, hInst, NULL);
		*exclusive = false;
	}if(*hWnd == NULL) return false;
	
	// Amaguem el ratoli
	SetCursor(NULL);
	return true;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIntance, LPSTR lpszArgs, int nWinMode)
{
	bool exclusive, res;
	MSG msg;
	HWND hWnd;
	cGame *Game = cGame::Instance();
	res = InitWindow(hInstance, &hWnd, &exclusive);
	
	res = Game->Init(hWnd, hInstance, exclusive);
	if (res == true) {
		while (1)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				if (!Game->Loop()) break;
			}
		}
	}
	Game->Finalize();
	return 0;
}



