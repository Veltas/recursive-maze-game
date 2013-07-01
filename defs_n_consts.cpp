#include "defs_n_consts.hpp"

extern "C" LPCTSTR
	MAIN_WINDOW_CLASS_NAME = TEXT("RecMazeGameMainWindow"),
	MAIN_WINDOW_TITLE = TEXT("AMazeING game (get it)");

extern const unsigned
	MAIN_WINDOW_WIDTH = 640,
	MAIN_WINDOW_HEIGHT = 480,
	MAIN_CYCLE_TIMER_ID = 1,
	MAIN_CYCLE_WAIT = 17, // Wait between each cycle in ms, 16.666ms = 1 / 60Hz.
	MAZE_GRID_CELL_SIZE = 10,
	CELL_WALL_UP = 1,
	CELL_WALL_LEFT = 2,
	MAZE_STRANGE_WALL_EXPECTED_PERIOD = 50;

extern Gdiplus::Pen
	MY_BLACK_PEN(Gdiplus::Color(0xFF, 0, 0, 0)),
	MY_WHITE_PEN(Gdiplus::Color(0xFF, 0xFF, 0xFF, 0xFF)),
	MY_RED_PEN(Gdiplus::Color(0xFF, 0xFF, 0, 0));

extern Gdiplus::SolidBrush
	MY_BLACK_BRUSH(Gdiplus::Color(0xFF, 0, 0, 0)),
	MY_WHITE_BRUSH(Gdiplus::Color(0xFF, 0xFF, 0xFF, 0xFF)),
	MY_RED_BRUSH(Gdiplus::Color(0xFF, 0xFF, 0, 0)),
	MY_BLUE_BRUSH(Gdiplus::Color(0xFF, 0, 0, 0xFF)),
	WEAK_BLACK_BRUSH(Gdiplus::Color(0xAA, 0, 0, 0));
