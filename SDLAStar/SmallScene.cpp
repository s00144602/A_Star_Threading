#include "stdafx.h"
#include "SmallScene.h"


SmallScene::SmallScene():
	m_maze(900,9)
{

}

SmallScene::~SmallScene()
{
}

void SmallScene::render(Renderer & r)
{
	m_maze.render(r);
}

void SmallScene::update(float p_deltaTime)
{
}

void SmallScene::onEvent(EventListener::Event evt)
{

}

void SmallScene::start()
{
	//Set up the grid
	//m_maze.createGrid();
	m_maze.createLevel();
}

void SmallScene::stop()
{
}
