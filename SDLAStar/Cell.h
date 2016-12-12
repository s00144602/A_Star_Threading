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

	//bool operator() (const Cell& lhs, Cell& rhs) const;


protected:
	Point m_gridPos;

public:
	Cell();
	Cell(int x, int y, int size, bool isWall);

	bool operator <(const Cell& rhs) const
	{
		return (x < rhs.getX() && y < rhs.getY());
	}

	bool operator =(const Cell& rhs) const
	{
		return (x == rhs.getX() && y == rhs.getY());
	}

	Point getGridPos();
	std::vector<Cell*> m_neighbors;
	
	bool atPoint(const float & xPos, const float & yPos);
	void render(Renderer& renderer, int cellSize) const;
	void drawCircle(SDL_Renderer *renderer, SDL_Rect *TileMapRect) const;
	void renderSelected(SDL_Renderer *renderer, SDL_Rect *TileMapRect) const;
	void addNeighbor(Cell *neighbor);
	Point getPos();
	bool m_iswall;
	int getX() const { return x; }
	int getY() const { return y; }
};
