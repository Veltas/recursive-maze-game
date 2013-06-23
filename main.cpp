#include "main_header.hpp"

LRESULT CALLBACK MainWindowProcedure(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE instanceHandler, HINSTANCE, LPSTR commandLineParameters, int windowDisplayFlags)
{
	WNDCLASSEX mainWindowClass = {
		sizeof(WNDCLASSEX), 0, MainWindowProcedure, 0, 0, instanceHandler,
		LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW),
		(HBRUSH) COLOR_BACKGROUND + 1, NULL, MAIN_WINDOW_CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)};
	
	if (!RegisterClassEx(&mainWindowClass)) TotalFailureError();
	
	HWND mainWindowHandle = CreateWindow(
		MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TITLE, 
		WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT,
		NULL, NULL, instanceHandler, NULL);
	
	if (mainWindowHandle == NULL) TotalFailureError();
	
	ShowWindow(mainWindowHandle, windowDisplayFlags);
	if (!UpdateWindow(mainWindowHandle)) TotalFailureError();
	
	MSG mainMessage;
	
	while (BOOL recieveStatus = GetMessage(&mainMessage, mainWindowHandle, 0, 0)) {
		if (recieveStatus == -1) {
			TotalFailureError();
		} else {
			TranslateMessage(&mainMessage);
			DispatchMessage(&mainMessage);
		}
	}
	
	return mainMessage.wParam;
}

LRESULT CALLBACK MainWindowProcedure(HWND windowHandler, UINT messageCode, WPARAM wParam, LPARAM lParam)
{
	switch (messageCode) {
	case WM_CLOSE:
		DestroyWindow(windowHandler);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(windowHandler, messageCode, wParam, lParam);
		break;
	}
	return 0;
}
