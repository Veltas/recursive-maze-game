#include "defs_n_consts.hpp"

extern "C" LPCTSTR
	MAIN_WINDOW_CLASS_NAME = TEXT("RecMazeGameMainWindow"),
	MAIN_WINDOW_TITLE = TEXT("AMazeING game (get it)");

extern const unsigned
	MAIN_WINDOW_WIDTH = 617,
	MAIN_WINDOW_HEIGHT = 479,
	MAIN_CYCLE_TIMER_ID = 1,
	MAIN_CYCLE_WAIT = 33, // Wait between each cycle in ms, 16.666ms = 1 / 60Hz.
	MAZE_GRID_CELL_SIZE = 40,
	CELL_WALL_UP = 1,
	CELL_WALL_LEFT = 2,
	MAZE_STRANGE_WALL_EXPECTED_PERIOD = 5000;

extern Gdiplus::Pen
	*MY_BLACK_PEN = NULL,
	*MY_WHITE_PEN = NULL,
	*MY_RED_PEN = NULL;

extern Gdiplus::SolidBrush
	*MY_BLACK_BRUSH = NULL,
	*MY_WHITE_BRUSH = NULL,
	*MY_RED_BRUSH = NULL,
	*MY_BLUE_BRUSH = NULL,
	*WEAK_BLACK_BRUSH = NULL;
	
extern const Gdiplus::SmoothingMode GRAPHICS_SMOOTHING_MODE = Gdiplus::SmoothingModeAntiAlias;

#ifdef DEBUG
extern Debugger *globalDebugger = NULL; // DO NOT CHANGE
#endif
