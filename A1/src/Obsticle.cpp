#include "Obsticle.h"

#include "TextureManager.h"

Obsticle::Obsticle()
{
	TextureManager::Instance()->load("../Assets/textures/obstacle.png", "obsticle");

	auto size = TextureManager::Instance()->getTextureSize("obsticle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);

	setType(OBSTICLE);
}

Obsticle::~Obsticle()
= default;

void Obsticle::draw()
{
	TextureManager::Instance()->draw("obsticle", getTransform()->position.x, getTransform()->position.y);
}

void Obsticle::update()
{
}

void Obsticle::clean()
{
}
