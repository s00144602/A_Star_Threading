#pragma once
#include "GameObject.h"
#include "BasicTypes.h"
#include "Cell.h"
#include <map>

using namespace std;

typedef std::pair<int, int> Point;
class NPC: public GameObject
{

public:
	NPC(Point startPos, std::map<Point, Cell*> &m_cells);
	~NPC();

	Point m_pos;
	std::map<Point, Cell *> m_map;
	Cell m_targetCell;
	Cell m_currentCell;
	void update(float deltaTime) override;
	void findPath();
	float getManahattanScore(Point gridPos);
	void render(Renderer& r) override;

};

