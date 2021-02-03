#pragma once
#ifndef __SPACESHIP__
#define __SPACESHIP__

#include "DisplayObject.h"
#include "TextureManager.h"

class SpaceShip final : public DisplayObject
{
public:
	//Defualt Constructor
	SpaceShip();

	//Destructor
	~SpaceShip();

	void draw() override;
	void update() override;
	void clean() override;

	//setters and getters
	void setDestination(glm::vec2 destination);
	void setDestination2(glm::vec2 destination);
	float getMaxSpeed();
	void setMaxSpeed(float speed);
	glm::vec2 getOrientation();
	void setOrientation(glm::vec2 orientation);
	float getRotationAngle() const;
	void setRotationAngle(float angle);
	float getTurnRate();
	void setTurnRate(const float rate);
	float getAccelerationRate();
	void setAccelerationRate(float rate);

private:

	glm::vec2 m_targetDirection; //Normalized Values or Orientation or looking direction
	glm::vec2 m_destination;//where im going
	glm::vec2 m_orientation;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;
	//Private Function
	void m_Move();
};



#endif /* defined (__SPACE_SHIP__) */