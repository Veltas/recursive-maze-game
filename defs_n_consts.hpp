// Definitions, constants, and also a lot of globals that nobody else wanted.

#ifndef _DEFS_N_CONSTS_INCLUDED_
#define _DEFS_N_CONSTS_INCLUDED_

#include "predefs.hpp"

#include <Windows.h>
#include <Gdiplus.h>

#ifdef DEBUG
#include "debugger.hpp"
#endif

extern "C" LPCTSTR
	MAIN_WINDOW_CLASS_NAME,
	MAIN_WINDOW_TITLE;

#define MAZE_GRID_WIDTH 29
#define MAZE_GRID_HEIGHT 22
	
extern const unsigned
	MAIN_WINDOW_WIDTH,
	MAIN_WINDOW_HEIGHT,
	MAIN_CYCLE_TIMER_ID,
	MAIN_CYCLE_WAIT,
	MAZE_GRID_CELL_SIZE,
	CELL_WALL_UP,
	CELL_WALL_LEFT,
	MAZE_STRANGE_WALL_EXPECTED_PERIOD;

extern Gdiplus::Pen
	*MY_BLACK_PEN,
	*MY_WHITE_PEN,
	*MY_RED_PEN;

extern Gdiplus::SolidBrush
	*MY_BLACK_BRUSH,
	*MY_WHITE_BRUSH,
	*MY_RED_BRUSH,
	*MY_BLUE_BRUSH,
	*WEAK_BLACK_BRUSH;

extern const Gdiplus::SmoothingMode GRAPHICS_SMOOTHING_MODE;

#ifdef DEBUG
extern Debugger *globalDebugger; // DO NOT CHANGE
#endif

#endif
