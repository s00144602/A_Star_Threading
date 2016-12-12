#pragma once
#include "GameObject.h"
#include "BasicTypes.h"
#include "TileMap.h"
#include <map>

using namespace std;

typedef std::pair<int, int> Point;
class NPC: public GameObject
{

public:
	NPC(Point startPos,int size, std::map<Point, Cell*> m_cells);
	~NPC();
	float m_size;
	Point m_pos;
	Point m_startPos;
	vector<Cell*> finalPath;
	std::map<Point, Cell*> m_map;
	Cell* m_targetCell;
	Cell* m_currentCell;
	void update(float deltaTime) override;
	void findPath();
	float getManahattanScore(Point gridPos);
	void render(Renderer& r) override;
private:
	bool m_pathFound;
};

