#pragma once
#include "GameObject.h"

#include <map>
#include "TileMap.h"

class Player: public GameObject
{
public:
	Player(Point startPos, int size);
	~Player();
	void update(float delatTime) override;
	void render(Renderer& r) override;
	void onEvent(EventListener::Event);
	Point m_pos;//taken as the grid pos
	int m_size;
	map<Point, Cell*> m_map = map<Point,Cell *>();
private:
	void checkNeighbourCells(float direction);
};

