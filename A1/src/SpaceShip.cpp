#include "SpaceShip.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"

SpaceShip::SpaceShip()
{
	TextureManager::Instance()->load("../Assets/textures/ship.png", "spaceship");

	auto size = TextureManager::Instance()->getTextureSize("spaceship");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SPACESHIP);
	setMaxSpeed(2.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotationAngle(0.0f);
}

SpaceShip::~SpaceShip() = default;

void SpaceShip::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	//Draw Ship
	TextureManager::Instance()->draw("spaceship", getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);

	//aim lazer
	Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientation * 60.0f));
}

void SpaceShip::update()
{
	m_Move();
}

void SpaceShip::clean()
{

}

void SpaceShip::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}

void SpaceShip::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void SpaceShip::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

void SpaceShip::setRotationAngle(float angle)
{
	m_rotationAngle = angle;
}

float SpaceShip::getRotationAngle()
{
	return m_rotationAngle;
}



void SpaceShip::m_Move()
{
	//Magnitude
	m_targetDirection = m_destination - getTransform()->position;
	//Normalized Direction
	m_targetDirection = Util::normalize(m_targetDirection);
	//this is where we change to move forward instead of move directly to object
	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	getTransform()->position += getRigidBody()->velocity;
}
