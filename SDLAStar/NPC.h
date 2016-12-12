#pragma once
#include "GameObject.h"
#include "BasicTypes.h"
#include "TileMap.h"
#include <map>
using namespace std;


class NPC: public GameObject
{

public:
	NPC(Point startPos, int size, std::map<Point, Cell*> m_cells);
	~NPC();
	float m_size;
	Point m_pos;
	Point m_startPos;
	vector<Cell*> finalPath;
	std::map<Point, Cell*> m_cells;
	Cell* m_targetCell;
	Cell* m_currentCell;
	void update(float deltaTime) override;
	void resetMaps();
	void findPath();
	float getManahattanScore(Point gridPos);
	void render(Renderer& r) override;
	//set the target pos of the NPC
	void setTargetGridPos(Point);
private:
	bool m_pathFound;
	// Keep track of cells that have been scored and neighbours discovered
	map<Point, Cell *> checkedCells; 
	// Keep track of cells that are scored and were discovered but neighbours not discovered
	map<Cell *, float> availableCells;
	Colour m_color;
	// For every cell, keep track of what cell discovered it. This will be used for finding the final path
	map<Point, Point> parentCells;
	// For every cell discovered, keep track of how many steps it took to get there
	map<Point, float> distanceToRoot;
};

