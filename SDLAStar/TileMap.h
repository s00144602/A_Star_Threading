#pragma once
#include "BasicTypes.h"
#include <iostream>
#include <map>
#include "Cell.h"
#include "SDL.h"
#include "BasicTypes.h"

using namespace std;

class TileMap
{
protected:
	//used for rendering the walls
	vector<Cell *> m_Wallcells;


	// the texture this TileMap is drawn on. the main renderer draws this texture.
	SDL_Texture *m_texture;
public:
	TileMap(unsigned int sizeX, unsigned int cellSize);
	std::map<Point, Cell *> m_cells;
	void createWalls();
	// the size of this TileMap.
	unsigned int m_size;
	// the size of the cells in the TileMap.
	unsigned int m_cellSize;
	void createWallArray(vector<int>& wallArray, int numberOfWalls);
	//Creates bordered tiles with special walls
	bool createLevel();
	//add neighbours to cell
	void createCellNeighbours();
	//loops through cells and calls render on each one
	void render(Renderer &renderer);
	int m_numOfCells;
};

