#pragma once

#include "Scene.h"
#include "Renderer.h"
#include "TileMap.h"
#include <string>

using namespace std;

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void render(Renderer &r) override;
	void update(float p_deltaTime) override;
	void onEvent(EventListener::Event evt)override;
	void start()override;
	void stop()override;
private:
	TileMap m_TileMap;
	bool m_startClicked;
	bool m_keyDown;
};
