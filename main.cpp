// Recursive Maze Game, main source file.  -Veltas

/*	I'm not really sure how to explain this mess, but I've started commenting everything so maybe other people could understand it. */

#include "main_header.hpp"

// This global is used by main window procedure, controls game logic and stores state.
Game *mainGameObject = 0;

LRESULT CALLBACK MainWindowProcedure(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE instanceHandler, HINSTANCE, LPSTR commandLineParameters, int windowDisplayFlags)
{
	// Register window 'class' with OS in preperation for creating window.
	WNDCLASSEX mainWindowClass = {
		sizeof(WNDCLASSEX), 0, MainWindowProcedure, 0, 0, instanceHandler,
		LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW),
		NULL, // No brush, we'll fill our own background.
		NULL, MAIN_WINDOW_CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)};
	if (!RegisterClassEx(&mainWindowClass)) TotalFailureError();
	
	// Initialise game objects.
	mainGameObject = new Game;
	
	// Start window.
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
	
	// Main loop: recieves messages and transmits them so the OS can properly give them to MainWindowProcedure.
	while (BOOL recieveStatus = GetMessage(&mainMessage, mainWindowHandle, 0, 0)) {
		if (recieveStatus == -1) {
			TotalFailureError();
		} else {
			TranslateMessage(&mainMessage);
			DispatchMessage(&mainMessage);
		}
	}
	
	// Destruct game objects.
	delete mainGameObject;
	
	return mainMessage.wParam;
}


// Handles OS messages.
LRESULT CALLBACK MainWindowProcedure(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam)
{
	switch (messageCode) {
	// On window creation.
	case WM_CREATE:
		// Start game loop timer.
		SetTimer(windowHandle, MAIN_CYCLE_TIMER_ID, MAIN_CYCLE_WAIT, NULL);
		break;
	
	// Upon redraw request or something else changing we draw the window.
	case WM_PAINT:
		{
			PAINTSTRUCT paintJobStruct;
			// DrawGame requires a device context and game data to operate on.
			DrawGame(BeginPaint(windowHandle, &paintJobStruct), *mainGameObject);
			EndPaint(windowHandle, &paintJobStruct);
		}
		break;
	
	// When a user presses a key (can be triggered by auto-repeat).
	case WM_KEYDOWN:
		switch(wParam) {
		case VK_LEFT:
		case VK_RIGHT:
		case VK_UP:
		case VK_DOWN:
			mainGameObject->Input(wParam);
		}
		break;
		
	case WM_TIMER:
		if (wParam == MAIN_CYCLE_TIMER_ID) {
			// This is where the 'main game loop' kicks in.  This line should be reached at a frequency of about 60Hz.
			mainGameObject->Step(windowHandle);
			RedrawWindow(windowHandle, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		}
		break;
		
	case WM_CLOSE:
		// Clean up Windows API objects and etc.
		KillTimer(windowHandle, MAIN_CYCLE_TIMER_ID);
		DestroyWindow(windowHandle);
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		
	default:
		return DefWindowProc(windowHandle, messageCode, wParam, lParam);
		break;
	}
	return 0;
}

