#include "SpaceShip.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"
using namespace std;

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
	setMaxSpeed(10.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotationAngle(0.0f);
	setAccelerationRate(10.0f);
	setTurnRate(10.0f);
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

glm::vec2 SpaceShip::getOrientation()
{
	return m_orientation;
}

void SpaceShip::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

float SpaceShip::getRotationAngle() const
{
	return m_rotationAngle;
}


void SpaceShip::setRotationAngle(const float angle)
{
	m_rotationAngle = angle;

	const auto offset = -90.0f;
	const auto angle_in_radians = (angle + offset) * Util::Deg2Rad;

	auto x = cos(angle_in_radians);
	auto y = sin(angle_in_radians);

	// convert the angle to a normalized vector and stire in Orientation
	setOrientation(glm::vec2(x, y));
}

float SpaceShip::getTurnRate()
{
	return m_turnRate;
}

void SpaceShip::setTurnRate(const float rate)
{
	m_turnRate = rate;
}

float SpaceShip::getAccelerationRate()
{
	return m_accelerationRate;
}


void SpaceShip::setAccelerationRate(float rate)
{
	m_accelerationRate - rate;
}



void SpaceShip::m_Move()
{

	auto deltaTime = TheGame::Instance()->getDeltaTime();

	//Magnitude
	m_targetDirection = m_destination - getTransform()->position;

	//Normalized Direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensitivity = 10.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setRotationAngle(getRotationAngle() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setRotationAngle(getRotationAngle() - getTurnRate());
		}
	}

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	//PF=Pi+Vi*t+0.5Ai*(t*t)
	getRigidBody()->velocity += getOrientation() * (deltaTime)+0.5f * getRigidBody()->acceleration * (deltaTime);
	//          PF+Vi                    Pi               t+.5                      Ai                      (t*t)?????

	getRigidBody()->velocity - Util::clamp(getRigidBody()->velocity, m_maxSpeed);
	getTransform()->position += getRigidBody()->velocity;
}
