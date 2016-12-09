#ifndef _TileMap_CELL_H
#define _TileMap_CELL_H
#include <vector>
#include "Renderer.h"
#include "Camera.h"

typedef std::pair<int, int> Point;
class Cell
{
	float x;
	float y;
	float m_size;
	float wallSize;

protected:
	std::vector<Cell*> neighbors;
	std::vector<Cell*> attachedNeighbors;
public:
	Cell();
	Point getGridPos();
	Cell(int x, int y, int size, bool isWall);
	bool atPoint(const float & xPos, const float & yPos);
	void render(Renderer& renderer, int cellSize) const;
	void drawCircle(SDL_Renderer *renderer, SDL_Rect *TileMapRect) const;
	void renderSelected(SDL_Renderer *renderer, SDL_Rect *TileMapRect) const;
	void addNeighbor(Cell *neighbor, int direction);
	bool m_iswall;
	std::vector<Cell *> getUnVisitedNeighbors(unsigned int searchId) const;
	std::vector<Cell *> getUnVisitedAttachedNeighbors(unsigned int searchId) const;

	int getX() const { return x; }
	int getY() const { return y; }

	Cell *getAttachedNeighbor(unsigned int direction) const;

	const static int TOP = 0;
	const static int RIGHT = 1;
	const static int BOTTOM = 2;
	const static int LEFT = 3;
};

#endif