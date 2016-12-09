#include "stdafx.h"
#include <iostream>
#include "SDL_ttf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Constants.h"
#include <time.h>

using namespace std;
#define SDL_MAIN_HANDLED

#ifdef __APPLE__
#include "SDL2/SDL.h"
#elif defined(_WIN64) || defined(_WIN32)
#include "SDL.h"
#endif

#include "Renderer.h"

Renderer::Renderer() :sdl_renderer(NULL)
{

}


bool Renderer::init(const Size2D& winSize, const char* title) 
{

	// Initialize SDL2
	int e = SDL_Init(SDL_INIT_EVERYTHING);

	windowSize = winSize;
	if (e != 0) {
		// problem with SDL?...
		cout << "Could not init SDL: " << SDL_GetError() << std::endl;
		return false;
	}
	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		title,								// window title
		SDL_WINDOWPOS_UNDEFINED,			// initial x position
		SDL_WINDOWPOS_UNDEFINED,			// initial y position
		(int)winSize.w,						// width, in pixels
		(int)winSize.h,						// height, in pixels
		SDL_WINDOW_OPENGL					// flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		cout << "Could not create window: " << SDL_GetError() << std::endl;
		return false;
	}

	sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (sdl_renderer == NULL) {
		// In the case that the renderer could not be made...
		cout << "Could not create renderer: " << SDL_GetError() << std::endl;
		return false;
	}
	
	initTTF();
	
	return true;
}

//draw a rect in pixel coordinates
void Renderer::drawRect(const Rect& r, const Colour& c) 
{
	SDL_SetRenderDrawColor(sdl_renderer, c.r, c.g, c.b, c.a);
	SDL_Rect sr;
	sr.h = (int)r.size.h;
	sr.w = (int)r.size.w;
	sr.x = (int)r.pos.x;
	sr.y = (int)r.pos.y;
	SDL_RenderFillRect(sdl_renderer, &sr);
}

//draw a rectin world coordinates
void Renderer::drawWorldRect(const Rect &r, const Colour &c)
{ 
	drawRect(worldToScreen(r), c);
}

void Renderer::initTTF() 
{
	// Initialize SDL_ttf library
	if (TTF_Init() != 0)
	{
		cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
		SDL_Quit();
		exit(1);
	}

	font = TTF_OpenFont("arial.ttf", 20);
	//this opens a font style and sets a size
	if (font == NULL)
	{
		cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}
}

SDL_Rect renderQuad;
void Renderer::drawText(int i, string message)
{
	surfaceMessage = TTF_RenderText_Solid(font, message.c_str(), colour); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	Message[i] = SDL_CreateTextureFromSurface(sdl_renderer, surfaceMessage); //now you can convert it into a texture

	SDL_FreeSurface(surfaceMessage);
	renderQuad = { 30, 20, surfaceMessage->w, surfaceMessage->h };
	SDL_RenderCopy(sdl_renderer, Message[i], NULL, &renderQuad);
	SDL_DestroyTexture(Message[i]);
}

void Renderer::present() 
{ 
	//swap buffers
	SDL_RenderPresent(sdl_renderer);
}

void Renderer::clear(const Colour& col) {
	SDL_SetRenderDrawColor(sdl_renderer, col.r, col.g, col.b, col.a);
	SDL_RenderClear(sdl_renderer);

}
Point2D Renderer::worldToScreen(const Point2D &p)
{
	float vpTop = viewportBottomLeft.y + viewportSize.h;
	float x = (p.x - viewportBottomLeft.x)* windowSize.w / viewportSize.w;
	float y = (vpTop - p.y)* windowSize.h / viewportSize.h;

	return Point2D(x, y);
}
Rect Renderer::worldToScreen(const Rect &r)
{
	Point2D p = worldToScreen(r.pos);
	float sw = r.size.w*(windowSize.w / viewportSize.w);
	float sh = -r.size.h*(windowSize.h / viewportSize.h);

	return Rect(p, Size2D(sw, sh));
}


void Renderer::setViewPort(Rect &r)
{
	viewportBottomLeft = r.pos;
	viewportSize = r.size;
}

/**Destroys SDL_Window and SDL_Renderer*/
void Renderer::destroy() {
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(window);
}

Renderer::~Renderer()
{
}
