#include "stdafx.h"
#include "NPC.h"

NPC::NPC(Point startPos, std::map<Point, Cell*> &m_cells):

m_pos(startPos),
m_map(m_cells)
{

}

NPC::~NPC()
{
}

void NPC::update(float deltaTime)
{
	findPath();
}

void NPC::findPath()
{
	bool pathFound = false;
	map<Point, Cell *> checkedCells =  map<Point, Cell *>();
	map<Cell, float> availableCells = map<Cell, float>();
	map<Point, Cell *> parentCells = map<Point, Cell *>();
	map<Point, int> distanceToRoot;// = map<Point, int>();
	vector<Cell> finalPath = vector<Cell>();
	Cell currentCheckingCell = m_currentCell;

	//availableCells = 
	distanceToRoot.insert(std::make_pair(currentCheckingCell.getGridPos(), 0));

	while (!pathFound)
	{

	}
}

float NPC::getManahattanScore(Point gridPos)
{
	return 0.0f;
}

void NPC::render(Renderer & r)
{
	//SDL_RenderFillCircle(renderer, x - mazeRect->x, y - mazeRect->y, size / 2);
}



