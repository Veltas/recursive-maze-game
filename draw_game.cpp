#include "draw_game.hpp"

void DrawGame(Gdiplus::Graphics &graphics, Game &currentGame)
{
	// Draw background.
	graphics.FillRectangle(MY_WHITE_BRUSH, 0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
	
	// Draw end.
	const MazeState &currentMazeState = currentGame.CurrentState();
	
	graphics.FillRectangle(
		WEAK_BLACK_BRUSH,
		static_cast<INT>(currentMazeState.end[0] * MAZE_GRID_CELL_SIZE + 2),
		static_cast<INT>(currentMazeState.end[1] * MAZE_GRID_CELL_SIZE + 2),
		static_cast<INT>(MAZE_GRID_CELL_SIZE - 5),
		static_cast<INT>(MAZE_GRID_CELL_SIZE - 5));
	
	// Draw player.
	graphics.FillEllipse(
		MY_RED_BRUSH,
		static_cast<INT>(currentMazeState.currentPosition[0] * MAZE_GRID_CELL_SIZE + 2),
		static_cast<INT>(currentMazeState.currentPosition[1] * MAZE_GRID_CELL_SIZE + 2),
		static_cast<INT>(MAZE_GRID_CELL_SIZE - 4),
		static_cast<INT>(MAZE_GRID_CELL_SIZE - 4));
	
	// Draw maze jumps.
	int numJumps = currentMazeState.jumps.size();
	for (int i = 0; i < numJumps; ++i) {
		graphics.FillEllipse(
			MY_BLUE_BRUSH,
			static_cast<INT>(currentMazeState.jumps[i].array[0] * MAZE_GRID_CELL_SIZE + 3),
			static_cast<INT>(currentMazeState.jumps[i].array[1] * MAZE_GRID_CELL_SIZE + 3),
			static_cast<INT>(MAZE_GRID_CELL_SIZE - 5),
			static_cast<INT>(MAZE_GRID_CELL_SIZE - 5));
	}
	
	// Draw maze.
	graphics.DrawRectangle(
		MY_BLACK_PEN,
		0, 0,
		MAZE_GRID_CELL_SIZE * MAZE_GRID_WIDTH, MAZE_GRID_CELL_SIZE * MAZE_GRID_HEIGHT);
	
	for (int j = 0; j < MAZE_GRID_HEIGHT; ++j) {
		for (int i = 0; i < MAZE_GRID_WIDTH; ++i) {
			if (currentMazeState.cellFlags[j][i] & CELL_WALL_UP) {
				graphics.DrawLine(
					MY_BLACK_PEN,
					static_cast<INT>(MAZE_GRID_CELL_SIZE * i), static_cast<INT>(MAZE_GRID_CELL_SIZE * j),
					static_cast<INT>(MAZE_GRID_CELL_SIZE * (i+1)), static_cast<INT>(MAZE_GRID_CELL_SIZE * j));
			}
			if (currentMazeState.cellFlags[j][i] & CELL_WALL_LEFT) {
				graphics.DrawLine(
					MY_BLACK_PEN,
					static_cast<INT>(MAZE_GRID_CELL_SIZE * i), static_cast<INT>(MAZE_GRID_CELL_SIZE * j),
					static_cast<INT>(MAZE_GRID_CELL_SIZE * i), static_cast<INT>(MAZE_GRID_CELL_SIZE * (j+1)));
			}
		}
	}
}
