#include "stdafx.h"
#include "GameScene.h"
#include "Constants.h"

bool init = false;
GameScene::GameScene(int mapID):
	m_id(mapID),
	m_TileMap(Constants::MAP_SIZES[mapID],Constants::CELL_SIZES[mapID])
{
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
	//Add to npcs
	//randomize and use threads to update
	npcs.push_back(
		NPC(m_TileMap.m_cells.at(Point(1, 10))->getGridPos(),
		Constants::CELL_SIZES[m_id],
		m_TileMap.m_cells));

	init = true;

}

void GameScene::stop()
{

}


