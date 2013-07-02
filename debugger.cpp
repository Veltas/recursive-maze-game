#include "debugger.hpp"

#include <stack>

Debugger::Debugger()
{
	AllocConsole();
	m_ErrorOutputHandle = GetStdHandle(STD_ERROR_HANDLE);
}

void Debugger::PrintLine(LPCTSTR output)
{
	int length;
	DWORD feedback;
	for (length = 0; output[length]; ++length);
	WriteConsole(m_ErrorOutputHandle, (const void *) output, length, &feedback, NULL);
	WriteConsole(m_ErrorOutputHandle, (const void *) TEXT("\n"), 1, &feedback, NULL);
}

void Debugger::PrintLine(LPCTSTR name, int value)
{
	int length;
	DWORD feedback;
	for (length = 0; name[length]; ++length);
	WriteConsole(m_ErrorOutputHandle, (const void *) name, length, &feedback, NULL);
	WriteConsole(m_ErrorOutputHandle, (const void *) TEXT(": "), 2, &feedback, NULL);
	if (value == 0) {
		WriteConsole(m_ErrorOutputHandle, (const void *) TEXT("0\n"), 2, &feedback, NULL);
	} else {
		if (value < 0) {
			WriteConsole(m_ErrorOutputHandle, (const void *) TEXT("-"), 1, &feedback, NULL);
			value = -value;
		}
		std::stack<TCHAR> digits;
		int currentRemover;
		for (; value; value -= currentRemover, value /= 10) {
			currentRemover = value % 10;
			digits.push(TEXT('0') + static_cast<TCHAR>(currentRemover));
		}
		TCHAR currentCharacter;
		for (int i = digits.size(); i; --i) {
			currentCharacter = digits.top();
			digits.pop();
			WriteConsole(m_ErrorOutputHandle, (const void *) &currentCharacter, 1, &feedback, NULL);
		}
		WriteConsole(m_ErrorOutputHandle, (const void *) TEXT("\n"), 1, &feedback, NULL);
	}
}

Debugger::~Debugger()
{
	FreeConsole();
}
