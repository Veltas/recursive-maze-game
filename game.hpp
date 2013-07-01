#ifndef _GAME_HPP_INCLUDED_
#define _GAME_HPP_INCLUDED_

#include "predefs.hpp"

#include <vector>
#include <deque>
#include <stack>
#include <cmath>
#include <algorithm>

#include <Windows.h>
#include <Gdiplus.h>

#include "defs_n_consts.hpp"

template<typename T> struct TwoArray
{
	TwoArray(T i, T j) { array[0] = i; array[1] = j; }
	T array[2];
	bool operator==(TwoArray<T> other) { return ((array[0] == other.array[0]) && (array[1] == other.array[1])); }
};

struct MazeState
{
	int currentPosition[2];
	int end[2];
	std::deque<TwoArray<int>> jumps;
	char cellFlags[MAZE_GRID_HEIGHT][MAZE_GRID_WIDTH];
};

class Game
{
	std::stack<MazeState> m_MazePile;
	MazeState m_CurrentMaze;
	bool m_HaveCurrentInput;
	WPARAM m_LastKey;
	void InitialiseMazeState(MazeState &);
	void RecursiveMazeFiller(MazeState &, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY);
public:
	Game();
	void Step(HWND windowHandle);
	void Input(WPARAM key);
	const MazeState & CurrentState();
};

#endif

