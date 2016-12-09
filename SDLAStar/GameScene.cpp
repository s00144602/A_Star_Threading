#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene():
	m_TileMap(300,10)
{
	bool m_keyDown;
}

GameScene::~GameScene()
{

}

void GameScene::render(Renderer & r)
{
	m_TileMap.render(r);
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
	m_TileMap.createLevel();
}

void GameScene::stop()
{

}


