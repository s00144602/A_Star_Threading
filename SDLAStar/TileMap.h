#pragma once
#include "BasicTypes.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <deque>
#include "Cell.h"
#include "SDL.h"

using namespace std;

typedef std::pair<int, int> Point;

class TileMap
{
protected:

	std::map<Point, Cell *> m_cells;
	//vector<Cell *> m_cells;
	//used for rendering the walls
	vector<Cell *> m_Wallcells;
	// the size of this TileMap.
	unsigned int m_size;
	// the size of the cells in the TileMap.
	unsigned int m_cellSize;
	// the texture this TileMap is drawn on. the main renderer draws this texture.
	SDL_Texture *m_texture;
public:
	TileMap(unsigned int sizeX, unsigned int cellSize);
	void createWalls();

	void createWallArray(vector<int>& wallArray, int numberOfWalls);

	int rangeRandom(int min, int max);
	//Creates bordered tiles with special walls
	bool createLevel();
	std::deque<Cell*> aStarSearch(Cell * start, Cell * end);

	//loops through cells and calls render on each one
	void render(Renderer &renderer);
	//used to create walls in createLevel()
	std::vector<int> detachedwalls;
	std::vector<int> attachedwalls;
	int m_numOfCells;
};

