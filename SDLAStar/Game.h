#pragma once
#include <vector>
#include "Renderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "EventListener.h"
#include "Maze.h"
#include "Scene.h"
#include "GameScene.h"
#include "SmallScene.h"

/** The game objct whic manages the game loop*/
class Game:public EventListener
{

public:
	Game();
	~Game();
	Rect m_vpRect;
	Size2D m_vpSize;
	Size2D m_winSize;

	bool init();
	void destroy();
	void update();
	void render();
	void loop();
	void onEvent(EventListener::Event);

private:
	InputManager m_inputManager;
	Renderer m_renderer;
	std::vector<GameObject*> m_gameObjects;
	std::vector<Scene*> m_scenes;
	unsigned int m_lastTime;//time of last update;
	bool m_pause;
	bool m_quit;


};

