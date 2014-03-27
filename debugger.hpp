#pragma once

#include "predefs.hpp"
#include <Windows.h>

class Debugger
{
	HANDLE m_ErrorOutputHandle;
public:
	Debugger();
	void PrintLine(LPCTSTR output);
	void PrintLine(LPCTSTR name, int value); // Prints  name: value
	~Debugger();
};
