#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene():
	m_maze(300,10)
{
	bool m_keyDown;
}

GameScene::~GameScene()
{

}

void GameScene::render(Renderer & r)
{
	m_maze.render(r);
}

void GameScene::update(float p_deltaTime)
{

}

void GameScene::onEvent(EventListener::Event evt)
{
	if (evt == EventListener::Event::CHANGESCENE)
	{
		SceneManager::Instance()->changeScene(Scenes::GameScene);
	}
}

void GameScene::start()
{
	//Set up the maze
	m_maze.createGrid();
	if (!m_maze.createMaze()) {
		std::cout << "Failed to create maze." << std::endl;
		//return 1;
	}
}

void GameScene::stop()
{

}


