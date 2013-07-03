#include "game.hpp"

void Game::InitialiseMazeState(MazeState &mazeState)
{
	// Start at top-left.
	mazeState.currentPosition[0] = mazeState.currentPosition[1] = 0;
	
	// End at bottom-right.
	mazeState.end[0] = MAZE_GRID_WIDTH - 1;
	mazeState.end[1] = MAZE_GRID_HEIGHT - 1;
	
	// Initialise top and left border walls.
	for (int j = 1; j < MAZE_GRID_HEIGHT; ++j) {
		for (int i = 1; i < MAZE_GRID_WIDTH; ++i) {
			mazeState.cellFlags[j][i] = 0;
		}
	}
	mazeState.cellFlags[0][0] = CELL_WALL_UP | CELL_WALL_LEFT;
	for (int i = 1; i < MAZE_GRID_WIDTH; ++i) {
		mazeState.cellFlags[0][i] = CELL_WALL_UP;
	}
	for (int i = 1; i < MAZE_GRID_HEIGHT; ++i) {
		mazeState.cellFlags[i][0] = CELL_WALL_LEFT;
	}
	
	// Generate maze within.
	DEBUG_OUT(TEXT("RecursiveMazeFiller() recursion started"));
	RecursiveMazeFiller(mazeState, 0, 0, MAZE_GRID_WIDTH - 1, MAZE_GRID_HEIGHT - 1);
}

//	Fills in the walls correctly and sticks in our jumps sometimes, uses 'recursive maze algorithm' from wikipedia because it looked like the easiest, don't judge me etc.
/*	mazeState: Current maze state to fill walls in on.
	topLeftX, topLeftY: Coordinates of top-left of box to initialise of the maze.
	bottomRightX, bottomRightY: Coordinates of bottom-right of box to initialise of the maze. */
void Game::RecursiveMazeFiller(MazeState &mazeState, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)
{
	int splitX = bottomRightX, splitY = bottomRightY;
	
	if ((topLeftX == bottomRightX) || (topLeftY == bottomRightY)) return;
	
	splitX = std::rand() % (bottomRightX - topLeftX) + topLeftX + 1;
	
	// Draw wall along this split.
	for (int i = topLeftY; i <= bottomRightY; ++i) {
		mazeState.cellFlags[i][splitX] |= CELL_WALL_LEFT;
	}
	
	splitY = std::rand() % (bottomRightY - topLeftY) + topLeftY + 1;
	
	for (int i = topLeftX; i <= bottomRightX; ++i) {
		mazeState.cellFlags[splitY][i] |= CELL_WALL_UP;
	}
	
	bool
		doubleSplitVertical = std::rand() % 2,
		firstYSplit, secondYSplit, firstXSplit, secondXSplit;
	
	if (doubleSplitVertical) {
		firstYSplit = secondYSplit = true;
	} else {
		firstYSplit = std::rand() % 2;
		secondYSplit = !firstYSplit;
	}
	
	if (!doubleSplitVertical) {
		firstXSplit = secondXSplit = true;
	} else {
		firstXSplit = std::rand() % 2;
		secondXSplit = !firstXSplit;
	}
	
	if (firstYSplit) {
		int manipulationPoint = std::rand() % (bottomRightY - splitY + 1) + splitY;
		mazeState.cellFlags[manipulationPoint][splitX] ^= CELL_WALL_LEFT;
	}
	if (secondYSplit) {
		int manipulationPoint = std::rand() % (splitY - topLeftY) + topLeftY;
		mazeState.cellFlags[manipulationPoint][splitX] ^= CELL_WALL_LEFT;
	}
	if (firstXSplit) {
		int manipulationPoint = std::rand() % (bottomRightX - splitX + 1) + splitX;
		mazeState.cellFlags[splitY][manipulationPoint] ^= CELL_WALL_UP;
	}
	if (secondXSplit) {
		int manipulationPoint = std::rand() % (splitX - topLeftX) + topLeftX;
		mazeState.cellFlags[splitY][manipulationPoint] ^= CELL_WALL_UP;
	}
	
	// Finish the job, call again for rectangles left after splitting to fill rest of maze.
	RecursiveMazeFiller(mazeState, topLeftX, topLeftY, splitX - 1, splitY - 1);
	RecursiveMazeFiller(mazeState, splitX, topLeftY, bottomRightX, splitY - 1);
	RecursiveMazeFiller(mazeState, topLeftX, splitY, splitX - 1, bottomRightY);
	RecursiveMazeFiller(mazeState, splitX, splitY, bottomRightX, bottomRightY);
}

