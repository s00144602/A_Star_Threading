#pragma once
#define SDL_MAIN_HANDLED
#ifdef __APPLE__
#include "SDL2/SDL.h"
#elif defined(_WIN64) || defined(_WIN32)
#include "SDL.h"
#endif

#include "BasicTypes.h"
#include <string>
#include "SDL_ttf.h"

//Responsible for all drawing operations
//abstracts away specfic SDL specific drawing functions
class Renderer{

	// size of window in pixels
	Size2D windowSize;
	//position of window in world coordinates
	//change these if you want to zoom or pan
	Point2D viewportBottomLeft;
	Size2D viewportSize;
	SDL_Window *window;
	SDL_Renderer *sdl_renderer;
	TTF_Font* font;
	SDL_Texture* Message[10];
	SDL_Color colour = {0,0,0};
	SDL_Surface* surfaceMessage;

public:
	Renderer();

	bool init(const Size2D&, const char*);
	void drawRect(const Rect&, const Colour&);
	void drawWorldRect(const Rect&, const Colour&);
	void initTTF();
	void drawCircle(int x0, int y0, int radius, const Colour& c);
	void drawText(int id, std::string message);
	void present();
	void clear(const Colour&);
	Point2D worldToScreen(const Point2D&);
	Rect worldToScreen(const Rect&);
	void setViewPort(Rect&);
	void destroy();
	~Renderer();
};

