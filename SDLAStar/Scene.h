#pragma once
#include "Renderer.h"
#include "EventListener.h"
#include "SceneId.h"

class SceneManager;

class Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void render(Renderer &r);
	virtual void update(float deltaTime);
	virtual void onEvent(EventListener::Event evt);
	virtual void start();
	virtual void stop();
};

#include "SceneManager.h"

