#include "stdafx.h"
#include "TileMap.h"
#include <stack>
#include <vector>
#include "Renderer.h"
#include <omp.h>
#include <time.h> 


TileMap::TileMap(unsigned int size, unsigned int cellSize) :
	m_size(size),
	m_cellSize(cellSize)
{
	m_numOfCells = m_size / m_cellSize;
	createLevel();
}


//TODO:REfactor- must be a better way 
//walls created with random"ish" length and random"ish" x pos 
void TileMap::createWalls()
{
	/* initialize random seed: */
	srand(time(NULL));
	vector<int>& wallArray = vector<int>();
	//3 walls (1attached)
	if (m_numOfCells <= 32)
	{
		createWallArray(wallArray,3);
	}
	//6 walls (2attached) add 3 more walls
	if (m_numOfCells <= 100 && m_numOfCells > 32)
	{
		createWallArray(wallArray, 6);
	}
	//18walls (4 attached) add 12 more walls
	if (m_numOfCells > 100)
	{
		createWallArray(wallArray, 18);
	}

	int start;//determines what random amount of space to take from the start/y of the walls 
	int end;
	for (size_t i = 0; i < wallArray.size(); i++)
	{
		start = rangeRandom(2, 3);
		end = rangeRandom(m_numOfCells - 4, m_numOfCells-2);
		for (size_t j = 0; j < m_numOfCells; j++)
		{
			//Attached at the top walls
			if (i == 2 || i == 10)
			{
				if (j > start)
				{
					m_Wallcells.push_back(new Cell(wallArray[i] * m_cellSize, j*m_cellSize, m_cellSize, true));
					m_cells.at(Point(wallArray[i], j))->m_iswall = true;
				}
			}
			//Attached at bottom
			else if (i == 4 || i ==15)
			{
				if (j < end)
				{
					m_Wallcells.push_back(new Cell(wallArray[i] * m_cellSize, j*m_cellSize, m_cellSize, true));
					m_cells.at(Point(wallArray[i], j))->m_iswall = true;
				}
			}
			//Detached walls
			else
			{
				if (j > start && j < end)
				{
					m_Wallcells.push_back(new Cell(wallArray[i] * m_cellSize, j*m_cellSize, m_cellSize, true));
					m_cells.at(Point(wallArray[i], j))->m_iswall = true;
				}
			}
		}
	}
}

void TileMap::createWallArray(vector<int>& wallArray, int numberOfWalls)
{
	int x = 2;
	int y = m_numOfCells / (numberOfWalls+1);
	for (size_t i = 0; i < numberOfWalls; i++)
	{
		wallArray.push_back(rangeRandom(x, y));
		x += m_numOfCells / (numberOfWalls);
		y += m_numOfCells / (numberOfWalls);
	}
}

int TileMap::rangeRandom(int min, int max) 
{
	int n = max - min + 1;
	int remainder = RAND_MAX % n;
	int x;
	do {
		x = rand();
	} while (x >= RAND_MAX - remainder);
	return min + x % n;
}

//Creates a simple level with desired number of attached and detached walls
bool TileMap::createLevel()
{
	m_cells = {};
	// reverse x and y loop order so we can preserve previous row. (could have done previous column as well.)
	#pragma omp parallel for
	for (unsigned int y = 0; y < m_size; y += m_cellSize)
	{
		for (unsigned int x = 0; x < m_size; x += m_cellSize)
		{
			//add border walls
			if (y == 0 || y == m_size - m_cellSize || x == 0 || x == m_size - m_cellSize)
			{
				m_cells.emplace(Point(x / m_cellSize, y / m_cellSize), new Cell(x, y, m_cellSize, true));
				//m_cells.push_back(new Cell(x, y, true));
				m_Wallcells.push_back(new Cell(x, y,m_cellSize, true));
			}
			//add empty cells
			else
			{
				//m_cells.push_back(new Cell(x, y, false));
				m_cells.emplace(Point(x / m_cellSize, y / m_cellSize), new Cell(x, y, m_cellSize, false));
			}
		}
	}
	createWalls();
	createCellNeighbours();
	//addSpecialWalls();
	std::cout << "finito" << std::endl;
	return true;
}

void TileMap::createCellNeighbours()
{

	for (auto &c : m_cells)
	{
		if (c.second->getGridPos().second > 0)
			c.second->addNeighbor(m_cells[Point(c.second->getGridPos().first, c.second->getGridPos().second - 1)]);
		if (c.second->getGridPos().second < m_numOfCells - 1)
			c.second->addNeighbor(m_cells[Point(c.second->getGridPos().first, c.second->getGridPos().second + 1)]);
		if (c.second->getGridPos().first  > 0)
			c.second->addNeighbor(m_cells[Point(c.second->getGridPos().first - 1, c.second->getGridPos().second)]);
		if (c.second->getGridPos().first < m_numOfCells - 1)
			c.second->addNeighbor(m_cells[Point(c.second->getGridPos().first + 1, c.second->getGridPos().second)]);
	}

}

std::deque<Cell*> TileMap::aStarSearch(Cell * start, Cell * end)
{
	//TODO: implementation
	return std::deque<Cell*>();
}

//TODO: take the camera pos and width into account to determine which cells to render
//Make camera zoom in for scaling.. help with not having to render all the cells
//perhaps have two arrays .. one for walls and one for no walls . only draw the walls
//also use the camera culling
void TileMap::render(Renderer& renderer)
{
	//int camPos = Camera::Instance()->getPosition().x;

	for (auto &c : m_Wallcells) {
		if (c->m_iswall)
			c->render(renderer,m_cellSize);
	}
}