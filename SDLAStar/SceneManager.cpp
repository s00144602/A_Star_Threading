#include "stdafx.h"
#include "SceneManager.h"


SceneManager * SceneManager::m_inst = nullptr;
SceneManager * SceneManager::Instance()
{
	if (!m_inst)
	{
		m_inst = new SceneManager();
	}
	return m_inst;
}

void SceneManager::onEvent(EventListener::Event evt)
{
	m_currentScene->onEvent(evt);
}
void SceneManager::update(float deltaTime)
{
	m_currentScene->update(deltaTime);
}

void SceneManager::changeScene(int scene)
{
	m_sceneID = scene;
	m_currentScene->stop();
	m_currentScene = m_scenes[scene];
	m_currentScene->start();
}

void SceneManager::render(Renderer& r)
{
	m_currentScene->render(r);
}

void SceneManager::addScene(Scene *scene)
{
	if (m_currentScene == nullptr)
	{
		m_currentScene = scene;
		m_currentScene->start();
	}
	m_scenes.push_back(scene);
}

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	for (std::vector<Scene*>::iterator i = m_scenes.begin(), e = m_scenes.end(); i != e; i++)
	{
		delete *i;
	}
	delete m_inst;
	m_scenes.clear();
}
