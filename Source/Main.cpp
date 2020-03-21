#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <new>

#include "MainWindow.h"

struct StateInfo {
	// struct members
	int StateInt;
};

inline StateInfo* GetAppState(HWND hwnd)
{
	LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
	StateInfo *pState = reinterpret_cast<StateInfo*>(ptr);
	return pState;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow win;

	if (!win.Create(L"Learn to Program Widows", WS_OVERLAPPEDWINDOW))
	{
		return 0;
	}

	ShowWindow(win.Window(), nCmdShow);

	// Run the message loop.

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

/*
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the data pointer

	StateInfo *pState = new (std::nothrow) StateInfo;

	if (pState == NULL)
	{
		return 0;
	}

	// Create the window

	HWND hwnd = CreateWindowEx(
		0,									// Optional window styles.
		CLASS_NAME,							// Window class
		L"Learn to Program Windows",		// Window text
		WS_OVERLAPPEDWINDOW,				// Window style

		// Size and Position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,				// Parent window
		NULL,				// Menu
		hInstance,			// Instance handle
		pState				// Addtional application data
		);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	// Run the message loop.

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
*/

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	StateInfo *pState;

	if (uMsg == WM_CREATE)
	{
		CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pState = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
	}
	else
	{
		pState = GetAppState(hwnd);
	}

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 2));
			EndPaint(hwnd, &ps);
		}
		return 0;

	case WM_CLOSE:
		if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		return 0; // User canceled. Do nothing.
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}