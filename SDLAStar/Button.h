#pragma once
#include <SDL.h>
//#include <SDL_image.h>
#include <vector>
#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"

class Button :public GameObject
{

public:
	enum MOUSEPOS { HOVER, DEFAULT, SELECTED };
	//Initialize the variables
	Button(SDL_Texture * t, int x, int y, int w, int h);

	void set_clips();

	//Handles events and set the button's sprite region
	void update(int,int);

	//Shows the button on the screen
	void render(Renderer &r) override;

private:
	//The attributes of the button
	Rect m_rect;
	//The part of the button sprite sheet that will be shown
	Rect * m_clip;

	Rect m_clips[3];// 3 buttons for mouse hover and clicks etc.
	//Textures for Button
	SDL_Texture * m_texture;
	int m_textureWidth = 0;
	int m_textureHeight = 0;

};

