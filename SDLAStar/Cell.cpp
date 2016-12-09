#include "stdafx.h"
#include "Cell.h"
#include "SDL.h"
#include "SDL_render.h"
#include "Constants.h"


Cell::Cell()
{
}

Point Cell::getGridPos()
{
	return Point(x/m_size,y/m_size);
}

Cell::Cell(int x, int y, int size, bool isWall) : x(x), y(y), m_size(size), m_iswall(isWall)
{
	
}

bool Cell::atPoint(const float& xPos,const float& yPos)
{
	if ((x == xPos) && (y = yPos))
	{
		return true;
	}
	return false;
}

void Cell::drawCircle(SDL_Renderer *renderer, SDL_Rect *TileMapRect) const
{
	//SDL_RenderFillCircle(renderer, x - TileMapRect->x, y - TileMapRect->y, size / 2);
}

void Cell::renderSelected(SDL_Renderer *renderer, SDL_Rect *TileMapRect) const
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	drawCircle(renderer, TileMapRect);
}


//TODO:refactor .. get rid of walls and attach a boolean to detemine if wall or not
void Cell::render(Renderer& renderer, int cellsize) const
{
	Rect drawRect = Rect(Point2D(x - Camera::Instance()->getPosition().x, y - Camera::Instance()->getPosition().y), Size2D(cellsize, cellsize));
		renderer.drawRect(drawRect, Colour(255, 0, 0, 255));
}

void Cell::addNeighbor(Cell *neighbor, int direction)
{
	neighbors[direction] = neighbor;
}





Cell *Cell::getAttachedNeighbor(unsigned int direction) const
{
	auto n = neighbors[direction];
	for (Cell *c : attachedNeighbors) {
		if (n == c) {
			return c;
		}
	}

	return nullptr;
}
