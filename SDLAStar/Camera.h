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

//private:
	Camera();  ~Camera();
	// the camera's target  
	Point2D* m_pTarget;
	// the camera's position  
	Point2D m_position;
	static Camera* s_pCamera;

	//TEST
	void Move2D(int x, int y);

	//Setting Functions
	//Set the position of the camera
	void SetPosition(glm::vec3 pos);
	//Set's the look at point for the camera
	void SetLookAt(glm::vec3 pos);
	//Changes the Field of View (FOV) for the camera
	void SetFOV(double fov);
	//Change the viewport location and size
	void SetViewport(int loc_x, int loc_y, int width, int height);

	void SetDistance(double cam_dist);
	void SetPos(int button, int state, int x, int y);

	//Getting Functions
	void GetViewport(int &loc_x, int &loc_y, int &width, int &height);
	void GetMatricies(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M);

	int viewport_x;
	int viewport_y;

	int window_width;
	int window_height;

	double aspect;
	double field_of_view;

	float camera_scale;
	bool move_camera;


};