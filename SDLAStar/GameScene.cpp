#include "stdafx.h"
#include "GameScene.h"

bool init = false;
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
	if (init)
	for (auto &n : npcs)
	{
		n.render(r);
	}
}

void GameScene::update(float p_deltaTime)
{
	if(init)
		for(auto &n : npcs)
		{
			n.update(p_deltaTime);
		}
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
	//m_TileMap.createLevel();
	npcs.push_back(
		NPC(m_TileMap.m_cells.at(Point(1, 1))->getPos(),
		10,
		m_TileMap.m_cells));
	//testNPC = NPC(m_TileMap.m_cells.at(Point(1,1))->getPos(), 10, m_TileMap.m_cells);
	init = true;

}

void GameScene::stop()
{

}


