#pragma once
#ifndef __SPACESHIP4__
#define __SPACESHIP4__

#include "DisplayObject.h"
#include "TextureManager.h"

class SpaceShip4 final : public DisplayObject
{
public:
	//Defualt Constructor
	SpaceShip4();

	//Destructor
	~SpaceShip4();

	void draw() override;
	void update() override;
	void clean() override;

	//setters and getters
	//void DrawCircle();
	void setDestination(glm::vec2 destination);
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
	glm::vec2 m_whiskerAngle;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;
	//Private Function
	void m_Move();
};



#endif /* defined (__SPACE_SHIP__) */#pragma once
#pragma once
