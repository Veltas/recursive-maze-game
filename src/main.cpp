// Recursive Maze Game, entry point source file.  -Veltas

#include "headers/predefs.hpp"

#include <vector>
#include <deque>
#include <list>
#include <queue>

#include <Windows.h>
#include <Gdiplus.h>

#include "headers/defs_n_consts.hpp"
#include "headers/total_failure_error.h"

#include "headers/game.hpp"
#include "headers/draw_game.hpp"

#ifdef DEBUG
#include "headers/debugger.hpp"
#endif

// This global is used by main window procedure, controls game logic and stores state.
Game *mainGameObject = 0;

LRESULT CALLBACK MainWindowProcedure(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE instanceHandler, HINSTANCE, LPSTR commandLineParameters, int windowDisplayFlags)
{
	// Initialise game objects.
	DEBUG_ONLY(globalDebugger = new Debugger); // DO NOT CHANGE
	mainGameObject = new Game;
	
	// Initialise GDI+
	DEBUG_OUT(TEXT("Gdiplus::GdiplusStartup() . . ."));
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	gdiplusStartupInput.GdiplusVersion = 1;
	gdiplusStartupInput.DebugEventCallback = NULL;
	gdiplusStartupInput.SuppressBackgroundThread = FALSE;
	gdiplusStartupInput.SuppressExternalCodecs = TRUE;
	if (Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL) != Gdiplus::Ok) TotalFailureError();
	
	// Initialise GDI+ objects
	MY_BLACK_PEN = new Gdiplus::Pen(Gdiplus::Color(0xFF, 0, 0, 0));
	MY_WHITE_PEN = new Gdiplus::Pen(Gdiplus::Color(0xFF, 0xFF, 0xFF, 0xFF));
	MY_RED_PEN = new Gdiplus::Pen(Gdiplus::Color(0xFF, 0xFF, 0, 0));

	MY_BLACK_BRUSH = new Gdiplus::SolidBrush(Gdiplus::Color(0xFF, 0, 0, 0));
	MY_WHITE_BRUSH = new Gdiplus::SolidBrush(Gdiplus::Color(0xFF, 0xFF, 0xFF, 0xFF));
	MY_RED_BRUSH = new Gdiplus::SolidBrush(Gdiplus::Color(0xFF, 0xFF, 0, 0));
	MY_BLUE_BRUSH = new Gdiplus::SolidBrush(Gdiplus::Color(0xFF, 0, 0, 0xFF));
	WEAK_BLACK_BRUSH = new Gdiplus::SolidBrush(Gdiplus::Color(0xAA, 0, 0, 0));
	
	// Register window 'class' with OS in preparation for creating window.
	DEBUG_OUT(TEXT("RegisterClassEx() . . ."));
	WNDCLASSEX mainWindowClass = {
		sizeof(WNDCLASSEX), 0, MainWindowProcedure, 0, 0, instanceHandler,
		LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW),
		NULL, // No brush, we'll fill our own background.
		NULL, MAIN_WINDOW_CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)};
	if (!RegisterClassEx(&mainWindowClass)) TotalFailureError();
	
	// Start window.
	DEBUG_OUT(TEXT("CreateWindow() . . ."));
	HWND mainWindowHandle = CreateWindow(
		MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TITLE, 
		WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT,
		NULL, NULL, instanceHandler, NULL);
	if (mainWindowHandle == NULL) TotalFailureError();
	
	// This starts the window being displayed, and invokes the first WM_PAINT message.
	DEBUG_OUT(TEXT("ShowWindow() . . ."));
	ShowWindow(mainWindowHandle, windowDisplayFlags);
	{
		BOOL result = UpdateWindow(mainWindowHandle);
		DEBUG_VAL(TEXT("UpdateWindow()"), result);
		if (!result) TotalFailureError();
	}
	
	MSG mainMessage;
	
	// Main loop: receives messages and transmits them so the OS can properly give them to MainWindowProcedure.
	DEBUG_OUT(TEXT("Main Windows message loop starting . . ."));
	while (BOOL recieveStatus = GetMessage(&mainMessage, mainWindowHandle, 0, 0)) {
		if (recieveStatus == -1) {
			TotalFailureError();
		} else {
			TranslateMessage(&mainMessage);
			DispatchMessage(&mainMessage);
		}
	}
	
	// Destruct GDI+ objects
	delete MY_BLACK_PEN;
	delete MY_WHITE_PEN;
	delete MY_RED_PEN;
	delete MY_BLACK_BRUSH;
	delete MY_WHITE_BRUSH;
	delete MY_RED_BRUSH;
	delete MY_BLUE_BRUSH;
	delete WEAK_BLACK_BRUSH;
	
	// Shut-down GDI+.
	Gdiplus::GdiplusShutdown(gdiplusToken);
	
	// Destruct game objects.
	delete mainGameObject;
	DEBUG_ONLY(delete globalDebugger); // DO NOT TOUCH
	
	return mainMessage.wParam;
}

// Handles OS messages, is driven by the 'main loop' above.
LRESULT CALLBACK MainWindowProcedure(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam)
{
	switch (messageCode) {
	// On window creation.
	case WM_CREATE:
		DEBUG_OUT(TEXT("WM_CREATE message"));
		// Start game loop timer.
		DEBUG_VAL(TEXT("SetTimer()"), SetTimer(windowHandle, MAIN_CYCLE_TIMER_ID, MAIN_CYCLE_WAIT, NULL));
		break;
	
	// Upon redraw request or something else changing we draw the window.
	case WM_PAINT:
		{
			PAINTSTRUCT paintJobStruct;
			HDC deviceContextHandle = BeginPaint(windowHandle, &paintJobStruct);
			HDC bufferDeviceContextHandle = CreateCompatibleDC(deviceContextHandle);
			HBITMAP bufferBitmapHandle = CreateCompatibleBitmap(deviceContextHandle, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
			HGDIOBJ oldBufferBitmapHandle = SelectObject(bufferDeviceContextHandle, bufferBitmapHandle);
			Gdiplus::Graphics graphics(bufferDeviceContextHandle);
			graphics.SetSmoothingMode(GRAPHICS_SMOOTHING_MODE);
			DrawGame(graphics, *mainGameObject);
			BitBlt(deviceContextHandle, 0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, bufferDeviceContextHandle, 0, 0, SRCCOPY);
			SelectObject(bufferDeviceContextHandle, oldBufferBitmapHandle);
			DeleteDC(bufferDeviceContextHandle);
			DeleteObject(bufferBitmapHandle);
			EndPaint(windowHandle, &paintJobStruct);
		}
		break;
	
	// When a user presses a key (can be triggered by auto-repeat).
	case WM_KEYDOWN:
		DEBUG_OUT(TEXT("WM_KEYDOWN message"));
		DEBUG_VAL(TEXT("wParam"), wParam);
		switch(wParam) {
		case VK_LEFT:
		case VK_UP:
		case VK_RIGHT:
		case VK_DOWN:
			DEBUG_OUT(TEXT("Arrow key pressed"));
			mainGameObject->Input(wParam);
		}
		break;
		
	case WM_TIMER:
		if (wParam == MAIN_CYCLE_TIMER_ID) {
			// This is where the 'main game loop' kicks in.  This line should be reached at a frequency of about 60Hz.
			mainGameObject->Step(windowHandle);
			RedrawWindow(windowHandle, NULL, NULL, RDW_INVALIDATE);
			//InvalidateRect(windowHandle, NULL, TRUE);
			//UpdateWindow(windowHandle);
		}
		break;
		
	case WM_CLOSE:
		DEBUG_OUT(TEXT("WM_CLOSE message"));
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
