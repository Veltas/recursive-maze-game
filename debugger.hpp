#ifndef _DEBUGGER_HPP_INCLUDED_
#define _DEBUGGER_HPP_INCLUDED_

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

#endif
