#pragma once

#include "Renderer.h"
#include "math.h"



/*Base class for all in game objects*/
class GameObject
{

public:
	GameObject() {};
	virtual ~GameObject() {};

	virtual void render(Renderer& r)=0;
	virtual void update(float deltaTime)=0;


};

