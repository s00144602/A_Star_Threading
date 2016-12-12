#pragma once
#include "Scene.h"
#include "Renderer.h"
#include "TileMap.h"
#include <string>
#include "NPC.h"

using namespace std;

class GameScene : public Scene
{
public:
	GameScene(int mapId); // 0 for small, 1 for medium 2 for large
	~GameScene();
	int m_id;
	vector<NPC> npcs = vector<NPC>();
	
	void render(Renderer &r) override;
	void update(float p_deltaTime) override;
	void onEvent(EventListener::Event evt)override;
	void start()override;
	void stop()override;
	TileMap m_TileMap;
private:
	bool m_startClicked;
	bool m_keyDown;
};
