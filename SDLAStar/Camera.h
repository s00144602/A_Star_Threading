#pragma once
#include "BasicTypes.h"
#include "EventListener.h"
#include <math.h>
#include "glm\glm.hpp"

class Camera {
public:
	static Camera* Instance();

	void update(Point2D velocity);
	void onEvent(EventListener::Event evt);
	void setTarget(Point2D* target) { m_pTarget = target; }  
	void setPosition(const Point2D& position) { m_position = position; }
	const Point2D getPosition() const;

private:
	Camera();  ~Camera();
	// the camera's target  
	Point2D* m_pTarget;
	// the camera's position  
	Point2D m_position;
	static Camera* s_pCamera;

	int viewport_x;
	int viewport_y;

	int window_width;
	int window_height;

	double aspect;
	double field_of_view;

	float camera_scale;
	bool move_camera;

};