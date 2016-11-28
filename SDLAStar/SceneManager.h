#pragma once
#include <vector>
#include "EventListener.h"
#include "Scene.h"
#include "Renderer.h"

class SceneManager
{
public:
	static SceneManager * Instance();
	void onEvent(EventListener::Event evt);
	void update(float deltaTime);
	void changeScene(int scene);
	void render(Renderer & r);
	void addScene(Scene *p_scene);
	int m_sceneID = 0;

private:
	std::vector<Scene*>m_scenes;
	Scene *m_currentScene;
	static SceneManager *m_inst;
	SceneManager();
	~SceneManager();
};


