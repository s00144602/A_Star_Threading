#include "stdafx.h"
#include "Maze.h"
#include <stack>
#include "Renderer.h"

Maze::Maze(unsigned int sizeX, unsigned int sizeY, unsigned int cellSize): 
	m_sizeX(sizeX),
	m_sizeY(sizeY), 
	m_cellSize(cellSize), 
	m_searchId(1)
{
}

void Maze::createGrid()
{
	m_cells = {};
	std::vector<Cell *> currentRow = {};
	std::vector<Cell *> previousRow = {};
	// reverse x and y loop order so we can preserve previous row. (could have done previous column as well.)
	for (unsigned int y = m_cellSize; y < m_sizeY - m_cellSize; y += m_cellSize) {
		Cell *previousCell = nullptr;
		for (unsigned int x = m_cellSize; x < m_sizeX - m_cellSize; x += m_cellSize) {
			Cell *currentCell = new Cell(x, y, m_cellSize);
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
		c.second->render(renderer);
	}
}



