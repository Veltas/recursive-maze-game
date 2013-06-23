#define UNICODE 1
#include <Windows.h>
#include <strsafe.h>

void TotalFailureError()
{
	DWORD errorCode;
	TCHAR *messageBuffer, *displayMessage;
	HANDLE processHeapHandle;
	
	errorCode = GetLastError();
	
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR) &messageBuffer,
		0, NULL);
	
	processHeapHandle = GetProcessHeap();
	
	displayMessage = HeapAlloc(processHeapHandle, HEAP_ZERO_MEMORY, lstrlen(messageBuffer) + 80);
	StringCchPrintf(
		displayMessage,
		HeapSize(processHeapHandle, 0, displayMessage) / sizeof(TCHAR),
		TEXT("The application failed.  Error code: %d, error message: %s"),
		errorCode, messageBuffer);
	MessageBox(NULL, displayMessage, TEXT("Error"), MB_OK);
	
	HeapFree(processHeapHandle, 0, displayMessage);
	//HeapFree(messageBuffer);
	
	ExitProcess(errorCode);
}
