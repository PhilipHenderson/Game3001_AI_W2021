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
	void setMaxSpeed(float speed);

private:


	
	glm::vec2 m_targetDirection; //Normalized Values or Orientation or looking direction
	glm::vec2 m_destination;//where im going
	float m_maxSpeed;
	//Private Function
	void m_Move();
};



#endif /* defined (__SPACE_SHIP__) */