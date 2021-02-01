#pragma once
#ifndef __OBSTILE__
#define __OBSTICLE__
#include "DisplayObject.h"

class Obsticle final : public DisplayObject
{
public:
	//constructor
	Obsticle();
	//destructor
	~Obsticle();
	//life cycle functions
	void draw() override;
	void update() override;
	void clean() override;

};


#endif