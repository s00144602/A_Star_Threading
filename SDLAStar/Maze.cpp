#include "stdafx.h"
#include "Maze.h"
#include <stack>
#include <vector>
#include "Renderer.h"
#include <omp.h>

Maze::Maze(unsigned int size, unsigned int cellSize) :
	m_size(size),
	m_searchId(1)
{
	Maze::m_cellSize = cellSize;
	m_numOfCells = m_size / m_cellSize;
	initialiseSpecialWalls();
}

//TODO:REfactor- must be a better way
void Maze::initialiseSpecialWalls()
{
	//3
	//(3*2) = 6
	//(3*2)+(6*2) = 18
	//2 detached
	detachedwalls.push_back(m_numOfCells / 2);
	detachedwalls.push_back(m_numOfCells / 3);
	//1 attached
	attachedwalls.push_back(m_numOfCells* 3 / 5);
	if (m_numOfCells <= 100)
	{
		//`+2 detached = 4
		detachedwalls.push_back(m_numOfCells / 10);
		detachedwalls.push_back(m_numOfCells * 3/ 4);
		//1 attached = 2
		attachedwalls.push_back(m_numOfCells *2 / 5);
	}
	if (m_numOfCells > 100)
	{
		//+10 = 14
		detachedwalls.push_back(m_numOfCells / 20);
		detachedwalls.push_back(m_numOfCells * 3/ 20);
		detachedwalls.push_back(m_numOfCells / 5);
		attachedwalls.push_back(m_numOfCells * 3 / 10);
		detachedwalls.push_back(m_numOfCells *7/ 20);
		detachedwalls.push_back(m_numOfCells *9/ 20);
		detachedwalls.push_back(m_numOfCells *11/20);
		detachedwalls.push_back(m_numOfCells * 3 / 5);
		detachedwalls.push_back(m_numOfCells * 13 / 20);
		detachedwalls.push_back(m_numOfCells * 7 / 10);
		attachedwalls.push_back(m_numOfCells * 8 / 10);
		detachedwalls.push_back(m_numOfCells * 17 / 20);
		detachedwalls.push_back(m_numOfCells * 9 / 10);
		detachedwalls.push_back(m_numOfCells * 19 / 20);
		//+2 = 4
	}
}

void Maze::createGrid()
{
	m_cells = {};
	std::vector<Cell *> currentRow = {};
	std::vector<Cell *> previousRow = {};
	// reverse x and y loop order so we can preserve previous row. (could have done previous column as well.)
#pragma omp parallel for
	for (unsigned int y = m_cellSize; y < m_size; y += m_cellSize) {
		Cell *previousCell = nullptr;
		for (unsigned int x = m_cellSize; x < m_size; x += m_cellSize) {
			Cell *currentCell = new Cell(x, y, m_cellSize);
			//TODO.. need to add back in the walls for the maze
			currentCell->addWall(Cell::TOP);
			currentCell->addWall(Cell::BOTTOM);
			currentCell->addWall(Cell::LEFT);
			currentCell->addWall(Cell::RIGHT);
			if (previousCell != nullptr) {
				// connect the two cells on the side.
				previousCell->addNeighbor(currentCell, Cell::RIGHT);
				currentCell->addNeighbor(previousCell, Cell::LEFT);
			}
			currentRow.push_back(currentCell);
			m_cells[Point(x / m_cellSize, y / m_cellSize)] = currentCell;
			previousCell = currentCell;

		}
		for (unsigned int i = 0; i < previousRow.size(); i++) {
			// connect the two cells top and bottom.
			previousRow.at(i)->addNeighbor(currentRow.at(i), Cell::BOTTOM);
			currentRow.at(i)->addNeighbor(previousRow.at(i), Cell::TOP);
		}
		// with the four connections above, this loop only needs to happen once to have all cells connected.
		// clear and reassign our previous row for the next loop.
		previousRow.clear();
		previousRow = currentRow;
		// clear our current row
		currentRow.clear();
	}
}

