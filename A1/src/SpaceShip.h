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

	void tRight();
	void tLeft();
	void mForward();
	void mBack();

	void move();


private:
	float m_currentHeading;
	float m_turnRate;
};



#endif /* defined (__SPACE_SHIP__) */