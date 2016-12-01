#include "stdafx.h"
#include "Cell.h"
#include "SDL.h"
#include "SDL_render.h"
#include "Constants.h"


Cell::Cell(int x, int y, int size) :size(size), x(x), y(y), walls{ 0, 0, 0, 0 }, searchVisitId(0)
{
	//neighbors = { nullptr, nullptr, nullptr, nullptr };
	wallSize = 2;
}

void Cell::drawCircle(SDL_Renderer *renderer, SDL_Rect *mazeRect) const
{
	//SDL_RenderFillCircle(renderer, x - mazeRect->x, y - mazeRect->y, size / 2);
}

void Cell::renderSelected(SDL_Renderer *renderer, SDL_Rect *mazeRect) const
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	drawCircle(renderer, mazeRect);
}

void Cell::render(Renderer& renderer) const
{
	Rect rects[4] = {};
	int rectCount = 0;
	if (walls[0]) {
		// top wall.
		rects[rectCount++] = {
			x, y,
			size, wallSize,
		};
	}

	if (walls[1]) {
		// right wall.
		rects[rectCount++] = {
			x + size, y,
			wallSize, size,
		};
	}

	if (walls[2]) {
		// bottom wall.
		rects[rectCount++] = {
			x, y + size,
			size, wallSize,
		};
	}

	if (walls[3]) {
		// left wall.
		rects[rectCount++] = {
			x, y,
			wallSize, size,
		};
	}
	for (size_t i = 0; i < rectCount; i++)
	{
		// if outside the viewable area then skip the tile ie Don't draw
		if ((rects[i].pos.x - Camera::Instance()->getPosition().x) < -size
			|| (rects[i].pos.x - Camera::Instance()->getPosition().x) > Constants::WIN_WIDTH)
		{ 
			continue; 
		}
		Rect drawRect = Rect(Point2D(rects[i].pos.x - Camera::Instance()->getPosition().x, rects[i].pos.y - Camera::Instance()->getPosition().y), rects[i].size);
		renderer.drawRect(drawRect, Colour(rand() % (int)(255 + 1), rand() % (int)(255 + 1), 0, 255));
	}
}

void Cell::addNeighbor(Cell *neighbor, int direction)
{
	neighbors[direction] = neighbor;
}

void Cell::setSearchVisitId(unsigned int visitId)
{
	searchVisitId = visitId;
}

bool Cell::isVisited(unsigned int searchId) const
{
	return searchVisitId == searchId;
}

std::vector<Cell*> Cell::getUnVisitedNeighbors(unsigned int searchId) const
{
	std::vector<Cell *> unvisited;
	for (Cell *c : neighbors) {
		if (c == nullptr || c->isVisited(searchId)) {
			continue;
		}
		unvisited.push_back(c);
	}

	return unvisited;
}

std::vector<Cell *> Cell::getUnVisitedAttachedNeighbors(unsigned int searchId) const
{
	std::vector<Cell *> unvisitedAttached;
	for (auto n : attachedNeighbors) {
		if (n->isVisited(searchId)) {
			continue;
		}
		unvisitedAttached.push_back(n);
	}
	return unvisitedAttached;
}

void Cell::removeWall(const Cell *neighbor)
{
	for (unsigned int i = 0; i < neighbors.size(); i++) {
		if (neighbors[i] == nullptr || neighbors[i] != neighbor) {
			continue;
		}
		attachedNeighbors.push_back(neighbors[i]);
		walls[i] = 0;
		break;
	}
}

void Cell::removeAllWalls()
{
	walls[0] = 0;
	walls[1] = 0;
	walls[2] = 0;
	walls[3] = 0;
}

void Cell::addWall(int direction)
{
	walls[direction] = 1;
}

void Cell::removeWall(int direction)
{
	walls[direction] = 0;
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
