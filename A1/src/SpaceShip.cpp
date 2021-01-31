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
}

SpaceShip::~SpaceShip() = default;

void SpaceShip::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	TextureManager::Instance()->draw("spaceship", x, y, m_currentHeading, 255, true);
}

void SpaceShip::update()
{
	move();
}

void SpaceShip::move()
{
	getTransform()->position += getRigidBody()->velocity;
	getRigidBody()->velocity *= 0.9f;
}

void SpaceShip::clean()
{
}

void SpaceShip::tRight()
{
}

void SpaceShip::tLeft()
{
}

void SpaceShip::mForward()
{
}

void SpaceShip::mBack()
{
}
