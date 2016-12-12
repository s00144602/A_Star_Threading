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
	return m_gridPos;
}

Cell::Cell(int x, int y, int size, bool isWall) :
	x(x), 
	y(y),
	m_size(size), 
	m_iswall(isWall), 
	m_gridPos(x / size, y / size)
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

void Cell::addNeighbor(Cell *neighbor)
{
	m_neighbors.push_back(neighbor);
}

Point Cell::getPos()
{
	return Point(x, y);
}

