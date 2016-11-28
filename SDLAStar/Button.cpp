#include "stdafx.h"
#include "Button.h"

//Button::~Button()
//{
//}

Button::Button(SDL_Texture * t, int x, int y, int w, int h) :
	m_rect(x, y, w, h)
{
	m_texture = t;
	SDL_QueryTexture(t, NULL, NULL, &m_textureWidth, &m_textureHeight);

}

void Button::set_clips()
{
	//Clip the sprite sheet
	//Default Button
	m_clips[DEFAULT].pos = Point2D(0, 0);
	m_clips[DEFAULT].size = Size2D(m_textureWidth, m_textureHeight / 4);
	//Hover button
	m_clips[HOVER].pos = Point2D(0, 0);
	m_clips[HOVER].size = Size2D(m_textureWidth, m_textureHeight / 4);
	//Selected Button
	m_clips[SELECTED].pos = Point2D(0, 0);
	m_clips[SELECTED].size = Size2D(m_textureWidth, m_textureHeight / 4);

}

void Button::update(int mouseX, int mouseY)
{
	//If the mouse is over the button
	if ((mouseX > m_rect.pos.x) && (mouseX < m_rect.pos.x + m_rect.size.w) && (mouseY > m_rect.pos.y) && (mouseY < m_rect.pos.y + m_rect.size.h))
	{
		//Set the button sprite
		m_clip = &m_clips[HOVER];
	}
	//If not
	else
	{
		//Set the button sprite
		m_clip = &m_clips[DEFAULT];
	}

}

void Button::render(Renderer & r)
{
}

//TODO: load image
//SDL_Surface *load_image(std::string filename)
//{
//	//The image that's loaded
//	SDL_Surface* loadedImage = NULL;
//
//	//The optimized surface that will be used
//	SDL_Surface* optimizedImage = NULL;
//
//	//Load the image
//	loadedImage = IMG_Load(filename.c_str());
//
//	//If the image loaded
//	if (loadedImage != NULL)
//	{
//		//Create an optimized surface
//		optimizedImage = SDL_DisplayFormat(loadedImage);
//
//		//Free the old surface
//		SDL_FreeSurface(loadedImage);
//
//		//If the surface was optimized
//		if (optimizedImage != NULL)
//		{
//			//Color key surface
//			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
//		}
//	}