Game::Game()
{
	std::srand(std::time(0));
	m_HaveCurrentInput = false;
	InitialiseMazeState(m_CurrentMaze);
}

// Process game logic.
/*	windowHandle: Window of the game, used to post a close message at end of game. */
void Game::Step(HWND windowHandle)
{
	if (m_HaveCurrentInput) {
		char cellFlags;
		bool moved = false;
		
		switch (m_LastKey) {
		case VK_LEFT:
			cellFlags = m_CurrentMaze.cellFlags[m_CurrentMaze.currentPosition[1]][m_CurrentMaze.currentPosition[0]];
			if (!(cellFlags & CELL_WALL_LEFT)) {
				--m_CurrentMaze.currentPosition[0];
				moved = true;
			}
			break;
		case VK_UP:
			cellFlags = m_CurrentMaze.cellFlags[m_CurrentMaze.currentPosition[1]][m_CurrentMaze.currentPosition[0]];
			if (!(cellFlags & CELL_WALL_UP)) {
				--m_CurrentMaze.currentPosition[1];
				moved = true;
			}
			break;
		case VK_RIGHT:
			if (m_CurrentMaze.currentPosition[0] != MAZE_GRID_WIDTH - 1) {
				cellFlags = m_CurrentMaze.cellFlags[m_CurrentMaze.currentPosition[1]][m_CurrentMaze.currentPosition[0] + 1];
				if (!(cellFlags & CELL_WALL_LEFT)) {
					++m_CurrentMaze.currentPosition[0];
					moved = true;
				}
			}
			break;
		case VK_DOWN:
			if (m_CurrentMaze.currentPosition[1] != MAZE_GRID_HEIGHT - 1) {
				cellFlags = m_CurrentMaze.cellFlags[m_CurrentMaze.currentPosition[1] + 1][m_CurrentMaze.currentPosition[0]];
				if (!(cellFlags & CELL_WALL_UP)) {
					++m_CurrentMaze.currentPosition[1];
					moved = true;
				}
			}
			break;
		}
		
		if (moved) {
			int num = m_CurrentMaze.jumps.size();
			for (int i = 0; i < num; ++i) {
				if ((m_CurrentMaze.currentPosition[0] == m_CurrentMaze.jumps[i].array[0]) && (m_CurrentMaze.currentPosition[1] == m_CurrentMaze.jumps[i].array[1])) {
					m_CurrentMaze.jumps.erase(m_CurrentMaze.jumps.begin() + i);
					m_MazePile.push(m_CurrentMaze);
					InitialiseMazeState(m_CurrentMaze);
					break;
				}
			}
			if ((m_CurrentMaze.currentPosition[0] == m_CurrentMaze.end[0]) && (m_CurrentMaze.currentPosition[1] == m_CurrentMaze.end[1])) {
				if (m_MazePile.empty()) {
					PostMessage(windowHandle, WM_CLOSE, 0, 0);
				} else {
					m_CurrentMaze = m_MazePile.top();
					m_MazePile.pop();
				}
			}
		}
		
		m_HaveCurrentInput = false;
	}
}

// Register input ready for logic to manage.
void Game::Input(WPARAM key)
{
	if (!m_HaveCurrentInput) {
		m_HaveCurrentInput = true;
		m_LastKey = key;
	}
}

const MazeState & Game::CurrentState() { return m_CurrentMaze; }