Cell *Maze::firstCell()
{
	return m_cells.at(Point(1, 1));
}

//Creates a simple level with desired number of attached and detached walls
bool Maze::createLevel()
{
	m_cells = {};
	vector<Point> cellPoints = {};
	// reverse x and y loop order so we can preserve previous row. (could have done previous column as well.)
	for (unsigned int y = 0; y < m_size; y += m_cellSize)
	{
		for (unsigned int x = 0; x < m_size; x += m_cellSize)
		{
			Point pt = Point(x / m_cellSize, y / m_cellSize);
			m_cells[pt] = new Cell(x, y, m_cellSize);

			//add border
			if (y == 0)
				m_cells[pt]->addWall(Cell::TOP);
			if (y == m_size - m_cellSize)
				m_cells[pt]->addWall(Cell::BOTTOM);
			if (x == 0)
				m_cells[pt]->addWall(Cell::LEFT);
			if (x == m_size - m_cellSize)
				m_cells[pt]->addWall(Cell::RIGHT);
		}
	}
	addSpecialWalls();
	std::cout << "finito" << std::endl;
	return true;
}

void Maze::addSpecialWalls()
{
	for (size_t i = 0; i < m_numOfCells; i++)
	{
		//Add the Attached Walls
		for (std::vector<int>::iterator it = attachedwalls.begin(); it != attachedwalls.end(); ++it)
		{
			if (i != m_numOfCells - 1 && i != m_numOfCells - 2)
				m_cells.at(Point(*it, i))->addWall(Cell::LEFT);
		}
		//Add the detached walls
		for (std::vector<int>::iterator it = detachedwalls.begin(); it != detachedwalls.end(); ++it)
		{
			if (i != m_numOfCells -1 && i != 0)
				m_cells.at(Point(*it, i))->addWall(Cell::LEFT);
		}
	}
}

bool Maze::createMaze()
{
	// start at the top cell
	Cell *currentCell = m_cells.at(Point(1, 1));
	// we are visiting the current cell. start at 1
	currentCell->setSearchVisitId(m_searchId);
	// stack used to backtrack once a dead end has been reached.
	std::stack<Cell *> stack;
	unsigned int visited = 1;
	while (visited != m_cells.size()) {
		//visit every cell once.
		// gather all the cells that we have not visited that are neighbors to this one
		auto neighbors = currentCell->getUnVisitedNeighbors(m_searchId);
		// when there are *no* unvisted cells left near this one, we've hit a dead end in the maze (likely an edge)
		if (!neighbors.size()) {
			if (stack.empty()) {
				// the grid is invalid.
				return false;
			}
			// retrace our steps (this can happen many times if every neighbor has been visited)
			currentCell = stack.top();
			stack.pop();
			continue;
		}
		// we have unvisted neighbors! retain the current cell so we can rewind later.
		stack.push(currentCell);
		// grab a random neighbor
		Cell *neighborCell = neighbors[rand() % neighbors.size()];
		visited++;
		// mark it as visited, remove the wall between the two cells, and make our neighbor the current cell.
		neighborCell->setSearchVisitId(m_searchId);
		neighborCell->removeWall(currentCell);
		currentCell->removeWall(neighborCell);
		currentCell = neighborCell;
	}

	return true;
}

std::deque<Cell*> Maze::aStarSearch(Cell * start, Cell * end)
{
	//TODO: implementation
	return std::deque<Cell*>();
}

void Maze::render(Renderer& renderer)
{
	for (auto &c : m_cells) {
		// if outside the viewable area then skip the tile ie Don't draw
		/*if ((c.second->rects[i].pos.x - Camera::Instance()->getPosition().x) < -m_cellSize
			|| (rects[i].pos.x - Camera::Instance()->getPosition().x) > Constants::WIN_WIDTH)
		{
			continue;
		}*/
		c.second->render(renderer);
	}
}