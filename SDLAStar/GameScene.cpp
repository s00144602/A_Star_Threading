#include "stdafx.h"
#include "GameScene.h"
#include "Constants.h"
#include "MathsUtil.h"

bool init = false;
GameScene::GameScene(int mapID):
	m_id(mapID),
	m_TileMap(Constants::MAP_SIZES[mapID],Constants::CELL_SIZES[mapID]),
	m_player(Point(1,1),Constants::CELL_SIZES[mapID])
{
}

GameScene::~GameScene()
{

}

void GameScene::render(Renderer & r)
{
	m_TileMap.render(r);
	m_player.render(r);
	if (init)
	for (auto &n : npcs)
	{
		n.render(r);
	}
	//render every object
	//for (std::vector<GameObject*>::iterator i = m_gameObjects.begin(), e= m_gameObjects.end(); i != e; i++) {
	//	(*i)->Render(m_renderer);
	//}
	//
}

void GameScene::update(float p_deltaTime)
{
	if(init)
		for(auto &n : npcs)
		{
			n.setTargetGridPos(m_player.m_pos);
			n.update(p_deltaTime);
		}
}

void GameScene::onEvent(EventListener::Event evt)
{
	if (evt == EventListener::Event::CHANGESCENE)
	{
		SceneManager::Instance()->changeScene(Scenes::GameScene);
	}
		m_player.onEvent(evt);
}

void GameScene::start()
{
	//Add to npcs
	//randomize and use threads to update

	//get an random pos between
	//check if its a wall.. add 1 to x if it is
	createNPCArray();

	m_player.m_map = m_TileMap.m_cells;

	init = true;

}

void GameScene::createNPCArray()
{
	//Number of NPCs decided by size of level
	int npcArraySize=5;
	switch (m_id)
	{
	case 1:
		npcArraySize *= 10;
		break;
	case 2:
		npcArraySize *= 100;
		break;
	}
	//create the required num of npcs
	//TODO:: unique pos for npcs and range determine by level size
	for (size_t i = 0; i < npcArraySize; i++)
	{
		int x = MathsUtil::randomRange(Constants::NPC_START_RANGE[m_id].first, Constants::NPC_START_RANGE[m_id].second);
		int y = MathsUtil::randomRange(Constants::NPC_START_RANGE[m_id].first, Constants::NPC_START_RANGE[m_id].second);
		//if the x pos is a wall add 1
		if (m_TileMap.m_cells.at(Point(x, y))->m_iswall)
			x++;

		npcs.push_back(
			NPC(m_TileMap.m_cells.at(Point(x, y))->getGridPos(),
				Constants::CELL_SIZES[m_id],
				m_TileMap.m_cells));
	}
}

void GameScene::stop()
{

}


