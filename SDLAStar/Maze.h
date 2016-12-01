#pragma once
#include "BasicTypes.h"
#include <iostream>
#include <map>
#include <deque>
#include "Cell.h"
#include "SDL.h"

using namespace std;

typedef std::pair<int, int> Point;
class Maze
{
protected:
	std::map<Point, Cell *> m_cells;
	// the size of this maze.
	unsigned int m_size;
	// the size of the cells in the maze.
	unsigned int m_cellSize;
	// the current search id. incremented on each search
	unsigned int m_searchId;
	// the texture this maze is drawn on. the main renderer draws this texture.
	SDL_Texture *m_texture;
public:
	Maze(unsigned int sizeX, unsigned int cellSize);
	void initialiseSpecialWalls();

	//creates a grid of square cells. cells are connected on their four edges
	void createGrid();
	Cell *firstCell();

	//Creates bordered tiles with special walls
	bool createLevel();

	void addSpecialWalls();
	
	//creates the maze
	bool createMaze();

	std::deque<Cell*> aStarSearch(Cell * start, Cell * end);

	//loops through cells and calls render on each one
	void render(Renderer &renderer);
	//used to create walls in createLevel()
	std::vector<int> detachedwalls;
	std::vector<int> attachedwalls;
	int m_numOfCells;
};

