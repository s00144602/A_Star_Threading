#include "stdafx.h"
#include "Player.h"


Player::Player(Point startPos, int size):
	m_pos(startPos),
	m_size(size)
{
}

Player::~Player()
{
}

void Player::update(float delatTime)
{
}

void Player::render(Renderer & r)
{
	r.drawRect(
		Rect(
			(m_pos.first*m_size) - Camera::Instance()->getPosition().x,
			(m_pos.second*m_size) - Camera::Instance()->getPosition().y,
			m_size,
			m_size),
			{ 0,255,255,100 }
	);
}

void Player::onEvent(EventListener::Event evt)
{
	if (evt == EventListener::Event::W)
	{
		if (!m_map.at(Point(m_pos.first, m_pos.second - 1))->m_iswall)
		m_pos.second--;
	}
	if (evt == EventListener::Event::A)
	{
		if (!m_map.at(Point(m_pos.first - 1, m_pos.second))->m_iswall)
		m_pos.first--;
	}
	if (evt == EventListener::Event::S)
	{
		if (!m_map.at(Point(m_pos.first, m_pos.second+1))->m_iswall)
			m_pos.second++;
	}
	if (evt == EventListener::Event::D)
	{
		if(!m_map.at(Point(m_pos.first+1,m_pos.second))->m_iswall)
			m_pos.first++;
	}
}
