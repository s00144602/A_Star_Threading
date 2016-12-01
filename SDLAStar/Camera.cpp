#include "stdafx.h"
#include "Camera.h"
#include "Constants.h"

Camera * Camera::s_pCamera = nullptr;

Camera * Camera::Instance()
{
	if (s_pCamera == nullptr)
	{
		s_pCamera = new Camera();
		//test

	}
	return s_pCamera;
}

void Camera::update(Point2D velocity)
{
}

void Camera::onEvent(EventListener::Event evt)
{
	switch (evt) {
		//TODO: Change to maze size restriction
	case EventListener::Event::UP:
		if (m_position.y > 10)
			setPosition(Point2D(m_position.x, m_position.y - 11));
		break;
	case EventListener::Event::DOWN:
		if (m_position.x < Constants::WIN_HEIGHT)
		setPosition(Point2D(m_position.x, m_position.y + 11));
		break;
	case EventListener::Event::LEFT:
		if (m_position.x > 10)
		setPosition(Point2D(m_position.x - 11, m_position.y));
		break;
	case EventListener::Event::RIGHT:
		if (m_position.x < Constants::WIN_WIDTH)
		setPosition(Point2D(m_position.x + 11, m_position.y));
		break;

	}
}

const Point2D Camera::getPosition() const
{
	//if (m_pTarget != 0) {
	//	Point2D pos(m_pTarget->x - (Constants::WIN_WIDTH / 2), 0);
	//	if (pos.x < 0)
	//	{
	//		pos.x = 0;
	//	}
	//	return pos;
	//}
	return m_position;
}

Camera::Camera()
{
}


Camera::~Camera()
{
}
