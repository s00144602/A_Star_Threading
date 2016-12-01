#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <time.h>
#include "SDL_ttf.h"
#include "LTimer.h"
#include "Game.h"
#include "Constants.h"
#include "Camera.h"
using namespace std;

Game::Game():
	m_lastTime(LTimer::gameTime()),
	m_winSize(Constants::WIN_WIDTH, Constants::WIN_HEIGHT)
{
	m_pause = false;
	m_quit = false;
}

Game::~Game()
{

}

bool Game::init() {	

	//creates our renderer, which looks after drawing and the window
	m_renderer.init(m_winSize,"A* Maze implementing Threads");

	//set up the viewport
	//we want the vp centred on origin and 20 units wide
	float aspectRatio = m_winSize.w / m_winSize.h;
	float vpWidth = 20;
	m_vpSize = Size2D(vpWidth, vpWidth /aspectRatio);
	Point2D vpBottomLeft( -m_vpSize.w / 2, - m_vpSize.h / 2);
	m_vpRect = Rect(vpBottomLeft,m_vpSize);
	m_renderer.setViewPort(m_vpRect);
	//Add Scenes
	SceneManager::Instance()->addScene(new SmallScene());
	SceneManager::Instance()->addScene(new GameScene());

	//create some game objects


	//add some game objects
	

	//inputManager.AddListener(EventListener::Event::EXAMPLE, EventListener);
	m_inputManager.AddListener(EventListener::Event::UP, this);
	m_inputManager.AddListener(EventListener::Event::DOWN, this);
	m_inputManager.AddListener(EventListener::Event::LEFT, this);
	m_inputManager.AddListener(EventListener::Event::RIGHT, this);
	m_inputManager.AddListener(EventListener::Event::QUIT, this);

	return true;

}

void Game::destroy()
{
	//empty out the game object vector before quitting
	for (std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); i++) {
		delete *i;
	}
	m_gameObjects.clear();
	m_renderer.destroy();
	
}

//** calls update on all game entities*/
void Game::update()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	float deltaTime = (currentTime - m_lastTime) / 1000.0;//time since last update
	SceneManager::Instance()->update(deltaTime);

	//call update on all game objects
	//for (std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); i++) {
	//	(*i)->Update(deltaTime);
	//}

	//save the curent time for next frame
	m_lastTime = currentTime;
}

//** calls render on all game entities*/

void Game::render()
{
	m_renderer.clear(Colour(255,255,255));// prepare for new frame
	
	SceneManager::Instance()->render(m_renderer);
	//render every object
	//for (std::vector<GameObject*>::iterator i = m_gameObjects.begin(), e= m_gameObjects.end(); i != e; i++) {
	//	(*i)->Render(m_renderer);
	//}
	

	m_renderer.present();// display the new frame (swap buffers)

}

/** update and render game entities*/
void Game::loop()
{
	LTimer capTimer;//to cap framerate

	int frameNum = 0;
	while (!m_quit) { //game loop
		capTimer.start();

		m_inputManager.ProcessInput();

		if(!m_pause) //in pause mode don't bother updateing
			update();
		render();

		int frameTicks = capTimer.getTicks();//time since start of frame
		//if (frameTicks < SCREEN_TICKS_PER_FRAME)
		//{
		//	//Wait remaining time before going to next frame
		//	SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		//}
	}
}

void Game::onEvent(EventListener::Event evt) {
		
	if (evt == EventListener::Event::QUIT) {
		m_quit=true;
	}
	if (evt == EventListener::Event::SPACE) {
		
	}
	if (evt == EventListener::Event::UP) {
		Camera::Instance()->onEvent(UP);
	}
	if (evt == EventListener::Event::DOWN) {
		Camera::Instance()->onEvent(DOWN);
	}
	if (evt == EventListener::Event::LEFT) {
		Camera::Instance()->onEvent(LEFT);
	}
	if (evt == EventListener::Event::RIGHT) {
		Camera::Instance()->onEvent(RIGHT);
	}
}

static void RenderThread(void *ptr)
{

}
