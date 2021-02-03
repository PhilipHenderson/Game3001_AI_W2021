#include "SpaceShip4.h"
#include "Target.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"
#include "Math.h"
using namespace std;

SpaceShip4::SpaceShip4()
{
	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SPACESHIP);
	setMaxSpeed(getMaxSpeed());
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotationAngle(0.0f);
	setAccelerationRate(10.0f);
	setTurnRate(10.0f);
}

SpaceShip4::~SpaceShip4() = default;

void SpaceShip4::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	//Draw Ship
	TextureManager::Instance()->draw("spaceship", getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);
}

void SpaceShip4::update()
{
	m_Move();

	//Util::distance(getTransform()->position, m_pTarget->getTransform()->position);
}
void SpaceShip4::clean()
{

}

void SpaceShip4::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}

float SpaceShip4::getMaxSpeed()
{
	return m_maxSpeed;
}
void SpaceShip4::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

glm::vec2 SpaceShip4::getOrientation()
{
	return m_orientation;
}
void SpaceShip4::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

float SpaceShip4::getRotationAngle() const
{
	return m_rotationAngle;
}
void SpaceShip4::setRotationAngle(const float angle)
{
	m_rotationAngle = angle;

	const auto offset = -90.0f;
	const auto angle_in_radians = (angle + offset) * Util::Deg2Rad;

	auto x = cos(angle_in_radians);
	auto y = sin(angle_in_radians);

	// convert the angle to a normalized vector and stire in Orientation
	setOrientation(glm::vec2(x, y));
}

float SpaceShip4::getTurnRate()
{
	return m_turnRate;
}
void SpaceShip4::setTurnRate(const float rate)
{
	m_turnRate = rate;
}

float SpaceShip4::getAccelerationRate()
{
	return m_accelerationRate;
}
void SpaceShip4::setAccelerationRate(const float rate)
{
	m_accelerationRate = rate;
}

void SpaceShip4::m_Move()
{

	auto deltaTime = TheGame::Instance()->getDeltaTime();

	//Magnitude
	m_targetDirection = m_destination - getTransform()->position;

	//Normalized Direction
	m_targetDirection = Util::normalize(m_targetDirection);

	//Arrivinging
	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

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
