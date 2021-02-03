#pragma once
#ifndef __TARGET__
#define __TARGET__

#include "DisplayObject.h"

class Target final : public DisplayObject {
public:
	Target();
	~Target();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	float getRadius() const;
	void setRadius(float radius);
	void DrawCircle(glm::vec2 centre, int radius, glm::vec4 colour);;

private:
	void m_move();
	void m_checkBounds();
	void m_reset();
	float m_pRadius;
};


#endif /* defined (__TARGET__) */