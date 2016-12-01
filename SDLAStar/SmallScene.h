#pragma once
#include "Scene.h"
#include "Renderer.h"
#include "Maze.h"

class SmallScene : public Scene
{
public:
	SmallScene();
	~SmallScene();

	void render(Renderer &r) override;
	void update(float p_deltaTime) override;
	void onEvent(EventListener::Event evt)override;
	void start()override;
	void stop()override;

private:
	Maze m_maze;
	bool m_keyDown;
};

