#include "headers/total_failure_error.h"

#include <Windows.h>
#include <strsafe.h>

void TotalFailureError()
{
	DWORD errorCode;
	TCHAR *messageBuffer, *displayMessage;
	HANDLE processHeapHandle;
	
	errorCode = GetLastError();
	
	processHeapHandle = GetProcessHeap();
	
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR) &messageBuffer,
		0, NULL);
	
	displayMessage = HeapAlloc(
		processHeapHandle,
		HEAP_ZERO_MEMORY,
		sizeof (TCHAR) * (lstrlen(messageBuffer) + 1 + 80));
	
	StringCchPrintf(
		displayMessage,
		HeapSize(processHeapHandle, 0, displayMessage) / sizeof(TCHAR),
		TEXT("The application failed. %d: %s"),
		errorCode, messageBuffer);
	
	MessageBox(NULL, displayMessage, TEXT("Error"), MB_OK);
	
	LocalFree(LocalHandle((LPCVOID) messageBuffer));
	HeapFree(processHeapHandle, 0, displayMessage);
	
	ExitProcess(errorCode); // EXODUS POINT
}
