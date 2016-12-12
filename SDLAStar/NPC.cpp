#include "stdafx.h"
#include "NPC.h"
#include <algorithm>
#include <iterator>
#include <cmath> 
#include "MathsUtil.h"

NPC::NPC(Point startPos, int size, std::map<Point, Cell*> cells) :
	m_pathFound(false),
	m_startPos(startPos),
	m_pos(startPos),
	m_cells(cells),
	m_size(size)
{
	cout << "NPC created" << endl;
}

NPC::~NPC()
{
}

void NPC::update(float delatTime)
{
	findPath();
}

void NPC::resetMaps() 
{
	m_color = { MathsUtil::randomRange(0,255), MathsUtil::randomRange(0,255), MathsUtil::randomRange(0,255),25 };
	// Keep track of cells that have been scored and neighbours discovered
	 checkedCells = map<Point, Cell *>();
	// Keep track of cells that are scored and were discovered but neighbours not discovered
	 availableCells = map<Cell *, float>();
	// For every cell, keep track of what cell discovered it. This will be used for finding the final path
	 parentCells = map<Point, Point>();
	// For every cell discovered, keep track of how many steps it took to get there
	 distanceToRoot = map<Point, float>();
}

void NPC::findPath()
{
	if (!m_pathFound)
	{
		//init the maps 
		resetMaps();

		//set the currentcheckking tile to be the starting pos of the npc
		Cell* currentCheckingCell = m_cells.at(m_startPos);
		
		//m_targetCell = m_map.at(Point(28, 28));
		availableCells.insert(make_pair(currentCheckingCell, getManahattanScore(currentCheckingCell->getGridPos())));
		distanceToRoot.emplace(currentCheckingCell->getGridPos(), 0);

		while (!m_pathFound)
		{
			// Get manhattan distance to finish
			float currentDistance = availableCells[currentCheckingCell];


			// Mark current cell as checked, remove it from available so it won't be check again
			checkedCells.emplace(currentCheckingCell->getGridPos(), currentCheckingCell);
			availableCells.erase(currentCheckingCell);

			//// If the cell being checked is the target cell, stop
			if (currentCheckingCell->getGridPos() == m_targetCell->getGridPos())
			{
				m_pathFound = true;
				break;
			}

			//// This will be used later to see if a more suitable "next" cell is found
			Cell* nextCell = currentCheckingCell;

			//// For every neighbouring cell to the current checking one
			for (auto &t : currentCheckingCell->m_neighbors)
			{
				// Make sure its not a wall
				if (!t->m_iswall)
				{
					// Make sure it is not all ready available
					if (availableCells.count(t) == 0)
					{
						// Make sure it's not already been checked
						if (checkedCells.count(t->getGridPos()) == 0)
						{

							// Add it's parent cell (It will be the current checking cell)
							parentCells.emplace(t->getGridPos(), currentCheckingCell->getGridPos());

							// Get how many steps from the root cell it is. (.999 + the parents distance)
							// .999 instead of 1 so it will continue on the path it is currently checking
							distanceToRoot.emplace(t->getGridPos(), distanceToRoot[currentCheckingCell->getGridPos()] + .999f);

							// Get the manhattan distance of the current neighbour beinging checked
							float distance = getManahattanScore(t->getGridPos()) + distanceToRoot[parentCells[t->getGridPos()]];

							// Make this neighbour available for checking
							availableCells.insert(make_pair(t, distance));

							// If the neighbour is closer than the current checking one. Set is as the next cell
							if (distance <= currentDistance)
							{
								currentDistance = distance;
								nextCell = t;
							}
						}
					}
				}
			}
			// If no closer neighbour is found, the next cell will be picked from available cells where the manhattan distance is lowest
			if (nextCell->getGridPos() == currentCheckingCell->getGridPos())
			{
				vector<pair<Cell *, float> > v(availableCells.size());
				copy(availableCells.begin(), availableCells.end(), v.begin());
				sort(v.begin(), v.end(), [=](std::pair<Cell *, float>& a, std::pair<Cell *, float>& b)
				{
					return a.second < b.second;
				}
				);
				currentCheckingCell = v.begin()->first;
			}
			else
			{
				currentCheckingCell = nextCell;

			}
		}
		// #Path has been found
		
		m_pos = currentCheckingCell->getGridPos();
		finalPath.push_back(currentCheckingCell);

		bool Finished = false;
		// Trace back through the parent cells from 'Target' to 'Root'
		while (!Finished)
		{
			std::map<Point, Point>::iterator it;
			it = parentCells.find(currentCheckingCell->getGridPos());
			if (it != parentCells.end())
			{
				finalPath.push_back(checkedCells[it->second]);
				currentCheckingCell = checkedCells[it->second];
			}
			else
			{
				Finished = true;
			}

		}
	}
}

float NPC::getManahattanScore(Point gridPos)
{
	Point difference = Point(m_targetCell->getGridPos().first - gridPos.first, m_targetCell->getGridPos().second - gridPos.second);
	return abs(difference.first) + abs(difference.second);
}

void NPC::render(Renderer & r)
{
	//draw npc arriving
	r.drawRect(
		Rect(
		(m_pos.first*m_size) - Camera::Instance()->getPosition().x,
			(m_pos.second*m_size) - Camera::Instance()->getPosition().y,
			m_size,
			m_size),
			{ 0,0,0,100 }
	);
	//r.drawCircle(
	//(m_pos.first*m_size) + m_size / 2 - Camera::Instance()->getPosition().x,
	//(m_pos.second*m_size) + m_size / 2 - Camera::Instance()->getPosition().y,
	//m_size / 2,
	//{ 0,0,0 });
	//draw path
	for (auto t : finalPath)
	{
		r.drawRect(
			Rect(
				t->getPos().first + m_size/4 - Camera::Instance()->getPosition().x,
				t->getPos().second + m_size/4 - Camera::Instance()->getPosition().y,
				m_size/2, 
				m_size/2), 
				m_color
		);
	}
}

void NPC::setTargetGridPos(Point target)
{
	m_targetCell = m_cells.at(target);
}



